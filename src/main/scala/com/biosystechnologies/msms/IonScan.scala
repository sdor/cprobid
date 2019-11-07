package com.biosystechnologies.msms

trait IonScan {
  lazy val masses = ions.map(_._1)
  def basePeakMz: Double
  def ions: Array[(Double,Double)]


}
