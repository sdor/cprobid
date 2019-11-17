package com.biosystechnologies.peptides

sealed trait ImmoniumCod

case object AlaImmoniumCod extends ImmoniumCod
case object ArgImmoniumCod extends ImmoniumCod
case object AsnImmoniumCod extends ImmoniumCod
case object AspImmoniumCod extends ImmoniumCod
case object CysImmoniumCod extends ImmoniumCod
case object GluImmoniumCod extends ImmoniumCod
case object GlnImmoniumCod extends ImmoniumCod
case object GlyImmoniumCod extends ImmoniumCod
case object HisImmoniumCod extends ImmoniumCod
case object IleImmoniumCod extends ImmoniumCod
case object LeuImmoniumCod extends ImmoniumCod
case object LysImmoniumCod extends ImmoniumCod
case object MetImmoniumCod extends ImmoniumCod
case object PheImmoniumCod extends ImmoniumCod
case object ProImmoniumCod extends ImmoniumCod
case object SerImmoniumCod extends ImmoniumCod
case object ThrImmoniumCod extends ImmoniumCod
case object TrpImmoniumCod extends ImmoniumCod
case object TyrImmoniumCod extends ImmoniumCod
case object ValImmoniumCod extends ImmoniumCod
case object NTerminalImmoniumCod extends ImmoniumCod
case object CTerminalImmoniumCod extends ImmoniumCod
case object UnknownImmoniumCod extends ImmoniumCod

object ImmoniumCod {
  implicit def toImmoniumCod(aminoAcid: AminoAcid): ImmoniumCod = aminoAcid match {
    case Ala => AlaImmoniumCod
    case Arg => ArgImmoniumCod
    case Asn => AsnImmoniumCod
    case Asp => AspImmoniumCod
    case Cys => CysImmoniumCod
    case Glu => GluImmoniumCod
    case Gln => GlnImmoniumCod
    case Gly => GlyImmoniumCod
    case His => HisImmoniumCod
    case Ile => IleImmoniumCod
    case Leu => LeuImmoniumCod
    case Lys => LysImmoniumCod
    case Met => MetImmoniumCod
    case Phe => PheImmoniumCod
    case Pro => ProImmoniumCod
    case Ser => SerImmoniumCod
    case Thr => ThrImmoniumCod
    case Trp => TrpImmoniumCod
    case Tyr => TyrImmoniumCod
    case Val => ValImmoniumCod
    case NTerminal => NTerminalImmoniumCod
    case CTerminal => CTerminalImmoniumCod
    case UnknownAminoAcid => UnknownImmoniumCod
  }

  implicit def toImmoniumIons(immoniumCod: ImmoniumCod): List[ImmoniumIon] = immoniumCod match {
    case AlaImmoniumCod  => List(ImmoniumIon(mz = Ala.immoniumIon))
    case ArgImmoniumCod  => List(ImmoniumIon(mz = Arg.immoniumIon))
    case AsnImmoniumCod  => List(ImmoniumIon(mz = Asn.immoniumIon))
    case AspImmoniumCod  => List(ImmoniumIon(mz = Asp.immoniumIon))
    case CysImmoniumCod  => List(ImmoniumIon(mz = Cys.immoniumIon))
    case GluImmoniumCod  => List(ImmoniumIon(mz = Glu.immoniumIon))
    case GlnImmoniumCod  => List(ImmoniumIon(mz = Gln.immoniumIon))
    case GlyImmoniumCod  => List(ImmoniumIon(mz = Gly.immoniumIon))
    case HisImmoniumCod  => List(ImmoniumIon(mz = His.immoniumIon))
    case IleImmoniumCod  => List(ImmoniumIon(mz = Ile.immoniumIon))
    case LeuImmoniumCod  => List(ImmoniumIon(mz = Leu.immoniumIon))
    case LysImmoniumCod  => List(ImmoniumIon(mz = Lys.immoniumIon), ImmoniumIon(mz = Lys.immoniumIonWithAmmoniaLoss))
    case MetImmoniumCod  => List(ImmoniumIon(mz = Met.immoniumIon))
    case PheImmoniumCod  => List(ImmoniumIon(mz = Phe.immoniumIon))
    case ProImmoniumCod  => List(ImmoniumIon(mz = Pro.immoniumIon))
    case SerImmoniumCod  => List(ImmoniumIon(mz = Ser.immoniumIon))
    case ThrImmoniumCod  => List(ImmoniumIon(mz = Thr.immoniumIon))
    case TrpImmoniumCod  => List(ImmoniumIon(mz = Trp.immoniumIon))
    case TyrImmoniumCod  => List(ImmoniumIon(mz = Tyr.immoniumIon))
    case ValImmoniumCod  => List(ImmoniumIon(mz = Val.immoniumIon))
    case NTerminalImmoniumCod  => List(ImmoniumIon(mz=NTerminal.immoniumIon))
    case CTerminalImmoniumCod  => List(ImmoniumIon(mz=CTerminal.immoniumIon))
    case UnknownImmoniumCod  => List(ImmoniumIon(mz=UnknownAminoAcid.immoniumIon))
  }
}
