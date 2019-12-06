#include <catch.hpp>
#include <string>
#include <map>
#include <algorithm>
#include <AminoAcidSeq.h>
using namespace protein;
using namespace protein::amino_acid;

// TEST_CASE("create amino acid sequence","[AminoAcidSequence]") {
//     std::string seq = "ARNDCQEGHILKMFPSTWYV";
//     AminoAcidSeq aas(seq);
//     REQUIRE_THAT(aas,Catch::Equals(aas));
// }

TEST_CASE("digest with trypsine","[AminoAcidSequence]") {
//    std::string seq = "ARNDCQEGHILKMFPSTWYV";
   AminoAcidSeq aas = AminoAcidSeq {"ARNDCQEGHILKMFPSTWYV"};
   auto digest = aas.trypsinize();
   auto zero_misssed_sites = [&digest]() {
       std::vector<string> r(digest[0].size());
       std::transform(begin(digest[0]),end(digest[0]),begin(r),[](auto aas){
           return aas.toString();
       });
       return r;
   };
//    vector<AminoAcidSeq> no_misssed_expected = { AminoAcidSeq {"AR"}};
   REQUIRE_THAT(zero_misssed_sites(),Catch::UnorderedEquals(std::vector<std::string>{}));

}