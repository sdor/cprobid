#ifndef MS_AMINO_ACID_H
#define MS_AMINO_ACID_H
#include <optional>
using namespace std;
namespace protein {
    namespace amino_acid {
        
        class AminoAcidModification {
            private:
                unsigned int _uid;
                double _monoisotopicDeltaMass;
            public:
                AminoAcidModification() {}
                AminoAcidModification(unsigned uid, double monoisotopicDeltaMass) {
                    this->_uid = uid;
                    this->_monoisotopicDeltaMass = monoisotopicDeltaMass;
                }
                AminoAcidModification(const AminoAcidModification& m): AminoAcidModification(m.uid(),m.monoisotopicDeltaMass()) {}

                unsigned int uid() const { return this->_uid;}

                double monoisotopicDeltaMass() const {
                    return this->_monoisotopicDeltaMass;
                };

                bool operator == (const AminoAcidModification& m) const { return this->_uid == m.uid();};
        };
        class AminoAcid {
            public:
                enum AminoAcidType {
                    Alanine	        =  'A', // Ala	A	aliphatic	nonpolar	neutral	1.8			89.094	8.76	GCN
                    Arginine	    =  'R', // Arg	R	basic	basic polar	positive	−4.5			174.203	5.78	MGN, CGY (coding codons can also be expressed by: CGN, AGR)
                    Asparagine	    =  'N', // Asn	N	amide	polar	neutral	−3.5			132.119	3.93	AAY
                    AsparticAcid    =  'D', // Asp	D	acid	acidic polar	negative	−3.5			133.104	5.49	GAY
                    Cysteine	    =  'C', // Cys	C	sulfur-containing	nonpolar	neutral	2.5	250	0.3	121.154	1.38	UGY
                    Glutamine	    =  'Q', // Gln	Q	amide	polar	neutral	−3.5			146.146	3.9	CAR
                    GlutamicAcid    =  'E', // Glu	E	acid	acidic polar	negative	−3.5			147.131	6.32	GAR
                    Glycine	        =  'G', // Gly	G	aliphatic	nonpolar	neutral	−0.4			75.067	7.03	GGN
                    Histidine	    =  'H', // His	H	basic aromatic	basic polar	positive(10%) neutral(90%)	−3.2	211	5.9	155.156	2.26	CAY
                    Isoleucine	    =  'I', // Ile	I	aliphatic	nonpolar	neutral	4.5			131.175	5.49	AUH
                    Leucine	        =  'L', // Leu	L	aliphatic	nonpolar	neutral	3.8			131.175	9.68	YUR, CUY (coding codons can also be expressed by: CUN, UUR)
                    Lysine	        =  'K', // Lys	K	basic	basic polar	positive	−3.9			146.189	5.19	AAR
                    Methionine	    =  'M', // Met	M	sulfur-containing	nonpolar	neutral	1.9			149.208	2.32	AUG
                    Phenylalanine   =  'F', // Phe	F	aromatic	nonpolar	neutral	2.8	257, 206, 188	0.2, 9.3, 60.0	165.192	3.87	UUY
                    Proline	        =  'P', // Pro	P	cyclic	nonpolar	neutral	−1.6			115.132	5.02	CCN
                    Serine	        =  'S', // Ser	S	hydroxyl-containing	polar	neutral	−0.8			105.093	7.14	UCN, AGY
                    Threonine	    =  'T', // Thr	T	hydroxyl-containing	polar	neutral	−0.7			119.119	5.53	ACN
                    Tryptophan	    =  'W', // Trp	W	aromatic	nonpolar	neutral	−0.9	280, 219	5.6, 47.0	204.228	1.25	UGG
                    Tyrosine	    =  'Y', // Tyr	Y	aromatic	polar	neutral	−1.3	274, 222, 193	1.4, 8.0, 48.0	181.191	2.91	UAY
                    Valine	        =  'V', // Val	V	aliphatic	nonpolar	neutral	4.2			117.148	6.73	GUN
                    NTerminal     =  '<',
                    CTerminal       =  '>', 
                    UknownAminoAcid
                };
            private:
                AminoAcidType residue;
                optional<AminoAcidModification> modification;
            public:
                AminoAcid(){
                    this->residue = UknownAminoAcid;
                }

                AminoAcid(char cod);
                AminoAcid(const AminoAcid& aa) {
                    this->residue = aa.residue;
                    this->modification = aa.modification;
                }

                double monoisotopicMass() const;

                char cod() const { return this->residue;} 

                AminoAcidType getAminoAcidType() const {
                    return this->residue;
                }
                void setAminoAcidType(AminoAcidType c) {
                    this->residue = c;
                }

                std::optional<AminoAcidModification> getModification() const { return this->modification;}

                void modify(const AminoAcidModification& modification) {
                   this->modification = modification;
                } 

                bool operator == (char c) const { return this->residue == c;}

                bool operator == (const AminoAcid& aa) const {
                    return this->residue == aa.residue;
                }


        };


    }


    

    // }
  

    // A	Ala	C3H5ON	    71.03711	71.0788
    // R	Arg	C6H12ON4	156.10111	156.1875
    // N	Asn	C4H6O2N2	114.04293	114.1038
    // D	Asp	C4H5O3N	    115.02694	115.0886
    // C	Cys	C3H5ONS	    103.00919	103.1388
    // E	Glu	C5H7O3N	    129.04259	129.1155
    // Q	Gln	C5H8O2N2	128.05858	128.1307
    // G	Gly	C2H3ON      57.02146	57.0519
    // H	His	C6H7ON3	    137.05891	137.1411
    // I	Ile	C6H11ON	    113.08406	113.1594
    // L	Leu	C6H11ON	    113.08406	113.1594
    // K	Lys	C6H12ON2	128.09496	128.1741
    // M	Met	C5H9ONS	    131.04049	131.1926
    // F	Phe	C9H9ON	    147.06841	147.1766
    // P	Pro	C5H7ON	    97.05276	97.1167
    // S	Ser	C3H5O2N	    87.03203	87.0782
    // T	Thr	C4H7O2N	    101.04768	101.1051
    // W	Trp	C11H10ON2	186.07931	186.2132
    // Y	Tyr	C9H9O2N	    163.06333	163.1760
    // V	Val	C5H9ON	    99.06841	99.1326


    



}
#endif