package com.biosystechnologies.msms

case class TheoreticalIon(
                           mz: Double,
                           override val fragments: Option[Array[Ion]]=None
) extends Ion with CIDProduct {
  override def intensity: Option[Double] = None
}