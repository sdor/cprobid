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

#ifndef DICTIONARY_AMINO_ACID
#define DICTIONARY_AMINO_ACID

class dictionary_amino_acid {
private:
	double rmw;
	char cod;
public:
	typedef dictionary_amino_acid* daaPtr;
	dictionary_amino_acid(void);
	dictionary_amino_acid(char C, double rmass);
	~dictionary_amino_acid(void);
	double ResidueMonoMw(void);

	char get_cod() const {return cod;};
};

inline bool operator == (const dictionary_amino_acid& a1, const dictionary_amino_acid& a2){
	return a1.get_cod() == a2.get_cod();
}

#endif
