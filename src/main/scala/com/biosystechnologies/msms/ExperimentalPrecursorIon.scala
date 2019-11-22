package com.biosystechnologies.msms

case class ExperimentalPrecursorIon(mz: Double, intensity: Option[Double], collisionEnergy: Option[Double] = None, fragments: Option[List[Ion]]=None)
