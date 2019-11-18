package com.biosystechnologies.peptides

case class CIDFragments(
                precursor: PeptideIon,
                bIons: List[PeptideIon],
                yIons: List[PeptideIon],
                immoniumIons: List[ImmoniumIon]
              )
