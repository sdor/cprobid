#include <AminoAcid.h>
namespace MassSpec {
        double monoisotopicMass(AminoAcid::AminoAcidType aa) {
            switch (aa) {
                case AminoAcid::Alanine:
                    return 71.03711	;
                case AminoAcid::Arginine:
                    return 156.10111;
                case AminoAcid::Asparagine:
                    return 114.04293;
                case AsparticAcid  :
                    mass = 115.02694;
                    break;
                case Cysteine	     :
                    mass = 103.00919;
                    break;
                case Glutamine	    :
                    mass = 129.04259;
                    break;
                case GlutamicAcid  :
                    mass = 128.05858;
                    break;
                case Glycine	      :
                    mass = 57.02146	;
                    break;
                case Histidine	    :
                    mass = 137.05891;
                    break;
                case Isoleucine	   :
                    mass = 113.08406;
                    break;
                case Leucine	      :
                    mass = 113.08406;
                    break;
                case Lysine	       :
                    mass = 128.09496;
                    break;
                case Methionine	   :
                    mass = 131.04049;
                    break;
                case Phenylalanine :
                    mass = 147.06841;
                    break;
                case Proline	      :
                    mass = 97.05276	;
                    break;
                case Serine	       :
                    mass = 87.03203	;
                    break;
                case Threonine	    :
                    mass = 101.04768;
                    break;
                case Tryptophan	   :
                    mass = 186.07931;
                    break;
                case Tyrosine	     :
                    mass = 163.06333;
                    break;
                case AminoAcid::Valine	       :
                    return 99.06841	;
                default:
                    return 0.0;
            }
        }
    // namespace AminoAcid {
        AminoAcid::AminoAcid(char code) {
            switch(code) {
                case 'A': 
                    this->residue = Alanine; 
                    break;
                case 'R': 
                    this->residue = Arginine; 
                    break;
                case 'N': 
                    this->residue = Asparagine;
                    break;
                case 'D': 
                    this->residue = AsparticAcid; 
                    break;
                case 'C': 
                    this->residue = Cysteine;
                    break;
                case 'E': 
                    this->residue = Glutamine; 
                    break;
                case 'Q': 
                    this->residue = GlutamicAcid;
                    break;
                case 'G': 
                    this->residue = Glycine;
                    break;
                case 'H': 
                    this->residue = Histidine;
                    break;
                case 'I': 
                    this->residue = Isoleucine;
                    break;
                case 'L': 
                    this->residue = Leucine;
                    break;
                case 'K': 
                    this->residue = Lysine;
                    break;
                case 'M': 
                    this->residue = Methionine;
                    break;
                case 'F': 
                    this->residue = Phenylalanine;
                    break;
                case 'P': 
                    this->residue = Proline;
                    break;
                case 'S': 
                    this->residue = Serine;
                    break;
                case 'T': 
                    this->residue = Threonine;
                    break;
                case 'W': 
                    this->residue = Tryptophan;
                    break;
                case 'Y': 
                    this->residue = Tyrosine;
                    break;
                case 'V': 
                    this->residue = Valine;
                    break;
                case '<': 
                    this->residue = NTermininal;
                    break;
                case '>': 
                    this->residue = CTerminal;
                    break;
                default:
                    this->residue = UknownAminoAcid;
                    break;
            }
        }

        double AminoAcid::monoisotopicMass() const {
            double mass = 0.0;
            switch (this->residue) {
                case Alanine:
                    mass = 71.03711	;
                    break;
                case Arginine:
                    mass = 156.10111;
                    break;
                case Asparagine	   :
                    mass = 114.04293;
                    break;
                case AsparticAcid  :
                    mass = 115.02694;
                    break;
                case Cysteine	     :
                    mass = 103.00919;
                    break;
                case Glutamine	    :
                    mass = 129.04259;
                    break;
                case GlutamicAcid  :
                    mass = 128.05858;
                    break;
                case Glycine	      :
                    mass = 57.02146	;
                    break;
                case Histidine	    :
                    mass = 137.05891;
                    break;
                case Isoleucine	   :
                    mass = 113.08406;
                    break;
                case Leucine	      :
                    mass = 113.08406;
                    break;
                case Lysine	       :
                    mass = 128.09496;
                    break;
                case Methionine	   :
                    mass = 131.04049;
                    break;
                case Phenylalanine :
                    mass = 147.06841;
                    break;
                case Proline	      :
                    mass = 97.05276	;
                    break;
                case Serine	       :
                    mass = 87.03203	;
                    break;
                case Threonine	    :
                    mass = 101.04768;
                    break;
                case Tryptophan	   :
                    mass = 186.07931;
                    break;
                case Tyrosine	     :
                    mass = 163.06333;
                    break;
                case Valine	       :
                    mass = 99.06841	;
                    break;
                default:
                    break;
            }
            return mass;
        }

        std::string DefaultAminoAcid::toString() const {
            std::string cod;
            switch(this->residue) {
                case Alanine: 
                  cod = "A";
                  break;
                case Arginine:
                    cod = "R";
                    break;
                case Asparagine: 
                    cod = "N";
                    break;
                case AsparticAcid:
                    cod = "D";
                    break;
                case Cysteine:
                    cod = "C";
                    break;
                case Glutamine: 
                    cod = "E";
                    break;
                case GlutamicAcid:
                    cod = "Q";
                    break;
                case Glycine:
                    cod = "G";
                    break;
                case Histidine:
                    cod = "H";
                    break;
                case Isoleucine:
                    cod = "I";
                    break;
                case Leucine: 
                    cod = "L";
                    break;
                case Lysine:
                    cod = "K";
                    break;
                case Methionine: 
                    cod = "M";
                    break;
                case Phenylalanine:
                    cod = "F";
                    break;
                case Proline:
                    cod = "P";
                    break;
                case Serine:
                    cod = "S";
                    break;
                case Threonine:
                    cod = "T";
                    break;
                case Tryptophan:
                    cod = "W";
                    break;
                case Tyrosine:
                    cod = "Y";
                    break;
                case Valine:
                    cod = "V";
                    break;
                case NTermininal:
                    cod = "<";
                    break;
                case CTerminal:
                    cod = ">";
                    break;
                default:
                    cod = "X";
                    break;
            }
            return cod;
        }
    // }
}