package com.biosystechnologies.peptides

import com.biosystechnologies.chemical.{Hydrogen, Oxygen}

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
        mass = aminoAcidSeq.seq.slice(1, aminoAcidSeq.seq.length - 1).map(_.monoMw).fold(mass)((a, b) => {
            a + b - waterMonoIsotopicMass
        })
        modificationsMass = aminoAcidSeq.modifications.map(_.modification.deltaMonoIsotopicMw).fold(modificationsMass)(_ + _)
        mass + modificationsMass
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

//    def peptideBIon(aminoAcidSeq: AminoAcidSeq): List[PeptideIon] = {
//        val _monoIsotopicMass = monoIsotopicMass(aminoAcidSeq)
//        expectedIonCharges(aminoAcidSeq).map(PeptideIon(_,_monoIsotopicMass))
//    }

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

    def BandYIons(aminoAcidSeq: AminoAcidSeq) = {
        val seq: Seq[AminoAcid] = aminoAcidSeq.seq
        for(i <- 1 to seq.length) {
            val (bpep, ypep) = seq.splitAt(i)
            var bpepMw: Double = {
                aminoAcidSeq.modifications.find(_.pos == 0).map(_.modification.deltaMonoIsotopicMw).getOrElse(0.0)
            }
            for(aa <- bpep) {
                //TODO: take into account amino acid modifications
                bpepMw = bpepMw + aa.monoMw
            }
            bpepMw = bpepMw - Hydrogen.monoIsotopicMass
        }
    }
}