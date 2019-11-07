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

#pragma once
#include "amino_acid_sequence.h"


class amino_acid_sequence_fragment : public amino_acid_sequence
{

public:
	amino_acid_sequence_fragment(void);
	amino_acid_sequence_fragment(string accession, char front_aa_cod,vector<amino_acid>::iterator b,vector<amino_acid>::iterator e,char back_aa_cod);
    ~amino_acid_sequence_fragment(void);
	string SequenceString(void);
	vector<amino_acid>::iterator begin(){return this->fragment_begin;}
	vector<amino_acid>::iterator end(){return this->fragment_end;}
	char front_aa_cod(){return front;}
	char back_aa_cod(){return back;}
	string get_accession(){return accession;};
	void set_accession(string accession){this->accession=accession;};
private:
	// begin of amino acid fragment
	vector<amino_acid>::iterator fragment_begin;
	// end of amino acid sequence iterator
	vector<amino_acid>::iterator fragment_end;
	char front;
	char back;
	string accession;
};
typedef amino_acid_sequence_fragment aas_fragment;
