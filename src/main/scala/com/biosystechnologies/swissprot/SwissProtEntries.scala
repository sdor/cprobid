package com.biosystechnologies.swissprot

import java.lang
import java.util.Date

import akka.stream._
import akka.stream.scaladsl._
import org.bson.codecs.configuration.{CodecProvider, CodecRegistries, CodecRegistry}
import org.bson.{BsonReader, BsonType, BsonWriter}
import org.bson.codecs.{Codec, DecoderContext, EncoderContext}
import org.mongodb.scala.MongoClient
import org.mongodb.scala.bson.codecs.{DEFAULT_CODEC_REGISTRY, Macros}
import org.mongodb.scala.model._
import org.mongodb.scala.model.Filters._
import org.bson.codecs.configuration.CodecRegistries.{fromProviders, fromRegistries}

import scala.language.implicitConversions
import scala.concurrent._

object SwissProtEntries {
  //  import reactivemongo.bson._
  //
  //  implicit object FragmentTypeReader extends BSONReader[BSONValue, Sequence.FragmentType] {
  //    def read(bson: BSONValue): Sequence.FragmentType = bson match {
  //      case v:BSONString if v.value == "single" => Sequence.FragmentTypeSingle
  //      case v:BSONString if v.value == "multiple" => Sequence.FragmentTypeMultiple
  //      case _ => Sequence.FragmentTypeUnknown
  //    }
  //  }
  //
  //  implicit object FragmentTypeWriter extends BSONWriter[Sequence.FragmentType, BSONString] {
  //    def write(fragment: Sequence.FragmentType): BSONString = fragment match {
  //      case Sequence.FragmentTypeSingle => BSONString("single")
  //      case Sequence.FragmentTypeMultiple => BSONString("multiple")
  //      case _ => BSONString("unknown")
  //    }
  //  }
  //
  //  implicit object organismNameTypeWriter extends BSONWriter[OrganismName.NameType, BSONString] {
  //    def write(name: OrganismName.NameType): BSONString = name match {
  //      case OrganismName.NameTypeCommon => BSONString("common")
  //      case OrganismName.NameTypeFull => BSONString("full")
  //      case OrganismName.NameTypeScientific => BSONString("scientific")
  //      case OrganismName.NameTypeSynonym => BSONString("synonym")
  //      case OrganismName.NameTypeAbbreviation => BSONString("abbreviation")
  //      case _ => BSONString("unknown")
  //    }
  //  }
  //
  //  implicit object organismNameTypeReader extends BSONReader[BSONValue,OrganismName.NameType] {
  //    def read(bson: BSONValue): OrganismName.NameType = bson match {
  //      case BSONString("common") => OrganismName.NameTypeCommon
  //      case BSONString("full") =>  OrganismName.NameTypeFull
  //      case BSONString("scientific") => OrganismName.NameTypeScientific
  //      case BSONString("synonym") => OrganismName.NameTypeSynonym
  //      case BSONString("abbreviation") => OrganismName.NameTypeAbbreviation
  //      case _ => OrganismName.NameTypeUnknown
  //    }
  //  }
  //
  //  implicit val dbReferenceHandler: BSONDocumentHandler[DbReference] = Macros.handler[DbReference]
  //  implicit val organismNameHandler: BSONDocumentHandler[OrganismName] = Macros.handler[OrganismName]
  //  implicit val organismHandler: BSONDocumentHandler[Organism] = Macros.handler[Organism]
  //  implicit val proteinNameHandler: BSONDocumentHandler[ProteinName] = Macros.handler[ProteinName]
  //  implicit val proteinHandler: BSONDocumentHandler[Protein] = Macros.handler[Protein]
  //  implicit val sequenceHandler: BSONDocumentHandler[Sequence] = Macros.handler[Sequence]
  //
  //  implicit val entryHandler = Macros.handler[Entry]

  //  def create(entry: Entry)(implicit coll: BSONCollection, ec: ExecutionContext):Future[WriteResult] = {
  //    coll.insert.one(entry)
  //  }

  //  def save(entry: Entry)(implicit coll: BSONCollection, ec: ExecutionContext): Future[UpdateWriteResult] = {
  //    val accession = entry.accessions.head
  //    val selector = BSONDocument("accessions" -> accession)
  //    val modifier = BSONDocument("$set"-> entry)
  //    coll.update.one(q = selector,u = modifier,upsert = true,multi = false)
  //  }
  //
  //
  //
  //  def persistor()(implicit coll: BSONCollection, ec: ExecutionContext) = {
  //        Flow[Entry].mapAsync(1)(save)
  //  }
//  class someDateCodec extends Codec[Some[Date]] {
//    override def encode(writer: BsonWriter, value: Some[Date], encoderContext: EncoderContext): Unit = value match {
//      case Some(v: Date)  => writer.writeDateTime(v.getTime)
//    }
//
//    override def getEncoderClass: Class[Some[Date]] = classOf[Some[Date]]
//
//    override def decode(reader: BsonReader, decoderContext: DecoderContext): Some[Date] = {
//      reader.getCurrentBsonType match {
//        case BsonType.INT64 =>
//          val value = reader.readInt64()
//          Some(new java.util.Date(value))
//      }
//    }
//  }

//  class OrganismNameTypeCodec extends Codec[NameTypeScientific] {
//    override def encode(writer: BsonWriter, value: OrganismName.NameType, encoderContext: EncoderContext): Unit = value match {
//      case OrganismName.NameTypeCommon => writer.writeString("common")
//      case OrganismName.NameTypeFull => writer.writeString("full")
//      case OrganismName.NameTypeScientific => writer.writeString("scientific")
//      case OrganismName.NameTypeSynonym => writer.writeString("synonym")
//      case OrganismName.NameTypeAbbreviation => writer.writeString("abbreviation")
//      case OrganismName.NameTypeUnknown => writer.writeString("unknown")
//    }
//
//    override def getEncoderClass: Class[OrganismName.NameType] = classOf[OrganismName.NameType]
//
//    override def decode(reader: BsonReader, decoderContext: DecoderContext): OrganismName.NameType =  {
//         reader.getCurrentBsonType match {
//           case BsonType.STRING =>
//             reader.readString() match {
//               case "common"       => OrganismName.NameTypeCommon
//               case "full"         => OrganismName.NameTypeFull
//               case "scientific"   => OrganismName.NameTypeScientific
//               case "synonym"      => OrganismName.NameTypeSynonym
//               case "abbreviation" => OrganismName.NameTypeAbbreviation
//               case "unknown"      => OrganismName.NameTypeUnknown
//               case _               => OrganismName.NameTypeUnknown
//             }
//           case _ =>  OrganismName.NameTypeUnknown
//         }
//    }
//  }

//  val organismNameTypeCodecRegistry: CodecRegistry = CodecRegistries.fromCodecs(new OrganismNameTypeCodec)

  val organismNameCodecProvider: CodecProvider = Macros.createCodecProvider[OrganismName]()

  val dbReferenceCodecProvider: CodecProvider = Macros.createCodecProvider[DbReference]()

  val organismCodecProvider: CodecProvider = Macros.createCodecProvider[Organism]()

  val proteinNameCodecProvider: CodecProvider = Macros.createCodecProvider[ProteinName]()

  val proteinCodecProvider: CodecProvider = Macros.createCodecProvider[Protein]()

  val sequenceCodecProvider: CodecProvider = Macros.createCodecProvider[Sequence]()

  val entryCodecProvider: CodecProvider = Macros.createCodecProviderIgnoreNone[Entry]()

  val codecRegistry: CodecRegistry = fromRegistries(
//    organismNameTypeCodecRegistry,
    fromProviders(
      organismNameCodecProvider,
      dbReferenceCodecProvider,
      organismCodecProvider,
      proteinNameCodecProvider,
      proteinCodecProvider,
      sequenceCodecProvider,
      entryCodecProvider
    )
  , DEFAULT_CODEC_REGISTRY)


  private def db(name: String)(implicit client: MongoClient) = client.getDatabase(name)


  def persist(source: Source[Entry,_], databaseName: String)(implicit client: MongoClient, materializer: Materializer, executionContext: ExecutionContext): Future[(Long, Long)] = {

    val proteins = db(databaseName).withCodecRegistry(codecRegistry).getCollection("proteins")

    val options = new UpdateOptions().upsert(true)

    def save(entry: Entry) = {
      val filter = and(in("accessions", entry.accessions), equal("version", entry.version))
      val update = Updates.combine(
        Updates.set("dataSet", entry.dataSet),
        Updates.set("created", entry.created),
        Updates.set("modified", entry.modified),
        Updates.set("accessions", entry.accessions),
        Updates.set("names", entry.names),
        Updates.set("organism", entry.organism),
        Updates.set("protein", entry.protein),
        Updates.set("sequence", entry.sequence)
      )
      proteins.updateOne(filter,update,options).toFuture()
    }

    source.mapAsync(1) {
      entry =>
        for {
          res <- save(entry)
        } yield {
          if(res.getMatchedCount == 0) {
            (1L,0L)
          } else {
            (0L,res.getMatchedCount.toLong)
          }
        }
    }.runWith(Sink.fold((0L,0L))((a,b) => {
      (a,b) match {
        case ((s1, s2), (n1, n2)) => (s1 + n1, s2 + n2)
      }
    }))

  }


}
