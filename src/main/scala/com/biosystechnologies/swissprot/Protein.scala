package com.biosystechnologies.swissprot

case class Protein(
                    recommendedNames: List[ProteinName] = List(),
                    alternativeNames: List[ProteinName] = List(),
                    submittedNames: List[ProteinName] = List(),
                    allergenName: Option[String] = None,
                    biotechName: Option[String] = None,
                    cdAntigenNames: List[String] = List(),
                    innNames: List[String] = List()
) {

  def name: String = (recommendedNames,alternativeNames,submittedNames) match {
    case (names, _,_) if !names.isEmpty => names.head.fullName
    case (_,names,_)  if !names.isEmpty => names.head.fullName
    case (_,_,names)  if !names.isEmpty => names.head.fullName
    case _ if allergenName.isDefined => allergenName.get
    case _ if biotechName.isDefined => biotechName.get
    case _ if !cdAntigenNames.isEmpty => cdAntigenNames.head
    case _ if !innNames.isEmpty => innNames.head
    case _ => ""
  }

}
