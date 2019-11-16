package com.biosystechnologies.peptides

import com.biosystechnologies.chemical.Hydrogen
import com.biosystechnologies.msms.Ion

case class PeptideIon(charge: Int, monoIsotopicMass: Double) extends Ion {

  override lazy val mz: Double = (monoIsotopicMass + charge * Hydrogen.monoIsotopicMass)/charge

  override def intensity: Option[Double] = None
}
