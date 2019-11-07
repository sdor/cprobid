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

#include "dictionary_amino_acid_modification.h"

dictionary_amino_acid_modification::dictionary_amino_acid_modification(void)
: deltamw(0)
{
}

dictionary_amino_acid_modification::dictionary_amino_acid_modification(const char* cod,double delta_mass, const char* targets){
	this->cod=cod;
	this->deltamw=delta_mass;
	this->targets=targets;
}
dictionary_amino_acid_modification::~dictionary_amino_acid_modification(void)
{
}

double dictionary_amino_acid_modification::DeltaMonoMass(void)
{
	return this->deltamw ;
}

// true if this modification can be used for given amino acid
bool dictionary_amino_acid_modification::CanModify(char aacod)
{
	bool result;
	size_t found;
	found=this->targets.find(aacod);
	if(found != string::npos){
		result=true;
	} else {
		result=false;
	}
	return result;
}




// add amino acid with cod to targeted amino acid list
void dictionary_amino_acid_modification::AddTarget(char aa)
{
		this->targets+=aa;
}
