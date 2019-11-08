package com.biosystechnologies.msms

case class Ion(mz: Double, intensity: Option[Double]=None, fragments: Option[Array[Ion]]=None) 