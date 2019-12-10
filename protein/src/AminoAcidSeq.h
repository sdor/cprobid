#ifndef MS_AMINO_ACID_SEQ_H
#define MS_AMINO_ACID_SEQ_H
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <map>
#include <AminoAcid.h>
namespace protein {
        using namespace amino_acid;
        double H2O = 1.007825 + 1.007825 + 15.994915;
        double HYDROGEN_MONO_MW = 1.007825;
        double OXYGEN_MONO_MW = 15.994915;

        class AminoAcidSeq {
            private:
                std::vector<AminoAcid> sequence;
            public:
                AminoAcidSeq() {}
                AminoAcidSeq(const std::string& seq);
                AminoAcidSeq(const std::vector<AminoAcid>& aminoAcids);
                AminoAcidSeq(const AminoAcidSeq& seq);

                double monoisotopicMass() const {
                    double mass = 0.0;
                    auto fold= [](double mass, const AminoAcid& aa) {
                        return mass += aa.monoisotopicMass();
                    };
                    return std::accumulate(begin(this->sequence),end(this->sequence),mass,fold) + H2O;
                }

                std::map<unsigned int, std::vector<AminoAcidSeq>> trypsinize(unsigned int n_missed=0);

                std::string toString() const {
                    std::string seq;
                    for(auto& aa: this->sequence) {
                        seq.push_back(aa.cod());
                    }
                    // seq = std::accumulate(begin(this->sequence),end(this->sequence),seq,[](const std::string& s,const AminoAcid& aa) {
                    //     return s + aa.cod();
                    // });
                    return seq;
                }

                AminoAcidSeq& operator = (const string& s) {
                    std::vector<AminoAcid> new_sequence(s.length());
                    std::transform(begin(s),end(s),begin(new_sequence),[](char cod) {
                        AminoAcid aa(cod);
                        return aa;
                    });
                    this->sequence = new_sequence;
                    return *this;
                }

                bool operator == (const AminoAcidSeq& seq) const {
                    bool res = true;
                    if(this->sequence.size() != seq.sequence.size()) {
                        return false;
                    }
                    auto i = begin(this->sequence);
                    auto j = begin(seq.sequence);
                    for(; i != end(this->sequence) && j != end(seq.sequence); i++, j++) {
                        res = res && (*i == *j);
                        if(res == false) {
                            break;
                        }
                    }
                    return res;
                }

                AminoAcidSeq concat(const AminoAcidSeq& seq) const;

                const std::vector<AminoAcid>& peptide() const { return this->sequence;}

        };

        AminoAcidSeq operator + (const AminoAcidSeq& a, const AminoAcidSeq& b) { return a.concat(b);};
}
#endif