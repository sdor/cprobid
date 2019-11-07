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

#include <math.h>
#include <algorithm>
#include <iostream>
#include "dictionary.h"
#include "precursor_ion.h"

precursor_ion::precursor_ion(void):ion()
{
	//this->fragments=new vector<ion>();
	this->sorted_by_mz=false;
}

precursor_ion::~precursor_ion(void)
{
	//delete(this->fragments);
}

precursor_ion::precursor_ion(double mz, int chrg):ion(mz,chrg,0.0)
{
	//this->fragments=new vector<ion>();
	this->sorted_by_mz=false;
}


precursor_ion::precursor_ion(double mz, int chrg, double area)
:ion(mz, chrg, area)
{
	this->sorted_by_mz=false;
}

void precursor_ion::add_fragment(const ion& e) {
	vector<ion>::iterator i;
	mz_equal comparable;
	comparable.to_compare_with=e;
	if((i=find_if(this->fragments.begin(),this->fragments.end(),comparable)) != this->fragments.end()){
		i->intensity+=e.intensity;
	}else{
		ion fragment(e);
		this->fragments.push_back(fragment);
	}
}



double precursor_ion::get_sum_intensity(const double& mz, const double& msms_error){
	double result=0.0;

	vector<ion>::iterator i;
	pair<vector<ion>::iterator,vector<ion>::iterator> range=this->mz_range(mz,msms_error);

	for(i=range.first;i!=range.second;i++){
		result+=i->get_intensity();
	}
	return result;
}

void precursor_ion:: print_fragments(){
	vector<ion>::iterator i=fragments.begin();
	cout<<"Fragments number is :"<<fragments.size()<<endl;
	while(i!=fragments.end()){
		cout<<i->get_mz()<<endl;
		i++;
	}
}


pair<vector<ion>::iterator,vector<ion>::iterator> precursor_ion::mz_range(double mz, double delta_mass){
	if(!this->sorted_by_mz){
		this->sort_fragments_by_mz();
		this->sorted_by_mz=true;
	}
	double lowmz=mz-delta_mass;
	double highmz=mz+delta_mass;
	ion lowion(lowmz, 1, 0.0);
	ion highion(highmz,1, 0.0);
	pair<vector<ion>::iterator,vector<ion>::iterator> range;
	range.first=lower_bound(this->fragments.begin(), this->fragments.end(), lowion, less_ion_mz);
    range.second=upper_bound(this->fragments.begin(), this->fragments.end(),highion, less_ion_mz);
    return range;
}

void precursor_ion::sort_fragments_by_mz(void)
{
	sort(this->fragments.begin(),this->fragments.end(),less_ion_mz);
	this->sorted_by_mz=true;
}

double precursor_ion::min_fragment_mz(){
	if(!this->sorted_by_mz){
		this->sort_fragments_by_mz();
	}
	return this->get_fragments()->front().get_mz();
}

double precursor_ion::max_fragment_mz(){
	if(!this->sorted_by_mz){
		this->sort_fragments_by_mz();
	}
	return this->get_fragments()->back().get_mz();
}

