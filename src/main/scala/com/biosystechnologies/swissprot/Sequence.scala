package com.biosystechnologies.swissprot

import java.util.Date

object Sequence {
  sealed trait FragmentType
  case object FragmentTypeSingle extends FragmentType
  case object FragmentTypeMultiple extends FragmentType
}

case class Sequence(value: String, length:Int, mass:Int, checksum: String, modified: Date, version:Int, precursor: Option[Boolean] = None, fragment: Option[Sequence.FragmentType])
