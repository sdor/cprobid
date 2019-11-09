package com.biosystechnologies.msms

trait Ion {
  def mz: Double
  def intensity: Option[Double]
}