package com.biosystechnologies.peptides

import com.biosystechnologies.chemical.{Hydrogen, Oxygen}

import scala.collection.mutable

case class AminoAcidSeq(seq: List[AminoAcid],modifications: List[AminoAcidSeqModification]=List())

object AminoAcidSeq {

    private val waterMonoIsotopicMass = {
        2*Hydrogen.monoIsotopicMass + Oxygen.monoIsotopicMass
    }
    def apply(s: String):AminoAcidSeq = AminoAcidSeq(seq = s"<${s}>".map(AminoAcid.fromChar(_)).toList)
    
    def concat(a: AminoAcidSeq, b: AminoAcidSeq): AminoAcidSeq = {
        val seq = a.seq.take(a.seq.length-1) :++ b.seq.drop(1)
        AminoAcidSeq(seq)
    }

    def monoIsotopicMass(aminoAcidSeq: AminoAcidSeq): Double = {
        var mass: Double = 0.0
        var modificationsMass = 0.0
        for(aa <- aminoAcidSeq.seq) {
            mass = mass + aa.monoMw
        }
        modificationsMass = aminoAcidSeq.modifications.map(_.modification.deltaMonoIsotopicMw).fold(modificationsMass)(_ + _)
        mass + modificationsMass + waterMonoIsotopicMass
    }

    def modifiedAt(aminoAcidSeq: AminoAcidSeq, pos: Int):Boolean = {
        aminoAcidSeq.modifications.exists(_.pos == pos)
    }

    def expectedIonCharges(aminoAcidSeq: AminoAcidSeq): List[Int] = {
        var numProtonSites: Int = 0;
        var pos = 0
        numProtonSites = aminoAcidSeq.seq.map {
            aa =>
              val site: Int =  aa match {
                    case NTerminal if modifiedAt(aminoAcidSeq, 0) => 0
                    case NTerminal => 1
                    case Lys if modifiedAt(aminoAcidSeq, pos ) => 0
                    case Lys => 1
                    case Arg => 1
                    case His => 1
                    case _ => 0
                }
            pos = pos + 1
            site
        }.fold(numProtonSites)(_ + _)
        Range(1,numProtonSites,1).toList
    }


    def immoniumIons(aminoAcidSeq: AminoAcidSeq): List[ImmoniumIon] = {
        import ImmoniumCod._
        var immoniumCods: Set[ImmoniumCod] = Set()
        for(aa <- aminoAcidSeq.seq) {
            val immoniumCod: ImmoniumCod = aa
            immoniumCod match {
                case NTerminalImmoniumCod =>
                case CTerminalImmoniumCod =>
                case UnknownImmoniumCod =>
                case cod =>
                    immoniumCods = immoniumCods + cod
            }
        }
        immoniumCods.iterator.flatMap {
            cod =>
                val immoniumIonsList: List[ImmoniumIon] = cod
                immoniumIonsList
        }.toList
    }

    def cid(aminoAcidSeq: AminoAcidSeq) = {
        val seq: Seq[AminoAcid] = aminoAcidSeq.seq
        val peptideMw = AminoAcidSeq.monoIsotopicMass(aminoAcidSeq)
        val bIons: mutable.ArrayBuffer[PeptideIon] = new mutable.ArrayBuffer[PeptideIon]()
        val yIons: mutable.ArrayBuffer[PeptideIon] = new mutable.ArrayBuffer[PeptideIon]()
        for(i <- 2 to seq.length - 2) {
            val (bpep, ypep) = seq.splitAt(i)

            var bpepMw: Double = {
                aminoAcidSeq.modifications.find(_.pos == 0).map(_.modification.deltaMonoIsotopicMw).getOrElse(0.0)
            }
            for(aa <- bpep) {
                //TODO: take into account amino acid modifications
                bpepMw = bpepMw + aa.monoMw
            }

            bIons.addOne(PeptideIon(1,monoIsotopicMass = bpepMw))

            //TODO: c-terminal modification
            var ypepMw: Double = {
                0.0
            }
            for(aa <- ypep) {
                //TODO: take into account amino acid modifications
                ypepMw = ypepMw + aa.monoMw
            }

            yIons.addOne(PeptideIon(1,monoIsotopicMass = ypepMw + waterMonoIsotopicMass))
        }
        bIons.addOne(PeptideIon(1,monoIsotopicMass = peptideMw - waterMonoIsotopicMass))
        CIDFragments(precursor = PeptideIon(1,peptideMw),bIons=bIons.toList, yIons = yIons.toList, immoniumIons = immoniumIons(aminoAcidSeq))
    }


}