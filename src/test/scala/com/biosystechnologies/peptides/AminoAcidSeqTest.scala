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

    it should "have collision induced dissociation fragments" in {
      val aminoAcidSeq = AminoAcidSeq("PEPTIDE")
      val fragments = AminoAcidSeq.cid(aminoAcidSeq)
      fragments.precursor.mz should equal(800.367769735)
      fragments.bIons.map(_.mz) should equal(List(98.060585035, 227.103175035, 324.15593503499997, 425.203615035, 538.287675035, 653.314615035, 782.357205035))
      fragments.yIons.map(_.mz) should equal(List(703.315009735, 574.272419735, 477.219659735, 376.171979735, 263.08791973499996, 148.060979735))
    }
}
//b - List(98.060585035, 227.103175035, 324.15593503499997, 425.203615035, 538.287675035, 653.314615035)
//y - List(703.315009735, 574.272419735, 477.219659735, 376.171979735, 263.08791973499996, 148.060979735)
//List(97.05276, 226.09535, 323.14811, 424.19579, 537.27985, 652.30679)
//P     1     98.06009    800.36728    7
//E     2    227.10268    703.31452    6
//P     3    324.15544    574.27193    5
//T     4    425.20312    477.21916    4
//I     5    538.28718    376.17149    3
//D     6    653.31413    263.08742    2
//E     7    782.35672    148.06048    1


// (M)	    799.36001	799.83277
// (M+H)+	  800.36728	800.84004
// (M+2H)2+	400.68730	400.92368
// (M+3H)3+	267.46064	267.61823
// (M+4H)4+	200.84731	200.96550