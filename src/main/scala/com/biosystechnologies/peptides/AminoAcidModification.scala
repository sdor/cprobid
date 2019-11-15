package com.biosystechnologies.peptides

trait AminoAcidModification {
  def name: Option[String]
  def deltaMw: Double
}
