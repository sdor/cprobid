package com.biosystechnologies.swissprot

object OrganismName {
//  sealed trait NameType
//  case object NameTypeCommon extends NameType
//  case object NameTypeFull extends NameType
//  case object NameTypeScientific extends NameType
//  case object NameTypeSynonym extends NameType
//  case object NameTypeAbbreviation extends NameType
//  case object NameTypeUnknown extends NameType
}
case class OrganismName(value: String, nameType: String)
