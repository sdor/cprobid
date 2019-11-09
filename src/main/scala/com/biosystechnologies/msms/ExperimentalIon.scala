package com.biosystechnologies.msms

case class ExperimentalIon(
                            mz: Double,
                            override val intensity: Option[Double],
                            override val fragments: Option[Array[Ion]]=None
                          ) extends Ion with CIDProduct