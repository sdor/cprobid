package com.biosystechnologies.msms

import java.awt.event.TextEvent
import java.util.Base64

import akka.NotUsed
import akka.stream.alpakka.xml._
import akka.stream.alpakka.xml.scaladsl.XmlParsing
import akka.stream.scaladsl.Flow
import akka.util.ByteString

object MzXmlParser {
  def parsePeaks(peaks: String, precision: Int = 32):List[ExperimentalIon] = precision match {
    case 32 =>
      ByteString(Base64.getDecoder.decode(peaks)).grouped(8).map {
        bs =>
          val Array(mz, int) = bs.grouped(4).map(_.asByteBuffer.getFloat).toArray
          ExperimentalIon(mz = mz.toDouble, intensity = Some(int.toDouble))
      }.toList
    case 64 =>
      ByteString(Base64.getDecoder.decode(peaks)).grouped(16).map {
        bs =>
          val Array(mz, intensity) = bs.grouped(8).map(_.asByteBuffer.getDouble).toArray
          ExperimentalIon(mz, Some(intensity))
      }.toList
    case _ =>
      ByteString(Base64.getDecoder.decode(peaks)).grouped(8).map {
        bs =>
          val Array(mz, int) = bs.grouped(4).map(_.asByteBuffer.getFloat).toArray
          ExperimentalIon(mz = mz.toDouble, intensity = Some(int.toDouble))
      }.toList
  }
  def scanFlow:Flow[ByteString, MzXmlScan, NotUsed] = {
    Flow[ByteString].via(XmlParsing.parser()).statefulMapConcat( () => {
      val peaksBuffer = new StringBuilder()
      val precursorMzBuffer = new StringBuilder()
      var inScan = false
      var inPeaks = false
      var inPrecursor = false
      var num:               Long = 0
      var msLevel:           Option[Int   ] = None
      var peaksCount:        Option[Int   ] = None
      var retentionTime:     Option[String] = None
      var startMz:           Option[Double] = None
      var endMz:             Option[Double] = None
      var lowMz:             Option[Double] = None
      var highMz:            Option[Double] = None
      var basePeakMz:        Double  = 0.0
      var basePeakIntensity: Option[Double] = None
      var totIonCurrent:     Option[Double] = None
      var peaksPrecision: Int = 32
      var precursorIntensity: Option[Double] = None
      var collisionEnergy: Option[Double] = None
      var precursorIon: Option[ExperimentalPrecursorIon] = None
//      var ions: Array[Ion] = new Array(0)

      event => event match {
        case s: StartElement if s.localName == "scan" =>
          inScan = true
          peaksBuffer.clear()
          precursorMzBuffer.clear()
          num               = s.findAttribute("num").map(_.value.toLong).get
          msLevel           = s.findAttribute("msLevel").map(_.value.toInt)
          peaksCount        = s.findAttribute("peaksCount").map(_.value.toInt)
          retentionTime     = s.findAttribute("retentionTime").map(_.value)
          startMz           = s.findAttribute("startMz").map(_.value.toDouble)
          endMz             = s.findAttribute("endMz").map(_.value.toDouble)
          lowMz             = s.findAttribute("lowMz").map(_.value.toDouble)
          highMz            = s.findAttribute("highMz").map(_.value.toDouble)
          basePeakMz        = s.findAttribute("basePeakMz").map(_.value.toDouble).get
          basePeakIntensity = s.findAttribute("basePeakIntensity").map(_.value.toDouble)
          totIonCurrent     = s.findAttribute("totIonCurrent").map(_.value.toDouble)
          precursorIon = None
          List()
        case e: EndElement if e.localName == "scan" =>
          inScan = false
          val ions = parsePeaks(peaksBuffer.result(),peaksPrecision)
          List(MzXmlScan(
            num = num,
            msLevel = msLevel,
            peaksCount = peaksCount,
            retentionTime = retentionTime,
            startMz = startMz,
            endMz = endMz,
            lowMz = lowMz,
            highMz = highMz,
            basePeakMz = basePeakMz,
            basePeakIntensity = basePeakIntensity,
            totIonCurrent = totIonCurrent,
            peaksPrecision = peaksPrecision,
            precursorIon = precursorIon,
            ions = ions
          ))
//          if(peaksPrecision == 32) {
//            ions = ByteString(Base64.getDecoder.decode(peaksBuffer.result())).grouped(8).map {
//              bs =>
//                val Array(mz, int) = bs.grouped(4).map(_.asByteBuffer.getFloat).toArray
//                ExperimentalIon(mz = mz.toDouble, intensity = Some(int.toDouble))
//            }.toArray
//            List(MzXmlScan(
//              num = num,
//              msLevel = msLevel,
//              peaksCount = peaksCount,
//              retentionTime = retentionTime,
//              startMz = startMz,
//              endMz = endMz,
//              lowMz = lowMz,
//              highMz = highMz,
//              basePeakMz = basePeakMz,
//              basePeakIntensity = basePeakIntensity,
//              totIonCurrent = totIonCurrent,
//              peaksPrecision = peaksPrecision,
//              ions = ions
//            ))
//          } else if(peaksPrecision == 64) {
//            ions = ByteString(Base64.getDecoder.decode(peaksBuffer.result())).grouped(16).map {
//              bs =>
//                val Array(mz, intensity) = bs.grouped(8).map(_.asByteBuffer.getDouble).toArray
//                ExperimentalIon(mz, Some(intensity))
//            }.toArray
//            List(MzXmlScan(
//              num = num,
//              msLevel = msLevel,
//              peaksCount = peaksCount,
//              retentionTime = retentionTime,
//              startMz = startMz,
//              endMz = endMz,
//              lowMz = lowMz,
//              highMz = highMz,
//              basePeakMz = basePeakMz,
//              basePeakIntensity = basePeakIntensity,
//              totIonCurrent = totIonCurrent,
//              peaksPrecision = peaksPrecision,
//              ions = ions
//            ))
//          } else {
//            List()
//          }
        case e: StartElement if e.localName == "peaks" =>
          inPeaks = true
          peaksPrecision = e.findAttribute("precision").map(_.value.toInt).getOrElse(32)
          List()
        case e:EndElement if e.localName == "peaks" =>
          inPeaks=false
          List()
        case e: StartElement if e.localName == "precursorMz" =>
          inPrecursor = true
//          precursorMzBuffer.clear()
          precursorIntensity = e.findAttribute("precursorIntensity").map(_.value.toDouble)
          collisionEnergy = e.findAttribute("collisionEnergy").map(_.value.toDouble)
          List()
        case e: EndElement if e.localName == "precursorMz" =>
          inPrecursor = false
          val precursorMz: Double = precursorMzBuffer.result().toDouble
          precursorIon=Some(ExperimentalPrecursorIon(mz=precursorMz,intensity = precursorIntensity,collisionEnergy = collisionEnergy))
          List()
        case t: TextEvent if inPrecursor =>
          precursorMzBuffer.append(t)
          List()
        case t:TextEvent if inScan && inPeaks =>
          peaksBuffer.append(t)
          List()
        case _ =>
          List()
      }
    })


  }


}