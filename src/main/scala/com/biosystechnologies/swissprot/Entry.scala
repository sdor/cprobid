package com.biosystechnologies.swissprot

import java.util.Date

case class Entry(
                  dataSet:String,
                  created: Date,
                  modified: Date,
                  version: Int,
                  accessions: List[String],
                  names: List[String],
                  protein: Protein,
                  sequence: Sequence
                )
