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

#ifndef DICTIONARY_AMINO_ACID_MODIFICATION
#define DICTIONARY_AMINO_ACID_MODIFICATION
#include <string>
#include <set>

#include "dictionary_amino_acid.h"

using namespace std;

class dictionary_amino_acid_modification {
private:
  string cod;
  double deltamw;
  string targets;
public:
  dictionary_amino_acid_modification(void);
  dictionary_amino_acid_modification(const char* cod,double delta_mass, const char* targets);
  ~dictionary_amino_acid_modification(void);
  double DeltaMonoMass(void);
  string Cod() const {return this->cod;}

  bool CanModify(char cod);

  // add amino acid with cod to targeted amino acid list
  void AddTarget(char aa);
  string modification_targets() const {return targets;};
};

typedef dictionary_amino_acid_modification amino_acid_modification;

inline bool operator == (const amino_acid_modification& m1, const amino_acid_modification& m2){
	return m1.Cod() == m2.Cod();
}

#endif
