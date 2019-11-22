package com.biosystechnologies.swissprot


import java.text.SimpleDateFormat
import java.time.{LocalDate, ZoneId}
import java.util.Date

import akka.stream.alpakka.xml.{EndElement, StartElement, TextEvent}
import akka.stream.alpakka.xml.scaladsl.XmlParsing
import akka.stream.scaladsl.{Compression, FileIO, Flow, Source}
import akka.util.ByteString

import scala.collection.mutable.ArrayBuffer

object SwissProt {
   private val dateFormat = new SimpleDateFormat("yyyy-MM-dd")
   def entries: Flow[ByteString,Entry,_] = {
     val next = List()
     val buffer: ArrayBuffer[Char] = new ArrayBuffer[Char]()
     var dataSet:String  = ""
     var created: Date  = java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant)
     var modified: Date  = java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant)
     var version: Int  = 0
//     var inAccession = false
     val accessions: ArrayBuffer[String] = new ArrayBuffer[String]()
//     var inName = false
     val names: ArrayBuffer[String] = new ArrayBuffer[String]()
     var inProtein = false
     var inProteinRecommendedName = false
     val proteinRecommendedNames: ArrayBuffer[ProteinName] = new ArrayBuffer[ProteinName]()
     val alternativeNames: ArrayBuffer[ProteinName] = new ArrayBuffer[ProteinName]()
     val submittedNames: ArrayBuffer[ProteinName] = new ArrayBuffer[ProteinName]()
     var allergenName: Option[String] = None
     var biotechName: Option[String] = None
     val cdAntigenName: ArrayBuffer[String] = new ArrayBuffer[String]()
     val innName: ArrayBuffer[String] = new ArrayBuffer[String]()
     var proteinFullName = ""
     val proteinShortNames: ArrayBuffer[String] = new ArrayBuffer[String]()
     val proteinEcNumbers: ArrayBuffer[String] = new ArrayBuffer[String]()
     var sequenceLength:Int = 0
     var sequenceMass:Int = 0
     var sequenceChecksum: String = ""
     var sequenceModified: Date = java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant)
     var sequenceVersion:Int = 0
     var sequencePrecursor: Option[Boolean] = None
     var sequenceFragment: Option[Sequence.FragmentType] = None

     var protein: Option[Protein] = None
     var sequence: Option[Sequence] = None

     XmlParsing.parser().statefulMapConcat(() => {
       case e: StartElement if e.localName == "entry" =>
         dataSet = e.findAttribute("dataset").map(_.value).getOrElse("")
         created = e.findAttribute("created").map(_.value).map(dateFormat.parse).getOrElse(java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant))
         modified = e.findAttribute("modified").map(_.value).map(dateFormat.parse).getOrElse(java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant))
         version = e.findAttribute("version").map(_.value.toInt).getOrElse(0)
         accessions.clear()
         names.clear()
         protein = None
         sequence = None
         next
       case e: EndElement if e.localName == "entry" =>
         val entry = Entry(
           dataSet = dataSet,
           created = created,
           modified = modified,
           version = version,
           accessions = accessions.toList,
           names = names.toList,
           protein = protein.get,
           sequence = sequence.get
         )
         List(entry)
       case e: StartElement if e.localName == "accession" =>
         buffer.clear()
         next
       case e: EndElement if e.localName == "accession" =>
         accessions.addOne(buffer.mkString)
         next
       case e: StartElement if e.localName == "name" =>
         buffer.clear()
         next
       case e: EndElement if e.localName == "name" =>
         names.addOne(buffer.mkString)
         next
       case e: StartElement if e.localName == "protein" =>
         proteinRecommendedNames.clear()
         alternativeNames.clear()
         submittedNames.clear()
         allergenName = None
         biotechName = None
         cdAntigenName.clear()
         innName.clear()
         protein = None
         inProtein = true
         next
       case e: EndElement if e.localName == "protein" =>
         protein = Some(
           Protein(
             recommendedNames = proteinRecommendedNames.toList,
             alternativeNames = alternativeNames.toList,
             submittedNames = submittedNames.toList,
             allergenName = allergenName,
             biotechName = biotechName,
             cdAntigenNames = cdAntigenName.toList,
             innNames = innName.toList
           )
         )
         inProtein = false
         next
       case e: StartElement if e.localName == "recommendedName" && inProtein =>
         proteinFullName = ""
         proteinShortNames.clear()
         proteinEcNumbers.clear()
         inProteinRecommendedName = true
         next
       case e: EndElement if e.localName == "recommendedName" && inProtein =>
         val proteinName = ProteinName(
           fullName = proteinFullName,
           shortNames = proteinShortNames.toList,
           ecNumbers = proteinEcNumbers.toList
         )
         proteinRecommendedNames.addOne(proteinName)
         inProteinRecommendedName = false
         next
       case e: StartElement if e.localName == "fullName" && inProtein =>
         buffer.clear
         next
       case e: EndElement if e.localName == "fullName" && inProtein =>
         proteinFullName = buffer.mkString
         next
       case e: StartElement if e.localName == "shortName" && inProtein =>
         buffer.clear
         next
       case e: EndElement if e.localName == "shortName" && inProtein =>
         proteinShortNames.addOne(buffer.mkString)
         next
       case e: StartElement if e.localName == "ecNumber" && inProtein =>
         buffer.clear()
         next
       case e: EndElement if e.localName == "ecNumber" && inProtein =>
         proteinEcNumbers.addOne(buffer.mkString)
         next
       case e: StartElement if e.localName == "sequence" =>
         buffer.clear
         sequenceLength = e.findAttribute("length").map(_.value.toInt).getOrElse(0)
         sequenceMass = e.findAttribute("mass").map(_.value.toInt).getOrElse(0)
         sequenceChecksum = e.findAttribute("checksum").map(_.value).getOrElse("")
         sequenceModified = e.findAttribute("modified").map(_.value).map(dateFormat.parse).getOrElse(java.util.Date.from(LocalDate.now().atStartOfDay(ZoneId.systemDefault()).toInstant))
         sequenceVersion = e.findAttribute("version").map(_.value.toInt).getOrElse(0)
         sequencePrecursor = e.findAttribute("precursor").map(_.value).map { case "true" => true case _ => false }
         sequenceFragment = e.findAttribute("fragment").map(_.value).map {
           case "single" => Sequence.FragmentTypeSingle
           case "multiple" => Sequence.FragmentTypeMultiple
         }
         next
       case e: EndElement if e.localName == "sequence" =>
         sequence = Some(Sequence(
           value = buffer.mkString,
           length = sequenceLength,
           mass = sequenceMass,
           checksum = sequenceChecksum,
           modified = sequenceModified,
           version = sequenceVersion,
           precursor = sequencePrecursor,
           fragment = sequenceFragment
         ))
         next
       case t: TextEvent =>
         buffer.addAll(t.text)
         next
       case _ =>
         next

     })
   }
}
