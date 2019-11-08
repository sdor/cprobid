package com.biosystechnologies.msms

trait IonScan {
  def basePeakMz: Double
  def basePeakIntensity: Option[Float]
  def ions: Array[Ion]
}
