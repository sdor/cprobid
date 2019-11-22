package com.biosystechnologies.msms

import scala.xml.XML

case class MzXmlScan (
  num:               Long,
  msLevel:           Option[Int] = None,
  peaksCount:        Option[Int] = None,
  retentionTime:     Option[String] = None,
  startMz:           Option[Double] = None,
  endMz:             Option[Double] = None,
  lowMz:             Option[Double] = None,
  highMz:            Option[Double] = None,
  basePeakMz:        Double,
  basePeakIntensity: Option[Double] = None,
  totIonCurrent:     Option[Double] = None,
  peaksPrecision: Int,
  precursorIon: Option[ExperimentalPrecursorIon] = None,
  ions: List[ExperimentalIon]
)  extends IonScan
