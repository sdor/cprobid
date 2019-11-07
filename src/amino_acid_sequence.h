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

//#pragma once
#ifndef AMINO_ACID_SEQUENCE
#define AMINO_ACID_SEQUENCE
#include <iostream>
#include<vector>
#include <set>
#include <algorithm>
#include "dictionary.h"
#include "amino_acid.h"
#include "precursor_ion.h"
using namespace std;

typedef vector<double> double_vector;

struct modification_info
{
  int position;
  double mass;
  amino_acid_modification* aam;
};

class amino_acid_sequence
{
protected:
	vector<amino_acid> sequence;
public:
  amino_acid_sequence(void);
  amino_acid_sequence(const char *s);
  amino_acid_sequence(string s);
  ~amino_acid_sequence(void);

  double MonoMw(void) const;
  int number_of_modifications();

  amino_acid AminoAcidAt(int pos) const;

  vector<modification_info> get_modification_info() const;

  vector<modification_info> modification_sites(vector<amino_acid_modification*>* modifications) const;

  dictionary_amino_acid_modification* getNTerminalModification() const;

  dictionary_amino_acid_modification* getCTerminalModification() const;

  string SequenceString(void) const;

  string CompleteSequenceString(void) const ;

  vector<amino_acid>* get_sequence(){return &this->sequence;};
  const vector<amino_acid>* get_sequence() const {return &this->sequence;};

  bool contains_amino_acid(char cod) const;

  vector<amino_acid>::iterator begin(){return this->sequence.begin();}

  vector<amino_acid>::const_iterator begin() const {return this->sequence.begin();}

  vector<amino_acid>::const_iterator end() const {return this->sequence.end();}

  unsigned int size() const {return this->sequence.size();};

  int length(void) const;

  vector<amino_acid_sequence> derivatives(vector<amino_acid_modification*>* modifications, double max_mw, int max_mod_number);

  vector< vector<double> > cidf(int charge) const;
  vector< vector<double> > cidf() const;

  void set_sequence(string s);

  amino_acid& operator [](int i){ return this->sequence[i];}
  amino_acid_sequence& operator = (const amino_acid_sequence& s){
	  this->sequence.clear();
	  this->sequence.resize(s.size());
	  copy(s.begin(),s.end(),this->sequence.begin());
	  return *this;
  }

  amino_acid_sequence& reverse_sequence();

  unsigned int immonium_cod();

private:
	int next_modification_set(int mask[], int n);
	vector<int>* get_modification_set(int mask[], int n);
};

inline bool operator == (const amino_acid_sequence& aas1, const amino_acid_sequence& aas2)
{
  bool equal=true;
  if(aas1.size() == aas2.size())
  {
    vector<amino_acid>::const_iterator i1=aas1.begin();
    vector<amino_acid>::const_iterator i1end=aas1.end();
    vector<amino_acid>::const_iterator i2=aas2.begin();
    vector<amino_acid>::const_iterator i2end=aas1.end();

    while(i1 != i1end && i2 != i2end && equal)
    {
      equal=((*i1)==(*i2));
      i1++;
      i2++;
    }
  }
  else
  {
    equal=false;
  }
  //cout<<" "<<equal<<"\n";
  return equal;
  //return strcmp(aas1.CompleteSequenceString().c_str(), aas2.CompleteSequenceString().c_str()) == 0;
}

inline bool operator < (const amino_acid_sequence& s1, const amino_acid_sequence& s2)
{
return s1.MonoMw()<s2.MonoMw();
//   bool result=false;
//   if(s1.size()==s2.size())
//   {
//     for(unsigned int i=0;i<s1.size();i++)
//     {
//       if(s1.get_sequence()->at(i).get_dictionary_amino_acid()==s2.get_sequence()->at(i).get_dictionary_amino_acid())
//       {
//         if(s1.get_sequence()->at(i).get_amino_acid_modification() != s2.get_sequence()->at(i).get_amino_acid_modification())
//         {
//           return s1.get_sequence()->at(i).get_amino_acid_modification() < s2.get_sequence()->at(i).get_amino_acid_modification();
//         }
//       }
//       else
//       {
//         return s1.get_sequence()->at(i).get_dictionary_amino_acid()<s2.get_sequence()->at(i).get_dictionary_amino_acid();
//       }
//     }
//   }
//   else
//   {
//     result=s1.size()<s2.size();
//   }
//   return result;
  //  return strcmp(s1.CompleteSequenceString().c_str(), s2.CompleteSequenceString().c_str()) < 0;
}

inline bool amino_acid_sequence_less(const amino_acid_sequence& aas1, const amino_acid_sequence& aas2)
{
  //return lexicographical_compare(aas1.begin(),aas1.end(),aas2.begin(),aas2.end(),amino_acid_less);
  return aas1.CompleteSequenceString().compare(aas2.CompleteSequenceString());
}

inline bool operator == (const modification_info& mi1,const modification_info& mi2)
{
  return (mi1.position == mi2.position)&&(mi1.mass==mi2.mass);
}
#endif
