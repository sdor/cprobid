#ifndef MS_AMINO_ACID_SEQ_H
#define MS_AMINO_ACID_SEQ_H

#include <numeric>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <AminoAcid.h>
namespace MassSpec {
    namespace AminoAcid {

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

                std::map<int, std::vector<AminoAcidSeq>> trypsinize() const;
                std::string toString() const {
                    std::string seq;
                    seq = std::accumulate(begin(this->sequence),end(this->sequence),seq,[](const std::string& s,const AminoAcid& aa) {
                        return s + aa.toString();
                    });
                    return seq;
                }     
        };
    }
}
#endif