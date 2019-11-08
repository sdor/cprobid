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

#include "amino_acid_sequence_fragment.h"

amino_acid_sequence_fragment::amino_acid_sequence_fragment(void)
{
}

amino_acid_sequence_fragment::amino_acid_sequence_fragment(string accession, char front_aa_cod,vector<amino_acid>::iterator b,vector<amino_acid>::iterator e,char back_aa_cod){
	this->set_accession(accession);
	this->front=front_aa_cod;
	this->back=back_aa_cod;
	this->fragment_begin=b;
	this->fragment_end=e;
	amino_acid ntaa('<');
	this->sequence.push_back(ntaa);
	vector<amino_acid>::iterator i;
	vector<amino_acid>::iterator theEnd=this->fragment_end;
	theEnd++;
	for(i=this->fragment_begin; i !=theEnd; i++){
		amino_acid aa(*i);
		this->sequence.push_back(aa);
	}
	amino_acid ctaa('>');
	this->sequence.push_back(ctaa);
}

amino_acid_sequence_fragment::~amino_acid_sequence_fragment(void)
{
}


string amino_acid_sequence_fragment::SequenceString(void)
{
	string s="";
	if(this->sequence.size() > 2){
		vector<amino_acid>::iterator theBegin=this->sequence.begin();
		theBegin++;
		vector<amino_acid>::iterator theEnd=this->sequence.end();
		theEnd--;

		for(vector<amino_acid>::iterator i=theBegin;i != theEnd;i++){
			s+=i->get_dictionary_amino_acid()->get_cod();
		}
	}
	return s;
}


