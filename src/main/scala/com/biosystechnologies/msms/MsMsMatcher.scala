package com.biosystechnologies.msms

import com.typesafe.config.ConfigFactory
import scala.math.{abs}
object MsMsMatcher {
   val msms_epsilon = {
     val config = ConfigFactory.load()
     config.getDouble("msms_pipeline.msms_epsilon")
   }



  //  def numMatchMsMsScans(a: IonScan, b: IonScan) = {
  //    val matchMissMatch: Array[Array[(Double, Boolean)]] = a.masses.map {
  //      a_mass =>
  //        b.masses.map {
  //          b_mass =>
  //            abs(a_mass - b_mass) <= msms_epsilon
  //        }.map((a_mass,_))
  //    }
  //  }
}
