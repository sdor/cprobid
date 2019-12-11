#include <catch.hpp>
#include <string>
#include <map>
#include <algorithm>
#include <AminoAcidSeq.h>
using namespace protein;
using namespace protein::amino_acid;


TEST_CASE("digest with trypsine","[AminoAcidSequence]") {
   AminoAcidSeq aas = AminoAcidSeq {"MRSIKPLRCCNAHGRHVSQEYGRCTLLLFREKLFLQTGLVCNKQCNAPNNDGAESKHHGIHHGSRGALALRGAGVHLLASAALGPRVLAGLVPTGRSVQGSVGQCGRVAQIGRARDVAARKQESYCEK"};
   
   auto digest = aas.trypsinize(1);
   std::map<unsigned int,std::vector<AminoAcidSeq>> expected;
   //TODO: write compare correctly
   REQUIRE(digest == expected);
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