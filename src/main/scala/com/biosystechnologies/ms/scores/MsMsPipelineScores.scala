package com.biosystechnologies.ms.scores

import com.biosystechnologies.msms.IonScan
import com.biosystechnologies.peptides.{AminoAcidSeq, CIDFragments}

object MsMsPipelineScores {
//    def compute(ionScan: IonScan, aminoAcidSeq: AminoAcidSeq, pipelineParams: MsMsPipelineParams): MsMsPipelineScore = {
//      val cid = {
//        val _cid = AminoAcidSeq.cid(aminoAcidSeq)
//        (ionScan.startMz, ionScan.endMz) match {
//          case (Some(startMz), Some(endMz)) =>
//            val immoniumIons =_cid.immoniumIons.filter(ion => ion.mz >= startMz && ion.mz <= endMz)
//            val bIons = _cid.bIons.filter(ion => ion.mz >= startMz && ion.mz <= endMz)
//            val yIons = _cid.yIons.filter(ion => ion.mz >= startMz && ion.mz <= endMz)
//            _cid.copy(bIons = bIons, yIons = yIons, immoniumIons = immoniumIons)
//          case _ => _cid
//        }
//      }
//
//      //Compute immonium score
//     val immoniumScore = cid match  {
//        case CIDFragments(_,_,_,List()) => 1E-6
//        case CIDFragments(_,_,_,peptideImmoniumIons) =>
//          val n: Int = peptideImmoniumIons.length
//          var numFound: Int = 0
//          for(peptideImmoniumIon <- peptideImmoniumIons) {
//            val found = ionScan.ions.find(ion => (peptideImmoniumIon.mz - ion.mz).abs >= pipelineParams.immoniumIonsError)
//            if(found.isDefined){
//              numFound = numFound + 1
//            }
//          }
//          (numFound / n).toDouble
//      }
//
//
//
//
//    }
}
