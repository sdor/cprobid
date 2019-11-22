package com.biosystechnologies.ms.scores

sealed trait MsScore {
   def precursorMatchScore: Option[Double]
   def matchScore: Option[Double]
   def immoniumScore: Option[Double]
}

case class MsMsPipelineScore(precursorMatchScore: Option[Double] = None, matchScore: Option[Double], immoniumScore: Option[Double]) extends MsScore
