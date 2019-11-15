package com.biosystechnologies.enzymes

import akka.stream.scaladsl.{Sink, Source}
import akka.stream.stage.{GraphStage, GraphStageLogic, InHandler, OutHandler}
import akka.stream._
import com.biosystechnologies.peptides._

import scala.concurrent.{ExecutionContext, Future}

object Trypsin {
  private class Digester extends GraphStage[FlowShape[AminoAcid,AminoAcidSeq]]  {
    val in = Inlet[AminoAcid]("In-AminoAcid")
    val out = Outlet[AminoAcidSeq]("Out-AminoAcidSeq")

    override def createLogic(inheritedAttributes: Attributes): GraphStageLogic = new GraphStageLogic(shape) {
      var peptide: List[AminoAcid] = List()
      setHandler(in, new InHandler {
        override def onPush(): Unit = {
          val aminoAcid = grab(in)
          aminoAcid match {
            case NTerminal if peptide.isEmpty =>
              peptide = peptide :+ NTerminal
              pull(in)
            case NTerminal =>
              val pep = peptide :+ CTerminal
              peptide = List(NTerminal)
              push(out,AminoAcidSeq(seq = pep))
            case CTerminal if peptide.isEmpty =>
              pull(in)
            case CTerminal =>
              val pep = peptide :+ CTerminal
              peptide = List()
              push(out,AminoAcidSeq(seq = pep))
            case Lys =>
              peptide = peptide :+ Lys
              pull(in)
            case Arg =>
              peptide = peptide :+ Arg
              pull(in)
            case Pro =>
              peptide = peptide :+ Pro
              pull(in)
            case aa: AminoAcid if peptide.last == Arg || peptide.last == Lys =>
              val pep = peptide :+ CTerminal
              peptide = List(NTerminal,aa)
              push(out,AminoAcidSeq(seq = pep))
            case aa: AminoAcid =>
              peptide = peptide :+ aa
              pull(in)
          }
        }
      })

      setHandler(out, new OutHandler {
        override def onPull(): Unit = {
          pull(in)
        }
      })
    }

    override def shape: FlowShape[AminoAcid, AminoAcidSeq] = FlowShape(in,out)
  }

  private lazy val digester = new Digester

  private def digest0(aminoAcidSeq: AminoAcidSeq)(implicit materializer: Materializer, ec: ExecutionContext): Future[List[AminoAcidSeq]] = {
    for {
      peptides <- Source(aminoAcidSeq.seq).via(digester).runWith(Sink.seq)
    } yield {
      peptides.toList
    }
  }


  def digest(aminoAcidSeq: AminoAcidSeq, numMissed: Int)(implicit materializer: Materializer, ec: ExecutionContext): Future[List[AminoAcidSeq]] = {
    if(numMissed == 0) {
      digest0(aminoAcidSeq)
    } else {
      for {
        peptides <- digest0(aminoAcidSeq)
      } yield {
         var res = peptides
         for(n <- 1 to numMissed)  {
           res = res :++ peptides.grouped(n+1).filter(list => list.length == n+1).map {
             list =>
               list.fold(AminoAcidSeq(""))((a, b) => {
                 AminoAcidSeq.concat(a, b)
               })
           }.toList
        }
        res
      }
    }
  }

}
