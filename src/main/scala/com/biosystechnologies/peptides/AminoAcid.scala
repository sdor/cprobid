package com.biosystechnologies.peptides

sealed trait AminoAcid {
  def code:Char
  def cod3:String
  def name:String
  def monoMw:Double
  def averageMw:Double
  def immoniumIon: Double
}

case object Ala extends AminoAcid {
  val code = 'A'
  val cod3 =	"Ala"
  val name =  "Alanine"
  val monoMw:Double = 71.03711
  val averageMw:Double = 71.0788
  val immoniumIon = 44.05003
}
case object Arg extends AminoAcid {
  val code = 'R'
  val cod3 =	"Arg"
  val name = "Arginine"
  val monoMw = 156.10111
  val averageMw = 156.1875
  val immoniumIon = 129.114
}
case object Asn extends AminoAcid {
  val code = 'N'
  val cod3 =	"Asn"
  val name =  "Asparagine"
  val monoMw = 114.04293
  val averageMw = 114.1038
  val immoniumIon = 87.05584
}
case object Asp extends AminoAcid {
  val code = 'D'
  val cod3 =	"Asp"
  val name =  "Aspartic Acid"
  val monoMw = 115.02694
  val averageMw = 115.0886
  val immoniumIon = 88.03986
}
case object Cys extends AminoAcid {
  val code = 'C'
  val cod3 =	"Cys"
  val name =  "Cysteine"
  val monoMw = 103.00919
  val averageMw = 103.1388
  val immoniumIon =  76.0221
}
case object Glu extends AminoAcid {
  val code = 'E'
  val cod3 =	"Glu"
  val name = "Glutamic Acid"
  val monoMw = 129.04259
  val averageMw = 129.1155
  val immoniumIon = 102.0555
}
case object Gln extends AminoAcid {
  val code = 'Q'
  val cod3 =	"Gln"
  val name = "Glutamine"
  val monoMw = 128.05858
  val averageMw = 128.1307
  val immoniumIon =  101.0715
}
case object Gly extends AminoAcid {
  val code = 'G'
  val cod3 =	"Gly"
  val name =  "Glycine"
  val monoMw =  57.02146
  val averageMw = 57.0519
  val immoniumIon = 30.03438
}
case object His extends AminoAcid {
  val code = 'H'
  val cod3 =	"His"
  val name = "Histidine"
  val monoMw = 137.05891
  val averageMw = 137.1411
  val immoniumIon = 110.0718
}
case object Ile extends AminoAcid {
  val code = 'I'
  val cod3 =	"Ile"
  val name = "Isoleucine"
  val monoMw = 113.08406
  val averageMw = 113.1594
  val immoniumIon = 86.09698
}
case object Leu extends AminoAcid {
  val code = 'L'
  val cod3 =	"Leu"
  val name =  "Leucine"
  val monoMw = 113.08406
  val averageMw = 113.1594
  val immoniumIon = 86.09698
}
case object Lys extends AminoAcid {
  val code = 'K'
  val cod3 =	"Lys"
  val name =  "Lysine"
  val monoMw = 128.09496
  val averageMw = 128.1741
  val immoniumIon = 101.1079
  val immoniumIonWithAmmoniaLoss = 84.08136
}
case object Met extends AminoAcid {
  val code = 'M'
  val cod3 =	"Met"
  val name =  "Methionine"
  val monoMw = 131.04049
  val averageMw = 131.1926
  val immoniumIon = 104.0534
}
case object Phe extends AminoAcid {
  val code = 'F'
  val cod3 =	"Phe"
  val name =  "Phenylalanine"
  val monoMw = 147.06841
  val averageMw = 147.1766
  val immoniumIon =  120.0813
}
case object Pro extends AminoAcid {
  val code = 'P'
  val cod3 =	"Pro"
  val name =  "Proline"
  val monoMw =  97.05276
  val averageMw = 97.1167
  val immoniumIon = 70.06568
}
case object Ser extends AminoAcid {
  val code = 'S'
  val cod3 =	"Ser"
  val name =  "Serine"
  val monoMw =  87.03203
  val averageMw = 87.0782
  val immoniumIon = 60.04494
}
case object Thr extends AminoAcid {
  val code = 'T'
  val cod3 =	"Thr"
  val name =  "Threonine"
  val monoMw = 101.04768
  val averageMw = 101.1051
  val immoniumIon = 74.06059
}
case object Trp extends AminoAcid {
  val code = 'W'
  val cod3 =	"Trp"
  val name =  "Tryptophan"
  val monoMw = 186.07931
  val averageMw = 186.2132
  val immoniumIon = 159.0922
}
case object Tyr extends AminoAcid {
  val code = 'Y'
  val cod3 =	"Tyr"
  val name =  "Tyrosine"
  val monoMw = 163.06333
  val averageMw = 163.1760
  val immoniumIon = 136.0762
}
case object Val extends AminoAcid {
  val code = 'V'
  val cod3 =	"Val"
  val name =  "Valine"
  val monoMw =  99.06841
  val averageMw = 99.1326
  val immoniumIon = 72.08133
}
case object NTerminal extends AminoAcid {
  val code = '<'
  val cod3 =	"<"
  val name =  "NTerminal"
  val monoMw =  0.0
  val averageMw = 0.0
  val immoniumIon = 0.0
}
case object CTerminal extends AminoAcid {
  val code = '>'
  val cod3 =	">"
  val name = "CTerminal"
  val monoMw =  0.0
  val averageMw = 0.0
  val immoniumIon = 0.0
}

case object UnknownAminoAcid extends AminoAcid {
  val code = 'X'
  val cod3 =	"XXX"
  val monoMw =  0.0
  val name = "UnknownAminoAcid"
  val averageMw = 0.0
  val immoniumIon = 0.0
}

object AminoAcid {
  def fromChar(c: Char):AminoAcid = c match {
    case 'A' => Ala 
    case 'R' => Arg
    case 'N' => Asn
    case 'D' => Asp
    case 'C' => Cys
    case 'E' => Glu
    case 'Q' => Gln
    case 'G' => Gly
    case 'H' => His
    case 'I' => Ile
    case 'L' => Leu
    case 'K' => Lys
    case 'M' => Met
    case 'F' => Phe
    case 'P' => Pro
    case 'S' => Ser
    case 'T' => Thr
    case 'W' => Trp
    case 'Y' => Tyr
    case 'V' => Val
    case '<' => NTerminal
    case '>' => CTerminal
    case _ => UnknownAminoAcid
  }
}
