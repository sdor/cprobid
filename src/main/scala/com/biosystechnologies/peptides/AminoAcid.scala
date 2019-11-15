package com.biosystechnologies.peptides

sealed trait AminoAcid {
  def code:Char
  def cod3:String  
  def monoMw:Double
  def averageMw:Double
}

case object Ala extends AminoAcid {
  def code = 'A'
  def cod3 =	"Ala"   
  def monoMw:Double = 71.03711
  def averageMw:Double = 71.0788
}
case object Arg extends AminoAcid {
  def code = 'R'
  def cod3 =	"Arg"	
  def monoMw = 156.10111	
  def averageMw = 156.1875
}
case object Asn extends AminoAcid {
  def code = 'N'
  def cod3 =	"Asn"
  def monoMw = 114.04293	
  def averageMw = 114.1038
}
case object Asp extends AminoAcid {
  def code = 'D'
  def cod3 =	"Asp"		  
  def monoMw = 115.02694	
  def averageMw = 115.0886
}
case object Cys extends AminoAcid {
  def code = 'C'
  def cod3 =	"Cys"	 
  def monoMw = 103.00919	
  def averageMw = 103.1388
}
case object Glu extends AminoAcid {
  def code = 'E'
  def cod3 =	"Glu"		  
  def monoMw = 129.04259	
  def averageMw = 129.1155
}
case object Gln extends AminoAcid {
  def code = 'Q'
  def cod3 =	"Gln"	  
  def monoMw = 128.05858	
  def averageMw = 128.1307
}
case object Gly extends AminoAcid {
  def code = 'G'
  def cod3 =	"Gly"	    
  def monoMw =  57.02146	
  def averageMw = 57.0519
}
case object His extends AminoAcid {
  def code = 'H'
  def cod3 =	"His"	   
  def monoMw = 137.05891	
  def averageMw = 137.1411
}
case object Ile extends AminoAcid {
  def code = 'I'
  def cod3 =	"Ile"	  
  def monoMw = 113.08406	
  def averageMw = 113.1594
}
case object Leu extends AminoAcid {
  def code = 'L'
  def cod3 =	"Leu"	  
  def monoMw = 113.08406	
  def averageMw = 113.1594
}
case object Lys extends AminoAcid {
  def code = 'K'
  def cod3 =	"Lys"	 
  def monoMw = 128.09496	
  def averageMw = 128.1741
}
case object Met extends AminoAcid {
  def code = 'M'
  def cod3 =	"Met"	  
  def monoMw = 131.04049	
  def averageMw = 131.1926
}
case object Phe extends AminoAcid {
  def code = 'F'
  def cod3 =	"Phe"	    
  def monoMw = 147.06841	
  def averageMw = 147.1766
}
case object Pro extends AminoAcid {
  def code = 'P'
  def cod3 =	"Pro"	    
  def monoMw =  97.05276	
  def averageMw = 97.1167
}
case object Ser extends AminoAcid {
  def code = 'S'
  def cod3 =	"Ser"	   
  def monoMw =  87.03203	
  def averageMw = 87.0782
}
case object Thr extends AminoAcid {
  def code = 'T'
  def cod3 =	"Thr"	   
  def monoMw = 101.04768	
  def averageMw = 101.1051
}
case object Trp extends AminoAcid {
  def code = 'W'
  def cod3 =	"Trp"	 
  def monoMw = 186.07931	
  def averageMw = 186.2132
}
case object Tyr extends AminoAcid {
  def code = 'Y'
  def cod3 =	"Tyr"	  
  def monoMw = 163.06333	
  def averageMw = 163.1760
}
case object Val extends AminoAcid {
  def code = 'V'
  def cod3 =	"Val"	   
  def monoMw =  99.06841	
  def averageMw = 99.1326
}
case object NTerminal extends AminoAcid {
  def code = '<'
  def cod3 =	"<"	   
  def monoMw =  0.0	
  def averageMw = 0.0
}
case object CTerminal extends AminoAcid {
  def code = '>'
  def cod3 =	">"	   
  def monoMw =  0.0	
  def averageMw = 0.0
}

case object UnknownAminoAcid extends AminoAcid {
  def code = 'X'
  def cod3 =	"XXX"	   
  def monoMw =  0.0	
  def averageMw = 0.0
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
