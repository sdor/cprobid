package com.biosystechnologies.swissprot

import java.util.Date

case class Entry(
                  dataSet:String,
                  created: Long,
                  modified: Long,
                  version: Int,
                  accessions: List[String],
                  names: List[String],
                  organism: Organism,
                  protein: Protein,
                  sequence: Sequence
                ) {
  def createdDate = new java.util.Date(created)
//  def modifiedDate = modified.map(new java.util.Date(_))
}
