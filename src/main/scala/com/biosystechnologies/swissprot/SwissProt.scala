package com.biosystechnologies.swissprot


import java.text.SimpleDateFormat
import java.time.{LocalDate, ZoneId}
import java.util.Date

import akka.actor.Status.Success
import akka.stream.alpakka.xml.{EndElement, StartElement, TextEvent}
import akka.stream.alpakka.xml.scaladsl.XmlParsing
import akka.stream.scaladsl.{Compression, FileIO, Flow, Source}
import akka.util.ByteString

import scala.collection.mutable.ArrayBuffer
import scala.util.Try

object SwissProt {
  private val dateFormat = new SimpleDateFormat("yyyy-MM-dd")
  //   def entries: Flow[ByteString,Entry,_] = {
  //     val next = List()
  //     val buffer: ArrayBuffer[Char] = new ArrayBuffer[Char]()
  //     var inEntry = false
  //     var dataSet:String  = ""
  //     var created: Date  = java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant)
  //     var modified: Date  = java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant)
  //     var version: Int  = 0
  //     val accessions: ArrayBuffer[String] = new ArrayBuffer[String]()
  //     val names: ArrayBuffer[String] = new ArrayBuffer[String]()
  //     var inProtein = false
  //     var inProteinRecommendedName = false
  //     val proteinRecommendedNames: ArrayBuffer[ProteinName] = new ArrayBuffer[ProteinName]()
  //     val alternativeNames: ArrayBuffer[ProteinName] = new ArrayBuffer[ProteinName]()
  //     val submittedNames: ArrayBuffer[ProteinName] = new ArrayBuffer[ProteinName]()
  //     var allergenName: Option[String] = None
  //     var biotechName: Option[String] = None
  //     val cdAntigenName: ArrayBuffer[String] = new ArrayBuffer[String]()
  //     val innName: ArrayBuffer[String] = new ArrayBuffer[String]()
  //     var proteinFullName = ""
  //     val proteinShortNames: ArrayBuffer[String] = new ArrayBuffer[String]()
  //     val proteinEcNumbers: ArrayBuffer[String] = new ArrayBuffer[String]()
  //
  //     var protein: Option[Protein] = None
  //     var sequence: Option[Sequence] = None
  //
  //     var inOrganism = false
  //     var organism: Option[Organism] = None
  //     val organismNames: ArrayBuffer[OrganismName] = new ArrayBuffer[OrganismName]()
  //     var organismNameType: OrganismName.NameType = OrganismName.NameTypeUnknown
  //     val organismDbRefs: ArrayBuffer[DbReference] = new ArrayBuffer[DbReference]()
  //     val organismTaxons: ArrayBuffer[String] = new ArrayBuffer[String]()
  //     var inOrganismTaxon = false
  //
  //     var sequenceLength:Int = 0
  //     var sequenceMass:Int = 0
  //     var sequenceChecksum: String = ""
  //     var sequenceModified: Date = java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant)
  //     var sequenceVersion:Int = 0
  //     var sequencePrecursor: Option[Boolean] = None
  //     var sequenceFragment: Option[Sequence.FragmentType] = None
  //
  //
  //     XmlParsing.parser().statefulMapConcat(() => {
  //       case e: StartElement if e.localName == "entry" =>
  //         dataSet = e.findAttribute("dataset").map(_.value).getOrElse("")
  //         created = e.findAttribute("created").map(_.value).map(dateFormat.parse).getOrElse(java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant))
  //         modified = e.findAttribute("modified").map(_.value).map(dateFormat.parse).getOrElse(java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant))
  //         version = e.findAttribute("version").map(_.value.toInt).getOrElse(0)
  //         accessions.clear()
  //         names.clear()
  //         protein = None
  //         sequence = None
  //         inEntry = true
  //         next
  //       case e: EndElement if e.localName == "entry" =>
  //         inEntry = false
  //         val entry = Entry(
  //           dataSet = dataSet,
  //           created = created,
  //           modified = modified,
  //           version = version,
  //           accessions = accessions.toList,
  //           names = names.toList,
  //           organism = organism.get,
  //           protein = protein.get,
  //           sequence = sequence.get
  //         )
  //         List(entry)
  //       case e: StartElement if e.localName == "accession" =>
  //         buffer.clear()
  //         next
  //       case e: EndElement if e.localName == "accession" =>
  //         accessions.addOne(buffer.mkString)
  //         next
  //       case e: StartElement if e.localName == "name" =>
  //         buffer.clear()
  //         next
  //       case e: EndElement if e.localName == "name" =>
  //         names.addOne(buffer.mkString)
  //         next
  //       case e: StartElement if e.localName == "organism" =>
  //         inOrganism = true
  //         organismNames.clear()
  //         organismDbRefs.clear()
  //         organismTaxons.clear()
  //         organism = None
  //         next
  //       case e: EndElement if e.localName == "organism" =>
  //         inOrganism = false
  //         organism = Some(
  //           Organism(names = organismNames.toList, dbReferences = organismDbRefs.toList, taxons = organismTaxons.toList)
  //         )
  //         next
  //       case e: StartElement if e.localName == "name" && inOrganism =>
  //         organismNameType = e.findAttribute("type").map(_.value).get match {
  //           case "scientific" => OrganismName.NameTypeScientific
  //           case "common" => OrganismName.NameTypeCommon
  //           case "full" => OrganismName.NameTypeFull
  //           case "scientific"  => OrganismName.NameTypeScientific
  //           case "synonym"  => OrganismName.NameTypeSynonym
  //           case "abbreviation"  => OrganismName.NameTypeAbbreviation
  //           case _ => OrganismName.NameTypeUnknown
  //         }
  //         buffer.clear()
  //         next
  //       case e: EndElement if e.localName == "name" && inOrganism =>
  //         organismNames.addOne(OrganismName(value = buffer.mkString,nameType = organismNameType))
  //         next
  //       case e: StartElement if e.localName == "dbReference" && inOrganism =>
  //         val dataBase = e.findAttribute("type").map(_.value).getOrElse("")
  //         val id = e.findAttribute("id").map(_.value).getOrElse("")
  //         organismDbRefs.addOne(DbReference(dataBase = dataBase, id = id))
  //         next
  //       case e: StartElement if e.localName == "taxon" && inOrganism =>
  //         buffer.clear()
  //         inOrganismTaxon = true
  //         next
  //       case e: EndElement if e.localName == "taxon" && inOrganismTaxon =>
  //         inOrganismTaxon = false
  //         organismTaxons.addOne(buffer.mkString)
  //         next
  //       case e: StartElement if e.localName == "protein" =>
  //         proteinRecommendedNames.clear()
  //         alternativeNames.clear()
  //         submittedNames.clear()
  //         allergenName = None
  //         biotechName = None
  //         cdAntigenName.clear()
  //         innName.clear()
  //         protein = None
  //         inProtein = true
  //         next
  //       case e: EndElement if e.localName == "protein" =>
  //         protein = Some(
  //           Protein(
  //             recommendedNames = proteinRecommendedNames.toList,
  //             alternativeNames = alternativeNames.toList,
  //             submittedNames = submittedNames.toList,
  //             allergenName = allergenName,
  //             biotechName = biotechName,
  //             cdAntigenNames = cdAntigenName.toList,
  //             innNames = innName.toList
  //           )
  //         )
  //         inProtein = false
  //         next
  //       case e: StartElement if e.localName == "recommendedName" && inProtein =>
  //         proteinFullName = ""
  //         proteinShortNames.clear()
  //         proteinEcNumbers.clear()
  //         inProteinRecommendedName = true
  //         next
  //       case e: EndElement if e.localName == "recommendedName" && inProtein =>
  //         val proteinName = ProteinName(
  //           fullName = proteinFullName,
  //           shortNames = proteinShortNames.toList,
  //           ecNumbers = proteinEcNumbers.toList
  //         )
  //         proteinRecommendedNames.addOne(proteinName)
  //         inProteinRecommendedName = false
  //         next
  //       case e: StartElement if e.localName == "fullName" && inProtein =>
  //         buffer.clear
  //         next
  //       case e: EndElement if e.localName == "fullName" && inProtein =>
  //         proteinFullName = buffer.mkString
  //         next
  //       case e: StartElement if e.localName == "shortName" && inProtein =>
  //         buffer.clear
  //         next
  //       case e: EndElement if e.localName == "shortName" && inProtein =>
  //         proteinShortNames.addOne(buffer.mkString)
  //         next
  //       case e: StartElement if e.localName == "ecNumber" && inProtein =>
  //         buffer.clear()
  //         next
  //       case e: EndElement if e.localName == "ecNumber" && inProtein =>
  //         proteinEcNumbers.addOne(buffer.mkString)
  //         next
  //       case e: StartElement if e.localName == "sequence" =>
  //         buffer.clear
  //         sequenceLength = e.findAttribute("length").map(_.value.toInt).getOrElse(0)
  //         sequenceMass = e.findAttribute("mass").map(_.value.toInt).getOrElse(0)
  //         sequenceChecksum = e.findAttribute("checksum").map(_.value).getOrElse("")
  //         sequenceModified = e.findAttribute("modified").map(_.value).map(dateFormat.parse).getOrElse(java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant))
  //         sequenceVersion = e.findAttribute("version").map(_.value.toInt).getOrElse(0)
  //         sequencePrecursor = e.findAttribute("precursor").map(_.value).map { case "true" => true case _ => false }
  //         sequenceFragment = e.findAttribute("fragment").map(_.value).map {
  //           case "single" => Sequence.FragmentTypeSingle
  //           case "multiple" => Sequence.FragmentTypeMultiple
  //         }
  //         next
  //       case e: EndElement if e.localName == "sequence" =>
  //         sequence = Some(Sequence(
  //           value = buffer.mkString,
  //           length = sequenceLength,
  //           mass = sequenceMass,
  //           checksum = sequenceChecksum,
  //           modified = sequenceModified,
  //           version = sequenceVersion,
  //           precursor = sequencePrecursor,
  //           fragment = sequenceFragment
  //         ))
  //         next
  //       case t: TextEvent =>
  //         buffer.addAll(t.text)
  //         next
  //       case _ =>
  //         next
  //
  //     })
  //   }


  private def parse(s: String): Try[Entry] = {
    try {
      val doc = scala.xml.XML.loadString(s)

      val dataSet = doc.attribute("dataset").map(_.text)
      val entry = Entry(
        dataSet = dataSet.get,
        created = doc.attribute("created").map(_.text).map(dateFormat.parse).map(_.getTime).get,
        modified = doc.attribute("modified").map(_.text).map(dateFormat.parse).map(_.getTime).get,
        version = doc.attribute("version").map(_.text.toInt).get,
        names = (doc \ "name").map(_.text).toList,
        accessions = (doc \ "accession").map(_.text).toList,
        organism = (doc \ "organism").map {
          organismNode =>
            val organismNames: List[OrganismName] = (organismNode \ "name").map(node => (node, node.attribute("type").map(_.text))).map {
              case (n, Some(nameType)) => OrganismName(value = n.text, nameType = nameType)
              case (n, _) => OrganismName(value = n.text, nameType = "unknown") //OrganismName(value = n.text, nameType = OrganismName.NameTypeUnknown)
            }.toList
            val dbRefs = (organismNode \ "dbReference").map {
              dbReferenceNode =>
                DbReference(
                  dataBase = dbReferenceNode.attribute("type").map(_.text).get,
                  id = dbReferenceNode.attribute("id").map(_.text).get
                )
            }.toList
            val taxons = (organismNode \ "lineage" \ "taxon").map(_.text).toList
            Organism(
              names = organismNames,
              dbReferences = dbRefs,
              taxons = taxons
            )
        }.head,
        protein = (doc \ "protein").map {
          proteinNode =>
            val recommendedNames = (proteinNode \ "recommendedName").map {
              recommendedNameNode =>
                val fullName: Seq[String] = (recommendedNameNode \ "fullName").map(_.text)
                val shortNames = (recommendedNameNode \ "shortName").map(_.text).toList
                val ecNumbers = (recommendedNameNode \ "ecNumber").map(_.text).toList
                ProteinName(fullName = fullName.head, shortNames = shortNames, ecNumbers = ecNumbers)
            }.toList
            Protein(recommendedNames = recommendedNames)
        }.head,
        sequence = (doc \ "sequence").map {
          sequenceNode => {
            val length = sequenceNode.attribute("length").map(_.text.toInt).get
            val mass = sequenceNode.attribute("mass").map(_.text.toInt).get
            val checksum = sequenceNode.attribute("checksum").map(_.text).get
            val modified = sequenceNode.attribute("modified").map(_.text).map(dateFormat.parse)
            val version = sequenceNode.attribute("version").map(_.text.toInt).get
            val seq = sequenceNode.text
            Sequence(
              value = seq,
              length = length,
              mass = mass,
              checksum = checksum,
              modified = modified,
              version = version,
              precursor = None,
              fragment = None
            )
          }
        }.head
      )
//      println(s"${entry.names.head}: ${entry.organism.names.head.value}: ${entry.protein.recommendedNames.head.fullName}")
      scala.util.Success(entry)
    } catch {
      case e: Throwable =>
        println(e.getMessage)
        println(s)
        scala.util.Failure(e)
    }
  }

  def escape(s: String) = s
    .replace("\"", "&quot;")
    .replace("&", "&amp;")
    .replace("'", "&apos;")
    .replace("<", "&lt;")
    .replace(">", "&gt;")

  def entries: Flow[ByteString, Entry, _] = {
    val next = List()
    val buffer: ArrayBuffer[Char] = new ArrayBuffer[Char]()
    var inEntry = false
    XmlParsing.parser().statefulMapConcat(() => {
      case e: StartElement if e.localName == "entry" =>
        inEntry = true
        buffer.clear()

        val attrs = e.attributes.map(v => s"""${v._1}="${v._2}"""").mkString(" ")
        buffer.addAll(s"<${e.localName} ${attrs}>")

        next
      case e: EndElement if e.localName == "entry" =>
        buffer.addAll(s"</${e.localName}>")
        val str = buffer.mkString
        inEntry = false
        parse(str) match {
          case scala.util.Success(entry) => List(entry)
          case _ => List()
        }
      case e: StartElement =>
        if (e.attributes.isEmpty) {
          buffer.addAll(s"<${e.localName}>")
        } else {
          val attrs = e.attributes.map(v => s"""${v._1}="${escape(v._2)}"""").mkString(" ")
          buffer.addAll(s"<${e.localName} ${attrs}>")
        }
        next
      case e: EndElement =>
        buffer.addAll(s"</${e.localName}>")
        next
      case t: TextEvent if inEntry =>
        buffer.addAll(escape(t.text))
        next
      case _ =>
        next
    })
  }

}
