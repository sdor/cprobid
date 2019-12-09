package com.biosystechnologies.swissprot

import java.nio.file.Paths

import akka.actor.ActorSystem
import akka.stream.{ActorMaterializer, IOResult}
import akka.stream.scaladsl.{Compression, FileIO, Sink, Source}
import akka.testkit.{TestKit}
import com.typesafe.config.{Config, ConfigFactory}
import org.scalatest.{BeforeAndAfterAll, FlatSpecLike, Matchers}

import scala.concurrent.{Await, Future}
import scala.concurrent.duration._

class SwissProtTest extends TestKit(ActorSystem("test")) with FlatSpecLike with Matchers with BeforeAndAfterAll {

  behavior of "SwissProtTest"

  val conf: Config = ConfigFactory.load()
  val swissProtPath: String = conf.getString("swissprot.xml")
  implicit val materializer: ActorMaterializer = ActorMaterializer()


  override def afterAll: Unit = {
    TestKit.shutdownActorSystem(system)
  }

  it should "stream entries" in {
    val entries: Source[Entry, Future[IOResult]] = FileIO.fromPath(Paths.get(swissProtPath)).via(Compression.gunzip(maxBytesPerChunk = 1024)).via(SwissProt.entries)
    val futureEntry = entries.take(10).runWith(Sink.head)
    Await.ready(futureEntry, 3.seconds)
    futureEntry.value.map(_.toOption.map(_.accessions).get).get should contain("Q6GZX4")
  }

}
