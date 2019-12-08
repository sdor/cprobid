#include <AminoAcid.h>
namespace protein {
    namespace amino_acid {
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
                    this->residue = NTerminal;
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
            if(this->is_modified()) {
                mass += this->modification.value().monoisotopicDeltaMass();
            }
            return mass;
        }

        char AminoAcid::cod() const {
            switch(this->residue) {
                case Alanine: 
                    return 'A';
                case Arginine: 
                    return 'R'; 
                case Asparagine:
                    return 'N';
                case     AsparticAcid:
                    return 'D'; 
                case Cysteine:
                    return 'C';
                case    Glutamine:
                    return 'E';
                case GlutamicAcid:
                    return 'Q';
                case Glycine:
                    return 'G';
                case Histidine:
                    return 'H';
                case Isoleucine:
                    return 'I';
                case    Leucine:
                    return 'L';
                case    Lysine:
                    return 'K';
                case Methionine:
                    return 'M';
                case    Phenylalanine:
                    return 'F';
                case Proline:
                    return 'P';
                case Serine:
                    return 'S';
                case Threonine:
                    return 'T';
                case Tryptophan:
                    return 'W';
                case Tyrosine:
                    return 'Y';
                case Valine:
                    return 'V';
                case NTerminal:
                    return '<';
                case CTerminal:
                    return '>';
                default:
                    return 'X';
            }
            
        }
    }
}