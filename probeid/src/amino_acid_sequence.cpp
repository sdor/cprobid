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

#include <cstdio>
#include <iostream>
#include <math.h>
#include <gsl/gsl_combination.h>
#include <map>
#include <algorithm>
#include <numeric>
#include <stack>
#include <deque>
#include <string.h>
#include <sstream>
#include "amino_acid_sequence.h"
#include "dictionary.h"

using namespace std;

amino_acid_sequence::amino_acid_sequence(void){

}

amino_acid_sequence::amino_acid_sequence(string s)
{
  int n;
  if((n=(int)s.length())>0)
  {
    amino_acid ntaa('<');
    this->sequence.push_back(ntaa);
    for(int i=0;i<n;i++)
    {
      if(Dictionary.IsAminoAcidCod(s[i]))
      {
        amino_acid aa(s[i]);
        this->sequence.push_back(aa);
      }
    }
    amino_acid ctaa('>');
    this->sequence.push_back(ctaa);
  }
}

void amino_acid_sequence::set_sequence(string s)
{
  int n;
  if((n=(int)s.length())>0)
  {
    amino_acid ntaa('<');
    this->sequence.push_back(ntaa);
    for(int i=0;i<n;i++)
    {
      if(Dictionary.IsAminoAcidCod(s[i]))
      {
        amino_acid aa(s[i]);
        this->sequence.push_back(aa);
      }
    }
    amino_acid ctaa('>');
    this->sequence.push_back(ctaa);
  }
}

amino_acid_sequence::amino_acid_sequence(const char *s)
{
  int n=(int)strlen(s);
  if(n>0)
  {
    amino_acid ntaa('<');
    this->sequence.push_back(ntaa);
    for(int i=0;i<n;i++)
    {
      if(Dictionary.IsAminoAcidCod(s[i]))
      {
        amino_acid aa(s[i]);
        this->sequence.push_back(aa);
      }
    }
    amino_acid ctaa('>');
    this->sequence.push_back(ctaa);
  }
}

amino_acid_sequence::~amino_acid_sequence(void)
{}

// Mono isotopic Mw of amino aid sequence
double amino_acid_sequence::MonoMw(void) const
{
    double mw=0.0;
    mw=accumulate(this->sequence.begin(),this->sequence.end(),mw);
    mw+=Oxygen.MonoMass()+Hydrogen.MonoMass()+Hydrogen.MonoMass();
    return mw;
}

amino_acid amino_acid_sequence::AminoAcidAt(int pos) const
{
  return this->sequence[pos];
}


string amino_acid_sequence::SequenceString(void) const
{
  string s="";
  if(this->sequence.size()>2)
  {
    for(unsigned int i=1;i<this->sequence.size()-1;i++)
    {

      s+=(this->sequence[i]).get_dictionary_amino_acid()->get_cod();
    }
  }
  return s;
}

string amino_acid_sequence::CompleteSequenceString(void) const
{
  string s="";
  for(vector<amino_acid>::const_iterator i=this->sequence.begin(); i != this->sequence.end();i++)
  {
    if(i->get_dictionary_amino_acid() != NULL)
    {
      s+=i->get_dictionary_amino_acid()->get_cod();
      if (i->get_amino_acid_modification() != NULL)
      {
        s+="("+i->get_amino_acid_modification()->Cod()+")";
      }
    }
  }
  return s;
}



vector<modification_info> amino_acid_sequence::get_modification_info() const
{
  vector<modification_info> v;
  if(this->sequence.size() > 2)
  {
    int index=1;
    for(unsigned int i=1;i<this->sequence.size()-1;i++)
    {
      if((this->sequence[i]).get_amino_acid_modification() != NULL)
      {
        modification_info info;
        info.position=index;
        info.mass=(this->sequence[i]).ResidueMonoMw();
        info.aam=(this->sequence[i]).get_amino_acid_modification();
        v.push_back(info);
      }
      index++;
    }
  }
  return v;
}

vector< vector<double> > amino_acid_sequence::cidf() const {
	  vector< vector<double> > vv;
	  vector<double> v1;
	  vector<double> v2;
	  vector<double> v3;

	  double thisMw=this->MonoMw();

	  double b_mw=this->sequence.begin()->ResidueMonoMw();

	  double b_mwz;
	  double y_mw;
	  double y_mwz;
	  for(unsigned int i=1;i<this->sequence.size()-2;i++)
	  {
	    b_mw+=(this->sequence[i]).ResidueMonoMw();
	    b_mwz=b_mw+Hydrogen.MonoMass();
	    y_mw=thisMw-b_mw;
	    y_mwz=y_mw+Hydrogen.MonoMass();
	    v1.push_back(b_mwz);

	    v1.push_back(y_mwz);
        v2.push_back(Hydrogen.MonoMass()+b_mw/2);
        v2.push_back(Hydrogen.MonoMass()+y_mw/2);
        v3.push_back(Hydrogen.MonoMass()+b_mw/3);
        v3.push_back(Hydrogen.MonoMass()+y_mw/3);
	  }
	  vv.push_back(v1);
	  vv.push_back(v2);
	  vv.push_back(v3);
	  return vv;
}

vector< vector<double> > amino_acid_sequence::cidf(int charge) const
{
  vector< vector<double> > vv;
  vector<double> v1;
  vector<double> v2;
  vector<double> v3;

  double thisMw=this->MonoMw();

  double b_mw=this->sequence.begin()->ResidueMonoMw();

  double b_mwz;
  double y_mw;
  double y_mwz;
  for(unsigned int i=1;i<this->sequence.size()-2;i++)
  {
    b_mw+=(this->sequence[i]).ResidueMonoMw();
    b_mwz=b_mw+Hydrogen.MonoMass();
    y_mw=thisMw-b_mw;
    y_mwz=y_mw+Hydrogen.MonoMass();
    v1.push_back(b_mwz);

    v1.push_back(y_mwz);

    if(charge > 2){
        v2.push_back(Hydrogen.MonoMass()+b_mw/2);
        v2.push_back(Hydrogen.MonoMass()+y_mw/2);
        v3.push_back(Hydrogen.MonoMass()+b_mw/3);
        v3.push_back(Hydrogen.MonoMass()+y_mw/3);
    }
  }
  vv.push_back(v1);
  vv.push_back(v2);
  vv.push_back(v3);
  return vv;
}


int amino_acid_sequence::length(void) const
{
  int result;
  int l;
  if((l=(int)this->sequence.size()) > 2)
  {
    result=l-2;
  }
  else
  {
    result=0;
  }
  return result;
}

bool amino_acid_sequence::contains_amino_acid(char cod)const
{
  for(vector<amino_acid>::const_iterator  i=this->sequence.begin();i<this->sequence.end();i++)
  {
    if(i->get_dictionary_amino_acid()->get_cod() == cod)
    {
      return true;
    }
  }
  return false;
}

int amino_acid_sequence::number_of_modifications()
{
  int result=0;
  vector<amino_acid>:: iterator i;
  for(i=this->sequence.begin();i!=this->sequence.end();i++)
  {
    if(i->get_amino_acid_modification() != NULL)
    {
      result++;
    }
  }
  return result;
}


dictionary_amino_acid_modification* amino_acid_sequence::getNTerminalModification() const
{
  amino_acid aa=this->sequence[0];
  return aa.get_amino_acid_modification();
}

dictionary_amino_acid_modification* amino_acid_sequence::getCTerminalModification() const
{
  amino_acid aa=this->sequence[this->sequence.size()-1];
  return aa.get_amino_acid_modification();
}


vector<modification_info> amino_acid_sequence::modification_sites(vector<amino_acid_modification*>* modifications) const {
	vector<modification_info> v;
	vector< amino_acid >::const_iterator i;
	vector<amino_acid_modification*>::iterator j;
	int pos=0;
	for(i=this->sequence.begin(); i != this->sequence.end(); i++, pos++){
		for(j=modifications->begin(); j != modifications->end(); j++){
			if ((*j)->CanModify(i->get_dictionary_amino_acid()->get_cod())) {
				modification_info minfo;
				minfo.position=pos;
				minfo.mass=i->ResidueMonoMw()+(*j)->DeltaMonoMass();
				minfo.aam=*j;
				v.push_back(minfo);
			}
		}
	}
	return v;
}


int amino_acid_sequence::next_modification_set(int mask[], int n) {
	int i;
	for (i = 0; (i < n) && mask[i]; ++i){
		mask[i] = 0;
	}

	if (i < n) {
		mask[i] = 1;
		return 1;
	}
	return 0;
}

vector<int>* amino_acid_sequence::get_modification_set(int mask[], int n) {
	vector<int>* v=new vector<int>();
	int i;
	for (i = 0; i < n ; ++i){
		if (mask[i]){
			v->push_back(i);
		}
	}
	return v;
}


vector<amino_acid_sequence> amino_acid_sequence::derivatives(vector<amino_acid_modification*>* modifications, double maxMw, int max_mod_number){
	vector<amino_acid_sequence> result;
	double mw=this->MonoMw();
	if (mw<=maxMw) {
		if (!modifications->empty()) {
			vector<modification_info> sites=
					this->modification_sites(modifications);
			if (!sites.empty()) {
				vector<unsigned int> positions;
				positions.resize(this->sequence.size());
				size_t n=sites.size();
				size_t k=max_mod_number;
				if (n<=k) {
					k=n;
				}
				for (size_t j=0; j<=k; j++) {
					gsl_combination * c=gsl_combination_calloc(n, j);
					if (c != NULL) {
						do {
							positions.assign(positions.size(),0);
							unsigned int max_mod_per_site=0;
							vector<int> mindex;
							mindex.resize(j);
							for (size_t i=0; i<j; i++) {
								size_t cel=gsl_combination_get(c, i);
								modification_info site;
								site=sites[cel];
								positions[site.position]+=1;
								if(max_mod_per_site<positions[site.position]){
									max_mod_per_site=positions[site.position];
								}
								mindex[i]=cel;
								//cout<<cel<<" ";
							}
							if (max_mod_per_site<2) {
								double delta_mw=0.0;
								vector<int>::iterator imindex;
								for (imindex=mindex.begin(); imindex!=mindex.end(); imindex++) {
									delta_mw+=(sites[*imindex]).aam->DeltaMonoMass();
								}
								if ((mw+delta_mw)<=maxMw) {
									amino_acid_sequence s=*this;
									for (imindex=mindex.begin(); imindex!=mindex.end(); imindex++) {
										s[(sites[*imindex]).position].modify((sites[*imindex]).aam);
									}
									result.push_back(s);
								}
							}
							//cout<<endl;
						} while (gsl_combination_next(c) == GSL_SUCCESS);
					}
					gsl_combination_free(c);
				}
			}
		}
		result.push_back(*this);
	}
	return result;
}

amino_acid_sequence& amino_acid_sequence::reverse_sequence(){
	vector<amino_acid> reversed;
	reversed.resize(this->sequence.size());
	copy(this->sequence.begin(),this->sequence.end(),reversed.begin());
	vector<amino_acid>::iterator begin;
	vector<amino_acid>::iterator end;
	vector<amino_acid>::iterator rbegin;
	begin=this->sequence.begin();
	begin++;
	end=this->sequence.end();
	end--;
	rbegin=reversed.begin();
	rbegin++;
	reverse_copy(begin,end,rbegin);
	this->sequence=reversed;
	return *this;
}

unsigned int amino_acid_sequence::immonium_cod(){
	unsigned int result=0;
	unsigned int immonium_L_mask=(1<<0);//L
	unsigned int immonium_H_mask=(1<<1);//H
	unsigned int immonium_F_mask=(1<<2);//F;
	unsigned int immonium_Y_mask=(1<<3);//Y;
	unsigned int immonium_W_mask=(1<<4);//W;
	unsigned int immonium_P_mask=(1<<5);
	string seq=this->SequenceString();
	if(strchr(seq.c_str(),'L') != 0){
		result=result | immonium_L_mask;
	}
	if(strchr(seq.c_str(),'H') != 0){
		result=result | immonium_H_mask;
	}
	if(strchr(seq.c_str(),'F') != 0){
		result=result | immonium_F_mask;
	}
	if(strchr(seq.c_str(),'Y') != 0){
		result=result | immonium_Y_mask;
	}
	if(strchr(seq.c_str(),'W') != 0){
		result=result | immonium_W_mask;
	}
	if(strchr(seq.c_str(),'P') != 0){
		result=result | immonium_P_mask;
	}
	return result;
}
