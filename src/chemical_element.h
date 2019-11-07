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

#ifndef CHEMICAL_ELIMENT
#define CHEMICAL_ELIMENT
#include <string>
using namespace std;
class chemical_element
{
public:
	chemical_element(void);
	chemical_element(string Name,double momo_mass);
	~chemical_element(void);
	// monoisotopic molecular weight
	double MonoMass(void);
private:
	// monoisotopic mass
	double mmmass;
public:
	// element name
	string Name(void) ;
private:
	// element name
	string name;
};
#endif

