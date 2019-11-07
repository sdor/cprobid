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

//#pragma once
#ifndef AMINO_ACID
#define AMINO_ACID

#include <string>
#include <vector>
#include "dictionary.h"
#include "dictionary_amino_acid_modification.h"

using namespace std;
class amino_acid
{
	dictionary_amino_acid* aa;
	dictionary_amino_acid_modification* aam;
public:
	amino_acid(void);
	amino_acid(char cod);
	amino_acid(char cod, const char* mcod);
	amino_acid(char cod, string mcod);
	amino_acid(const amino_acid* a);
	amino_acid(const amino_acid& a);
	~amino_acid(void);
	double ResidueMonoMw(void) const;
	// modify amino aicd
	void modify(amino_acid_modification* aa_modification);
	// remove amino acid modification
	void DeModify(void);
	// return amino acod cod

	dictionary_amino_acid* AminoAcid(void) const;
	dictionary_amino_acid* get_dictionary_amino_acid() const {return this->aa;};
	dictionary_amino_acid_modification* get_amino_acid_modification() const {return this->aam;}
	bool can_be_modified(amino_acid_modification* aam);
	operator double(){return this->ResidueMonoMw();};
	operator double() const {return this->ResidueMonoMw();};

};

typedef vector<amino_acid> aa_vector;
// bool is_equal(amino_acid& a1, amino_acid& a2);
inline bool operator < (const amino_acid& a1, const amino_acid& a2){
	return a1.ResidueMonoMw() < a2.ResidueMonoMw();
}

inline bool operator == (const amino_acid& a1, const amino_acid& a2){
	return a1.get_dictionary_amino_acid()==a2.get_dictionary_amino_acid() && a1.get_amino_acid_modification()==a2.get_amino_acid_modification();
}
// lexicographical compare
inline bool amino_acid_less(const amino_acid& a1, const amino_acid& a2) {
	if(a1.get_dictionary_amino_acid() != NULL && a2.get_dictionary_amino_acid() != NULL){
		if(a1.get_dictionary_amino_acid()->get_cod()<a2.get_dictionary_amino_acid()->get_cod()){
			return true;
		}else{
			return a1.ResidueMonoMw()<a2.ResidueMonoMw();
		}
	}else{
		return false;
	}
}
#endif
