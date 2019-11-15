package com.biosystechnologies.peptides

case class AminoAcidSeq(seq: List[AminoAcid],modifications: List[AminoAcidSeqModification]=List())

object AminoAcidSeq {

    def apply(s: String):AminoAcidSeq = AminoAcidSeq(seq = s"<${s}>".map(AminoAcid.fromChar(_)).toList)
    
    def concat(a: AminoAcidSeq, b: AminoAcidSeq): AminoAcidSeq = {
        val seq = a.seq.take(a.seq.length-1) :++ b.seq.drop(1)
        AminoAcidSeq(seq)
    }
}