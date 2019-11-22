package com.biosystechnologies.msms

trait IonScan {
  def startMz: Option[Double]
  def endMz: Option[Double]
  def precursorIon: Option[ExperimentalPrecursorIon]
  def ions: List[Ion]
}

object IonScan {
  implicit def toExperimentalPrecursorIon(scan: IonScan): Option[ExperimentalPrecursorIon] = {
    scan.precursorIon.map {
      precursorIon =>
        precursorIon.copy(fragments = Some(scan.ions))
    }
  }
}
