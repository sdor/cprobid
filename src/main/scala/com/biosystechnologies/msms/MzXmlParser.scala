package com.biosystechnologies.msms

import java.awt.event.TextEvent
import java.util.Base64

import akka.NotUsed
import akka.stream.alpakka.xml._
import akka.stream.alpakka.xml.scaladsl.XmlParsing
import akka.stream.scaladsl.Flow
import akka.util.ByteString

object MzXmlParser {

  def scanFlow:Flow[ByteString, MzXmlScan, NotUsed] = {
    Flow[ByteString].via(XmlParsing.parser()).statefulMapConcat( () => {
      val peaksBuffer = new StringBuilder()
      var inScan = false
      var inPeaks = false
      var num:               Long = 0
      var msLevel:           Option[Int   ] = None
      var peaksCount:        Option[Int   ] = None
      var retentionTime:     Option[String] = None
      var startMz:           Option[Float ] = None
      var endMz:             Option[Float ] = None
      var lowMz:             Option[Float ] = None
      var highMz:            Option[Float ] = None
      var basePeakMz:        Double  = 0.0
      var basePeakIntensity: Option[Float ] = None
      var totIonCurrent:     Option[Float ] = None
      var peaksPrecision: Int = 32
      var ions: Array[Ion] = new Array(0)

      event => event match {
        case s: StartElement if s.localName == "scan" =>
          inScan = true
          peaksBuffer.clear()
          num               = s.findAttribute("num").map(_.value.toLong).get
          msLevel           = s.findAttribute("msLevel").map(_.value.toInt)
          peaksCount        = s.findAttribute("peaksCount").map(_.value.toInt)
          retentionTime     = s.findAttribute("retentionTime").map(_.value)
          startMz           = s.findAttribute("startMz").map(_.value.toFloat)
          endMz             = s.findAttribute("endMz").map(_.value.toFloat)
          lowMz             = s.findAttribute("lowMz").map(_.value.toFloat)
          highMz            = s.findAttribute("highMz").map(_.value.toFloat)
          basePeakMz        = s.findAttribute("basePeakMz").map(_.value.toDouble).get
          basePeakIntensity = s.findAttribute("basePeakIntensity").map(_.value.toFloat)
          totIonCurrent     = s.findAttribute("totIonCurrent").map(_.value.toFloat)
          List()
        case e: EndElement if e.localName == "scan" =>
          inScan = false
          if(peaksPrecision == 32) {
            ions = ByteString(Base64.getDecoder.decode(peaksBuffer.result())).grouped(8).map {
              bs =>
                val Array(mz, int) = bs.grouped(4).map(_.asByteBuffer.getFloat).toArray
                Ion(mz = mz.toDouble, intensity = Some(int.toDouble))
            }.toArray
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
              ions = ions
            ))
          } else if(peaksPrecision == 64) {
            ions = ByteString(Base64.getDecoder.decode(peaksBuffer.result())).grouped(16).map {
              bs =>
                val Array(mz, intensity) = bs.grouped(8).map(_.asByteBuffer.getDouble).toArray
                Ion(mz, Some(intensity))
            }.toArray
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
              ions = ions
            ))
          } else {
            List()
          }
        case e: StartElement if e.localName == "peaks" =>
          inPeaks = true
          peaksPrecision = e.findAttribute("precision").map(_.value.toInt).getOrElse(32)
          List()
        case e:EndElement if e.localName == "peaks" =>
          inPeaks=false
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
