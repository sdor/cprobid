#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <AminoAcidSeq.h>
#include <Ion.h>
using namespace std;
using namespace msms;
using namespace protein;
TEST_CASE("collision induced dissociation","[Ions]") {
    auto precursor = cid(AminoAcidSeq{"PEPTIDE"},1);
    auto b_ions = precursor.b_ions();
    auto y_ions = precursor.y_ions();
    vector<double> b_ion_mws(b_ions.size());
    transform(begin(b_ions),end(b_ions),begin(b_ion_mws),[](auto ion) { return ion.mz().value();});
    REQUIRE_THAT(b_ion_mws[0],Catch::WithinAbs(98.06009,0.01));
    REQUIRE_THAT(b_ion_mws[1],Catch::WithinAbs(227.10268,0.01));
    REQUIRE_THAT(b_ion_mws[2],Catch::WithinAbs(324.15544,0.01));
    REQUIRE_THAT(b_ion_mws[3],Catch::WithinAbs(425.20312,0.01));
    REQUIRE_THAT(b_ion_mws[4],Catch::WithinAbs(538.28718,0.01));
    REQUIRE_THAT(b_ion_mws[5],Catch::WithinAbs(653.31413,0.01));
    REQUIRE_THAT(b_ion_mws[6],Catch::WithinAbs(782.35672,0.01));
    vector<double> y_ion_mws(y_ions.size());
    transform(begin(y_ions),end(y_ions),begin(y_ion_mws),[](auto ion) { return ion.mz().value();});
    REQUIRE_THAT(y_ion_mws[0],Catch::WithinAbs(703.31452,0.01));
    REQUIRE_THAT(y_ion_mws[1],Catch::WithinAbs(574.27193,0.01));
    REQUIRE_THAT(y_ion_mws[2],Catch::WithinAbs(477.21916,0.01));
    REQUIRE_THAT(y_ion_mws[3],Catch::WithinAbs(376.17149,0.01));
    REQUIRE_THAT(y_ion_mws[4],Catch::WithinAbs(263.08742,0.01));
    REQUIRE_THAT(y_ion_mws[5],Catch::WithinAbs(148.06048,0.01));
    REQUIRE_THAT(y_ion_mws[6],Catch::WithinAbs(19.01839,0.01));
}