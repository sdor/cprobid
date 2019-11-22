package com.biosystechnologies.msms

case class ExperimentalIon(
  mz: Double,
  intensity: Option[Double],
  fragments: Option[List[Ion]]=None
) extends Ion