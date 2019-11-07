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

#include "amino_acid.h"

amino_acid::amino_acid(void)
{
	this->aa=NULL;
	this->aam=NULL;
}

amino_acid::amino_acid(char cod)
{
	this->aa=Dictionary.GetAminoAcid(cod);
	this->aam=NULL;
}

amino_acid::amino_acid(char cod, const char* mcod){
	this->aa=Dictionary.GetAminoAcid(cod);
    this->aam=Dictionary.get_amino_acid_modification(mcod);
}

amino_acid::amino_acid(char cod, string mcod){
	this->aa=Dictionary.GetAminoAcid(cod);
	this->aam=Dictionary.get_amino_acid_modification(mcod);
}

amino_acid::amino_acid(const amino_acid* a){
	this->aa=a->get_dictionary_amino_acid();
	this->aam=a->get_amino_acid_modification();
}

amino_acid::amino_acid(const amino_acid& a){
	this->aa=a.get_dictionary_amino_acid();
	this->aam=a.get_amino_acid_modification();
}

amino_acid::~amino_acid(void)
{
	this->aa=NULL;
	this->aam=NULL;
}

double amino_acid::ResidueMonoMw(void) const
{
	double mw=0.0;
	if(this->aam != NULL && this->aa!=NULL){
		mw=this->aa->ResidueMonoMw()+this->aam->DeltaMonoMass();
	}else{
		if(this->aa!=NULL)
			mw=this->aa->ResidueMonoMw();
	}
	return mw;
}

// modify amino aicd
void amino_acid::modify(amino_acid_modification* aa_modification)
{
//	if(aa_modification->CanModify(this->aa->get_cod() )){
		this->aam=aa_modification;
//	}
}

// remove amino acid modification
void amino_acid::DeModify(void)
{
	this->aam=NULL;
}


dictionary_amino_acid* amino_acid::AminoAcid(void) const
{
	return this->aa;
}

bool amino_acid::can_be_modified(amino_acid_modification* aam){
	bool result;
	result=aam->CanModify(this->get_dictionary_amino_acid()->get_cod()) && this->aam == NULL;
	return result;
}

//bool is_equal(amino_acid& a1, amino_acid& a2)
//{
//	return a1.AminoAcid() == a2.AminoAcid() && a1.Modification()==a2.Modification();
//}
