package com.biosystechnologies.peptides

case class AminoAcidSeq(seq: Array[AminoAcid],modifications: List[AminoAcidSeqModification]=List())

object AminoAcidSeq {

    def apply(s: String):AminoAcidSeq = AminoAcidSeq(s"<${s}>".map(AminoAcid.fromChar(_)).toArray)
    
    
}