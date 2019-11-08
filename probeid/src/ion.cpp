/*
Program       : cprobid
Author        : Sergey Doronin <sdoronin@notes.cc.sunysb.edu>

Copyright (C) 2007 Sergey Doronin

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Sergey Doronin
Stony Brook University
Nicolls Rd.
Stony Brook, NY  11790  USA
sdoronin@notes.cc.sunysb.edu

*/

#include "ion.h"
#include "dictionary.h"

ion::ion(void) {
    mz=0.0;
    charge=0;
    mw=0.0;
    intensity=0.0;
    mwcomputed=true;
}
//
//ion::ion(double mz, double intensity){
//	this->mz=mz;
//	this->intensity=intensity;
//	this->charge=1;
//	this->mw=mz-Hydrogen.MonoMass();
//}

ion::ion(double mz, int chrg, double intensity) {
    this->mz=mz;
    this->charge=chrg;
    this->intensity=intensity;
    this->mw=0.0;
//    this->compute_mw();
}

ion::ion(const ion* e) {
    this->mz=e->get_mz();
    this->charge=e->get_charge();
    this->intensity=e->get_intensity();
//    this->compute_mw();
}

ion::ion(const ion& e) {
    this->mz=e.get_mz();
    this->charge=e.get_charge();
    this->intensity=e.get_intensity();
 //   this->compute_mw();
}

ion::~ion(void) {
}


double ion::get_mw(void) const {
    return this->charge*(this->mz-Hydrogen.MonoMass());
}

//void ion::compute_mw(){
//    this->mw=this->charge*(this->mz-Hydrogen.MonoMass());
//    this->mwcomputed=true;
//}




ion& ion::operator = (const ion& e){
    this->mz=e.get_mz();
    this->charge=e.get_charge();
    this->intensity=e.get_intensity();
    return *this;
}


