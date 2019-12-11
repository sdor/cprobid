#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
// #include <iosfwd>
// #include <boost/iostreams/stream.hpp>
// #include <boost/iostreams/categories.hpp> 

#include <AminoAcid.h>
#include <AminoAcidSeq.h>
namespace protein {
    using namespace amino_acid;


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
        

        std::map<unsigned int, std::vector<AminoAcidSeq>> AminoAcidSeq::trypsinize(unsigned int n_missed) {
            std::map<unsigned int, std::vector<AminoAcidSeq>> map;
            vector<AminoAcidSeq> fragments;

            auto first = begin(this->sequence);
            auto last = begin(this->sequence);
            size_t size = 0;
            for(; last != end(this->sequence); last++,size++) {
                if(*first == AminoAcid::Arginine || *first == AminoAcid::Lysine) {
                    vector<AminoAcid> fragment;
                    fragment.push_back(*first);
                    fragments.push_back(AminoAcidSeq {fragment} );
                    first++;
                    // last++;
                    if(first == end(this->sequence)) {
                        size = 0;
                        break;
                    }
                } else if(*last == AminoAcid::Arginine || *last == AminoAcid::Lysine) {
                    // last++;
                    // if(last == end(this->sequence)) {
                    //     break;
                    // }
                    size++;
                    vector<AminoAcid> fragment(size);
                    std::copy(first,last+1,begin(fragment));
                    fragments.push_back(AminoAcidSeq {fragment} );
                    first = ++last;
                    size = 0;
                }
            }
            if(size > 0){
                vector<AminoAcid> fragment(size);
                std::copy(first,last,begin(fragment));
                fragments.push_back(AminoAcidSeq {fragment} );
            }            
            map[0]=fragments;
            if(n_missed == 0) {
                return map;    
            }

            for(unsigned int i = 1; i < n_missed + 1; i++) {
                auto start = begin(fragments);
                auto next = [&start,&fragments,i]() {
                   auto _next = start; 
                   for(unsigned int j = 0; j < i + 1 && _next != end(fragments); j++) {
                       _next++;
                   }
                   return _next;
                };
                auto the_end = next();
                while(the_end != end(fragments)) {
                    auto fragment = std::accumulate(start,the_end,AminoAcidSeq{""},[](auto agg, auto aas) {
                        return agg + aas;
                    });
                    map[i].push_back(fragment);
                    start++;
                    if(start == end(fragments)) {
                        break;
                    }
                    the_end = next();
                }
            }

            return map;
        }

        AminoAcidSeq AminoAcidSeq::concat(const AminoAcidSeq& seq) const {
            std::vector<AminoAcid> _sequence;
            for(auto& aa: this->sequence) {
                _sequence.push_back(aa);
            }
            for(auto& aa: seq.sequence) {
                _sequence.push_back(aa);
            }
            return AminoAcidSeq {_sequence};
        }
    
}
