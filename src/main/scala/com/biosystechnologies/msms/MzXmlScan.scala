package com.biosystechnologies.msms

import scala.xml.XML

case class MzXmlScan (
  num:               Long,
  msLevel:           Option[Int] = None,
  peaksCount:        Option[Int] = None,
  retentionTime:     Option[String] = None,
  startMz:           Option[Float] = None,
  endMz:             Option[Float] = None,
  lowMz:             Option[Float] = None,
  highMz:            Option[Float] = None,
  basePeakMz:        Double,
  basePeakIntensity: Option[Float] = None,
  totIonCurrent:     Option[Float] = None,
  peaksPrecision: Int,
  ions: Array[Ion]
)  extends IonScan
