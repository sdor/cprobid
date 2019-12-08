#include <catch.hpp>
#include <AminoAcid.h>
using namespace protein::amino_acid;

TEST_CASE("amino acids equal","[AminoAcid]") {
    AminoAcidModification m = AminoAcidModification(0,0.0);
    AminoAcid modified = AminoAcid{AminoAcid::Alanine};
    modified.modify(m);
    REQUIRE(AminoAcid{AminoAcid::Alanine} == AminoAcid{AminoAcid::Alanine});
    REQUIRE(AminoAcid{AminoAcid::Alanine} != modified);
    REQUIRE(modified == modified);  
    REQUIRE(AminoAcid{AminoAcid::Alanine} != AminoAcid{AminoAcid::Glycine});
    REQUIRE(modified != AminoAcid{AminoAcid::Glycine});  
}

TEST_CASE("amino acid monomolecular mw","[AminoAcid]") {
    AminoAcid lysine = AminoAcid{ AminoAcid::Lysine};
    REQUIRE_THAT(lysine.monoisotopicMass(),Catch::WithinAbs(128.09496,0.000001));
    lysine.modify(AminoAcidModification{0,0.1});
    REQUIRE_THAT(lysine.monoisotopicMass(),Catch::WithinAbs(128.09496+0.1,0.000001));
}