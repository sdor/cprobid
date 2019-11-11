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

#ifndef IMMONIUM_ION
#define IMMONIUM_ION
#include <utility>
#include <map>
#include "ion.h"
#include "immonium_ion_cod.h"
using namespace std;
class immonium_ion :
	public ion
{
public:
	immonium_ion(void);
	immonium_ion(char cod, double mass, double area);
	~immonium_ion(void);



protected:
	// amino acid cod of immonium ion

	char cod;
};
typedef pair<char, immonium_ion> cod_immonium_ion_pair;
typedef map<char,immonium_ion> immonium_map;

#endif
