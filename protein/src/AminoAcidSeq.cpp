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
    // using namespace boost::iostreams;


        // template<typename Container>
        //     class container_sink {
        //     public:
        //         typedef typename Container::value_type  char_type;
        //         typedef sink_tag                        category;
        //         container_sink(Container& container) : container_(container) { }
        //         std::streamsize write(const char_type* s, std::streamsize n) {
        //             container_.insert(container_.end(), s, s + n);
        //             return n;
        //         }
        //         Container& container() { return container_; }
        //     private:
        //         Container& container_;
        // };

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
        

        std::map<int, std::vector<AminoAcidSeq>> AminoAcidSeq::trypsinize() {
            std::map<int, std::vector<AminoAcidSeq>> map;
            vector<AminoAcidSeq> fragments;
            // vector<AminoAcid> fragment;
            auto first = begin(this->sequence);
            auto last = begin(this->sequence);
            size_t size = 0;
            for(; last != end(this->sequence); last++,size++) {
                if(*last == AminoAcid::Arginine || *last == AminoAcid::Lysine) {
                    last++;
                    size++;
                    vector<AminoAcid> fragment(size);
                    std::copy(first,last,begin(fragment));
                    fragments.push_back(AminoAcidSeq {fragment} );
                    first = last;
                    size = 0;
                }
            }
            if(size > 0){
                vector<AminoAcid> fragment(size);
                std::copy(first,last,begin(fragment));
                fragments.push_back(AminoAcidSeq {fragment} );
            }            
            map[0]=fragments;
            return map;
        }
    
}
