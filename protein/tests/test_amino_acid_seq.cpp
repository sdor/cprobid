#include <catch.hpp>
#include <string>
#include <map>
#include <algorithm>
#include <AminoAcidSeq.h>

TEST_CASE("create amino acid sequence","[AminoAcidSequence]") {
    std::string seq = "<ARNDCQEGHILKMFPSTWYV>";
    MassSpec::AminoAcid::AminoAcidSeq aas(seq);
    REQUIRE(aas.toString() == seq);
}

TEST_CASE("digest with trypsine","[AminoAcidSequence]") {
   std::string seq = "<ARNDCQEGHILKMFPSTWYV>";
   MassSpec::AminoAcid::AminoAcidSeq aas(seq);
   auto digest = aas.trypsinize();
   std:vector<std::string> peptides;
   for(auto kv: digest) {
       vector<std::string> ss;
       for(auto aas: kv.second) {
           ss.push_back(aas.toString());
       }
       for(auto s: ss) {
           peptides.push_back(s);
       }
   }
   std::vector<std::string> expected = {"<AR","NDCQEGHILK","MFPSTWYV>"};
//    std::string s1 = ::Catch::Detail::stringify(peptides);
//    std::string s2 = ::Catch::Detail::stringify(expected);
   REQUIRE_THAT(peptides,Catch::Equals(expected));

}