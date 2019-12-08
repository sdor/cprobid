#include <catch.hpp>
#include <string>
#include <map>
#include <algorithm>
#include <AminoAcidSeq.h>
using namespace protein;
using namespace protein::amino_acid;


TEST_CASE("digest with trypsine","[AminoAcidSequence]") {
   AminoAcidSeq aas = AminoAcidSeq {"ARNDCQEGHILKMFPSTWYV"};
   auto digest = aas.trypsinize();
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

TEST_CASE("amino acid sequence monoisotopic mass","[AminoAcidSeq]") {
    AminoAcidSeq aas = AminoAcidSeq{ "PEPTIDE"};
    REQUIRE_THAT(aas.monoisotopicMass(),Catch::WithinAbs(799.3599,0.0001));
}