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

#ifndef ION
#define ION
#include <vector>

using namespace std;
class ion
{

private:


	bool mwcomputed;
	double mw;

public:

	int charge;
	double mz;
	double intensity;

	ion(void);
	~ion(void);
	ion(double mz, int chrg, double area);
	//ion(double mz, double area);
	ion(const ion* e);
	ion(const ion& e);

	int  get_charge(void) const{return this->charge;};
	double get_mz(void) const{return this->mz;};
	double get_mw(void) const;
	double get_intensity(void) const {return this->intensity;};
//	void compute_mw();

	ion& operator = (const ion& e);
	void set_intensity(double v){this->intensity=v;};
	//operator double(){return this->mz;};
	void set_mz(double v){this->mz=v;};
	void set_charge(int v){this->charge=v;};
	void set_mw(double v){mw=v;};
};

typedef vector<ion> ion_vector;
inline bool less_ion_mz(const ion& ion1, const ion& ion2){
	return ion1.get_mz()<ion2.get_mz();
}

inline bool less_ion_mw(const ion& ion1, const ion& ion2){
	return ion1.get_mw()<ion2.get_mw();
}

inline bool less_ion_area(const ion& ion1, const ion& ion2){
	return ion1.get_intensity()<ion2.get_intensity();
}

inline bool equal_mz(const ion& ion1, const ion& ion2){
	return (ion1.mz==ion2.mz);
}

class mz_equal{
public:
	ion to_compare_with;
	bool operator ()(const ion& e){
		return (to_compare_with.mz == e.mz);
	}
};

#endif
