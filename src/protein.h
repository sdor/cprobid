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
#include <vector>
#include "amino_acid_sequence.h"
#include "amino_acid_sequence_fragment.h"
using namespace std;
class protein :	public amino_acid_sequence
{
	string accession;
	string description;
public:
	protein(void);
	protein(string fasta_entry);
	protein(string accession, string description, string sequence);
	~protein(void);

	void set_accession(string accession){this->accession=accession;};
	void set_description(string description){this->description=description;}
	string get_accession(){return this->accession;};
	string get_description(){return this->description;};

	vector<aas_fragment> digest(string sites, int nmissed);
};
