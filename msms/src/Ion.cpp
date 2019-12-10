#include <Ion.h>
using namespace std;
namespace msms {
    PrecursorIon cid(const AminoAcidSeq& peptide, int charge) {
        vector<IonFragment> _b_ions;
        vector<IonFragment> _y_ions;

        auto aas = peptide.peptide();
        auto mw = peptide.monoisotopicMass();  
        for(auto& aa: aas) {
            if(_b_ions.empty()){
                auto fragment = IonFragment{aa.monoisotopicMass(),charge};
                _b_ions.push_back(fragment);
                _y_ions.push_back(IonFragment{mw - fragment.mw(), charge});
            } else {
                IonFragment fragment = IonFragment{_b_ions.back().mw() + aa.monoisotopicMass(), charge};
                _b_ions.push_back(fragment);
                _y_ions.push_back(IonFragment{mw - fragment.mw(), charge});
            }
        }

        auto precursor = PrecursorIon{peptide.monoisotopicMass(),charge};
        precursor.b_ions(_b_ions);
        precursor.y_ions(_y_ions);
        return precursor;
    }
}