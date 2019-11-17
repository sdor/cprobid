package com.biosystechnologies.peptides

import com.biosystechnologies.msms.Ion

case class ImmoniumIon(mz: Double) extends Ion {
  override val intensity: Option[Double] = None
}
