#ifndef MSMS_ION_H
#define MSMS_ION_H
#include <optional>
#include <vector>
#include <AminoAcidSeq.h>
using namespace std;
using namespace protein;
namespace msms {
    class Ion {
        private:
         inline static double HYDROGEN_MONO_MW = 1.007825;
        private:
         double _mw;
         int _charge;
        public:
         Ion() {};
         Ion(double mw, int charge) {
             this->_mw = mw;
             this->_charge = charge;
         }
         Ion(const Ion& ion) {
             this->_mw = ion.mw();
             this->_charge = ion.charge();
         }

         double mw() const { return this->_mw;}
         int charge() const { return this->_charge;}
         void add_proton() {
             this->_charge++;
         }
         void remove_proton() {
             this->_charge--;
         }
         bool has_charge() const { return this->_charge != 0;}
         optional<double> mz() {
             optional<double> _mz;
             if(this->has_charge()) {
                _mz = (this->mw() + this->charge()* HYDROGEN_MONO_MW)/this->charge();
             }
             return _mz;
         }  
    };

    class IonFragment: public Ion  {
        public:
         IonFragment(): Ion() {};
         IonFragment(double mw, int charge): Ion(mw,charge) {};
         IonFragment(const IonFragment& fragment): Ion(fragment.mw(), fragment.charge()) {
             
         } 
    };

    class PrecursorIon: public Ion {
       private:
        vector<IonFragment> _b_ions;
        vector<IonFragment> _y_ions;
       public:
         PrecursorIon(): Ion() {}
         PrecursorIon(double mw, int charge): Ion(mw,charge) {}
         PrecursorIon(const PrecursorIon& precursorIon): Ion(precursorIon.mw(),precursorIon.charge()) {
             this->_b_ions = precursorIon.b_ions();
             this->_y_ions = precursorIon.y_ions();
         }

         const vector<IonFragment>& b_ions() const { return this->_b_ions;}
         const vector<IonFragment>& y_ions() const { return this->_y_ions;}

         void b_ions(const vector<IonFragment>& ions) {
             this->_b_ions = ions;
         }
         void y_ions(const vector<IonFragment>& ions) {
             this->_y_ions = ions;
         }


    };

    extern PrecursorIon cid(const AminoAcidSeq& peptide, int charge);

    class PeptideIon: private PrecursorIon {
        private:
         AminoAcidSeq peptide;
        public:
            PeptideIon() {}
            PeptideIon(const AminoAcidSeq& peptide, int charge): PrecursorIon(peptide.monoisotopicMass(),charge) {
                this->peptide = peptide;
                auto precursor = cid(peptide,charge);
                this->b_ions(precursor.b_ions());
                this->y_ions(precursor.y_ions());
            } 
    };

    
}
#endif