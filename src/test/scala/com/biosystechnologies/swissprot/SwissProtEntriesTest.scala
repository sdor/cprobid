package com.biosystechnologies.swissprot

import java.nio.file.Paths

import akka.actor.ActorSystem
import akka.stream.scaladsl.{Compression, FileIO, Sink, Source}
import akka.stream.{ActorMaterializer, IOResult}
import akka.testkit.TestKit
import com.typesafe.config.{Config, ConfigFactory}
import org.mongodb.scala.MongoClient
import org.scalatest.{AsyncFlatSpecLike, BeforeAndAfterAll, FlatSpec, Matchers}
//import reactivemongo.api.bson.collection.BSONCollection
//import reactivemongo.api.{DefaultDB, MongoConnection, MongoDriver}

import scala.concurrent.Future

class SwissProtEntriesTest extends TestKit(ActorSystem("test")) with AsyncFlatSpecLike with BeforeAndAfterAll with Matchers {

  behavior of "SwissProtEntriesTest"
  val conf: Config = ConfigFactory.load()
  val swissProtPath: String = conf.getString("swissprot.xml")
  val biosysTestMongoUri = conf.getString("biosys.test.mongo.uri")
  implicit val mongoClient: MongoClient = MongoClient(biosysTestMongoUri)

//  val driver = new MongoDriver
  implicit val materializer: ActorMaterializer = ActorMaterializer()
//
//  val database: Future[DefaultDB] = for {
//    uri <- Future.fromTry(MongoConnection.parseURI(biosysTestMongoUri))
//    con <- Future.fromTry(driver.connection(uri,true))
//    dn <- Future(uri.db.get)
//    db <- con.database(dn)
//  } yield db
//
//  override def afterAll: Unit = {
//
//    driver.close()
//    TestKit.shutdownActorSystem(system)
//  }
//
//  it should "save entry to mongo database" in {
//    val entries: Source[Entry, Future[IOResult]] = FileIO.fromPath(Paths.get(swissProtPath)).via(Compression.gunzip(maxBytesPerChunk = 1024)).via(SwissProt.entries)
//    for {
//      coll <- database.map(_.collection[BSONCollection]("proteins"))
//      res <- {
//        implicit val c = coll
//        entries.take(10).via(SwissProtEntries.persistor).runWith(Sink.seq)
//      }
//    } yield {
//      res.map(_.n).fold(0)(_ + _) should be(10)
//    }
//  }

  it should "save entries" in {
    val entries: Source[Entry, Future[IOResult]] = FileIO.fromPath(Paths.get(swissProtPath)).via(Compression.gunzip(maxBytesPerChunk = 1024)).via(SwissProt.entries).take(10)
    for {
      res <- SwissProtEntries.persist(entries,"test")
    } yield {
      (res._1 + res._2) should be(10)
    }

  }

}
