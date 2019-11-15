package com.biosystechnologies.peptides

import org.scalatest.{FlatSpec, Matchers}

class AminoAcidSeqTest extends FlatSpec with Matchers {

     "AminoAcidSeq" should "be created from string" in {
       val aminoAcidSeq = AminoAcidSeq("LPG")
       aminoAcidSeq should equal(AminoAcidSeq(List(NTerminal, Leu, Pro, Gly, CTerminal)))
     }

    it should "create empty amino acid sequence" in {
      val aminoAcidSeq = AminoAcidSeq("")
      aminoAcidSeq should equal(AminoAcidSeq(List(NTerminal,CTerminal)))
    }

    it should "concat amino acid sequences" in {
      val aminoAcidSeq = AminoAcidSeq.concat(AminoAcidSeq("AAA"),AminoAcidSeq("LLL"))
      aminoAcidSeq should equal(AminoAcidSeq(List(NTerminal, Ala, Ala, Ala, Leu, Leu, Leu, CTerminal)))
    }
}
