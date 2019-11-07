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

#ifndef PRECURSOR_ION
#define PRECURSOR_ION
#include <vector>
#include <map>
#include "ion.h"

using namespace std;
//typedef pair<vector<ion>::iterator,vector<ion>::iterator> ion_range;
class precursor_ion :public ion
{
protected:


	bool sorted_by_mz;
public:
	vector<ion> fragments;
//typedef pair <double, double> deltamass_area;
	precursor_ion(void);
	~precursor_ion(void);
	precursor_ion(double mz, int chrg);
	precursor_ion(double mz, int chrg, double area);
	void add_fragment(const ion& );
	vector<ion>* get_fragments(){return &fragments;};
	const vector<ion>* get_fragments() const {return &fragments;};


	pair<vector<ion>::iterator,vector<ion>::iterator> mz_range(double mz, double delta_mass);

	void normalize_fragments(void);
	void sort_fragments_by_mz(void);

	double get_sum_intensity(const double& mz, const double& msms_error);
	double min_fragment_mz();
	double max_fragment_mz();
	void print_fragments();
};

#endif
