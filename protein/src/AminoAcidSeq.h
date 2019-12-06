#ifndef MS_AMINO_ACID_SEQ_H
#define MS_AMINO_ACID_SEQ_H

#include <numeric>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <AminoAcid.h>
namespace protein {
        using namespace amino_acid;

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
                    return std::accumulate(begin(this->sequence),end(this->sequence),mass,fold);
                }

                std::map<int, std::vector<AminoAcidSeq>> trypsinize();

                std::string toString() const {
                    std::string seq;
                    seq = std::accumulate(begin(this->sequence),end(this->sequence),seq,[](const std::string& s,const AminoAcid& aa) {
                        return s + aa.cod();
                    });
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
                    return this->sequence == seq.sequence;
                }

        };
}
#endif