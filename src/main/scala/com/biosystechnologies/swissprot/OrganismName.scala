package com.biosystechnologies.swissprot

object OrganismName {
  val schema =
    """
      |<xs:complexType name="organismNameType">
      | <xs:annotation>
      |  <xs:documentation>
      |    Describes different types of source organism names.
      |  </xs:documentation>
      | </xs:annotation>
      | <xs:simpleContent>
      |   <xs:extension base="xs:string">
      |     <xs:attribute name="type" use="required">
      |     <xs:simpleType>
      |       <xs:restriction base="xs:string">
      |       <xs:enumeration value="common"/>
      |       <xs:enumeration value="full"/>
      |       <xs:enumeration value="scientific"/>
      |       <xs:enumeration value="synonym"/>
      |       <xs:enumeration value="abbreviation"/>
      |       </xs:restriction>
      |     </xs:simpleType>
      |     </xs:attribute>
      |   </xs:extension>
      | </xs:simpleContent>
      |</xs:complexType
      |""".stripMargin
  sealed trait NameType
  case object NameTypeCommon extends NameType
  case object NameTypeFull extends NameType
  case object NameTypeScientific extends NameType
  case object NameTypeSynonym extends NameType
  case object NameTypeAbbreviation extends NameType
}
case class OrganismName(value: String, nameType: OrganismName.NameType)
