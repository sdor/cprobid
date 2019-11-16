package com.biosystechnologies.peptides

trait AminoAcidModification {
  def name: Option[String]
  def deltaMonoIsotopicMw: Double
  def targets: List[AminoAcid]
  def isTarget(aminoAcid: AminoAcid): Boolean = {
    targets.contains(aminoAcid)
  }
}
