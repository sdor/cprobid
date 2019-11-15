package com.biosystechnologies.enzymes

import akka.actor.ActorSystem
import akka.stream.ActorMaterializer
import com.biosystechnologies.peptides.{Ala, AminoAcidSeq, Arg, CTerminal, Leu, Lys, Met, NTerminal, Pro, Ser, Tyr, Val}
import org.scalatest.{AsyncFlatSpec, BeforeAndAfterAll, Matchers}

class TrypsinTest extends AsyncFlatSpec with Matchers with BeforeAndAfterAll {
   implicit val system = ActorSystem("trypsin-test")
   implicit val materializer = ActorMaterializer()

//  override def afterAll(): Unit = {
//    system.terminate()
//  }

   "Trypsin" should "digest amino acid sequence" in {
     val aminoAcidSeq = AminoAcidSeq("MAAARLLLKVVVRPSSSKPYYYRA")
     for {
       digest <- Trypsin.digest(aminoAcidSeq,0)
     } yield {
       digest should equal(List(
         AminoAcidSeq(List(NTerminal, Met, Ala, Ala, Ala, Arg, CTerminal),List()),
         AminoAcidSeq(List(NTerminal, Leu, Leu, Leu, Lys, CTerminal),List()),
         AminoAcidSeq(List(NTerminal, Val, Val, Val, Arg, Pro, Ser, Ser, Ser, Lys, Pro, Tyr, Tyr, Tyr,Arg, CTerminal),List()),
         AminoAcidSeq(List(NTerminal,Ala,CTerminal))
       ))
     }
   }

   it should "digest amino acid sequence with missing sites" in {
     val aminoAcidSeq = AminoAcidSeq("MAAARLLLKVVVRPSSSKPYYYRA")
     for {
       digest <- Trypsin.digest(aminoAcidSeq,  1)
     } yield {
       digest should equal(List(
         AminoAcidSeq(List(NTerminal, Met, Ala, Ala, Ala, Arg, CTerminal),List()),
         AminoAcidSeq(List(NTerminal, Leu, Leu, Leu, Lys, CTerminal),List()),
         AminoAcidSeq(List(NTerminal, Val, Val, Val, Arg, Pro, Ser, Ser, Ser, Lys, Pro, Tyr, Tyr, Tyr,Arg, CTerminal),List()),
         AminoAcidSeq(List(NTerminal,Ala,CTerminal)),
         AminoAcidSeq(List(NTerminal, Met, Ala, Ala, Ala, Arg, Leu, Leu, Leu, Lys, CTerminal)),
         AminoAcidSeq(List(NTerminal, Leu, Leu, Leu, Lys, Val, Val, Val, Arg, Pro, Ser, Ser, Ser, Lys, Pro, Tyr, Tyr, Tyr,Arg, CTerminal),List()),
       ))
     }
   }
}
