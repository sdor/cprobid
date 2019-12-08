#include <catch.hpp>
#include <string>
#include <map>
#include <algorithm>
#include <AminoAcidSeq.h>
using namespace protein;
using namespace protein::amino_acid;


TEST_CASE("digest with trypsine","[AminoAcidSequence]") {
//    std::string seq = "ARNDCQEGHILKMFPSTWYV";
   AminoAcidSeq aas = AminoAcidSeq {"ARNDCQEGHILKMFPSTWYV"};
   auto digest = aas.trypsinize();
//    auto zero_misssed_sites_f = [&digest]() {
//        std::vector<std::string> r(digest[0].size());
//        std::transform(begin(digest[0]),end(digest[0]),begin(r),[](auto aas){
//            return aas.toString();
//        });
//        return r;
//    };
//    std::vector<std::string> zero_misssed_sites = zero_misssed_sites_f(); 
//    std::vector<std::string> expected = std::vector<std::string>{
//        std::string{"AR"}, 
//        std::string{"NDCEQGHILK"}, 
//        std::string{"MFPSTWYV"}
//    };
//    REQUIRE(zero_misssed_sites == expected);
//    REQUIRE_THAT(zero_misssed_sites,Catch::UnorderedEquals(expected));
   std::vector<AminoAcidSeq> expected = std::vector<AminoAcidSeq>{
       AminoAcidSeq{"AR"}, 
       AminoAcidSeq{"NDCEQGHILK"}, 
       AminoAcidSeq{"MFPSTWYV"}
   };

   REQUIRE_THAT(
    digest[0], 
    Catch::Predicate<std::vector<AminoAcidSeq>>(
        [&expected](const std::vector<AminoAcidSeq>& a)->bool {
            auto res = a.size() == expected.size();
            if(res == false) {
                return false;
            }
            auto i = a.begin();
            auto j = expected.begin();
            for(; i != a.end() && j != expected.end(); i++, j++) {
                bool r = *i == *j;
                res = res && r;
                if(res == false) {
                    break;
                }
            }
            return res;
        }
    )
   );
}

TEST_CASE("concat amino acid sequences","[AminoAcidSequence]") {
    AminoAcidSeq a = AminoAcidSeq{ "PEPTIDE"};
    AminoAcidSeq b = AminoAcidSeq{ "PEPTIDE"};
    REQUIRE((a+b).toString() == (AminoAcidSeq{"PEPTIDEPEPTIDE"}).toString());
}