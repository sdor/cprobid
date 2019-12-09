package com.biosystechnologies.swissprot

import java.nio.file.Paths

import akka.Done
import akka.actor.ActorSystem
import akka.stream.scaladsl.{Compression, FileIO, Sink, Source}
import akka.stream.{ActorAttributes, ActorMaterializer, IOResult, Supervision}
import com.typesafe.config.{Config, ConfigFactory}
import org.mongodb.scala.MongoClient
//import reactivemongo.api.bson.collection.BSONCollection
//import reactivemongo.api.{DefaultDB, MongoConnection, MongoDriver}

import scala.concurrent.{ExecutionContext, Future}

object UploadSwissProt extends App {
  val conf: Config = ConfigFactory.load()
  val swissProtPath: String = conf.getString("swissprot.xml")
  val biosysMongoUri = conf.getString("biosys.mongo.uri")
//  implicit val mongoClient: MongoClient = MongoClient(biosysMongoUri)
  implicit val system: ActorSystem = ActorSystem("biosys")
  implicit val materializer: ActorMaterializer = ActorMaterializer()
  implicit val ec: ExecutionContext = system.dispatcher

  val entries: Source[Entry, Future[IOResult]] = FileIO.fromPath(Paths.get(swissProtPath)).via(Compression.gunzip(maxBytesPerChunk = 1024)).via(SwissProt.entries)

  val done = for {
    res <- entries.runWith(Sink.ignore)
  } yield {
    res
  }

  done.transform(
    (_) => {
      system.terminate()
    },
    (e) => {
      e.printStackTrace()
      system.terminate()
      e
    }
  )

  //  val driver = new MongoDriver
//  implicit val system: ActorSystem = ActorSystem("biosys")
//  implicit val materializer: ActorMaterializer = ActorMaterializer()
//  implicit val ec: ExecutionContext = system.dispatcher
//  val decider: Supervision.Decider = {
//    case _                      => Supervision.Resume
//  }
//
//  val database: Future[DefaultDB] = for {
//    uri <- Future.fromTry(MongoConnection.parseURI(biosysTestMongoUri))
//    con <- Future.fromTry(driver.connection(uri,true))
//    dn <- Future(uri.db.get)
//    db <- con.database(dn)
//  } yield db
//
//  val entries: Source[Entry, Future[IOResult]] = FileIO.fromPath(Paths.get(swissProtPath)).via(Compression.gunzip(maxBytesPerChunk = 1024)).via(SwissProt.entries)
//  val done: Future[Done] = for {
//    coll <- database.map(_.collection[BSONCollection]("proteins"))
//    res <- {
//      implicit val c: BSONCollection = coll
//      entries.via(SwissProtEntries.persistor).withAttributes(ActorAttributes.supervisionStrategy(decider)).runWith(Sink.ignore)
//    }
//  } yield res
//
//  done.transform(
//    _ => {
//      println("Done!")
//      driver.close()
//      system.terminate()
//    },
//    (e) => {
//      e.printStackTrace()
//      driver.close()
//      system.terminate()
//      e
//    }
//  )
}
