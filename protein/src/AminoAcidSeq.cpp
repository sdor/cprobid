#include <algorithm>
#include <vector>
#include <map>
#include <AminoAcid.h>
#include <AminoAcidSeq.h>
namespace MassSpec {
    namespace AminoAcid {

        AminoAcidSeq::AminoAcidSeq(const std::string& seq) {
            this->sequence.resize(seq.size());
            std::transform(begin(seq),end(seq),begin(this->sequence),[](char cod) {
                AminoAcid aa(cod);
                return aa;
            });
        }

        AminoAcidSeq::AminoAcidSeq(const std::vector<AminoAcid>& aminoAcids) {
            this->sequence.resize(aminoAcids.size());
            std::copy(begin(aminoAcids),end(aminoAcids), begin(this->sequence));
        }

        AminoAcidSeq::AminoAcidSeq(const AminoAcidSeq& seq): AminoAcidSeq(seq.sequence) {}
        

        std::map<int, std::vector<AminoAcidSeq>> AminoAcidSeq::trypsinize() const {
            std::map<int, std::vector<AminoAcidSeq>> res;
            std::vector<AminoAcidSeq> fragments;
            std::vector<AminoAcid> fragment;
            for(int i=0; i < this->sequence.size(); ++i) {
                AminoAcid aa = this->sequence[i];
                fragment.push_back(aa);
                // DefaultAminoAcid aa = this->sequence[i].getAminoAcid();
                if( aa == DefaultAminoAcid::Arginine || aa == DefaultAminoAcid::Lysine) {
                    if(this->sequence[i+1].getAminoAcid() != DefaultAminoAcid::Proline) {
                        AminoAcidSeq seq(fragment);
                        fragments.push_back(seq);
                        fragment.resize(0);
                    }
                }
            }
            AminoAcidSeq seq(fragment);
            fragments.push_back(seq);
            res[0] = fragments;
            fragments.clear();
            return res;
        }
    }
}
