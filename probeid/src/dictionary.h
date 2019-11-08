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
#include<string>
#include <vector>
#include<map>
#include "dictionary_amino_acid.h"
#include "dictionary_amino_acid_modification.h"
#include "chemical_element.h"
#include "immonium_ion.h"

using namespace std;

class dictionary
{
private:
  typedef pair<char, dictionary_amino_acid*> cod_amino_acid;
  typedef map<char, dictionary_amino_acid*> amino_acid_dictionary;
  typedef map<basic_string<char>,chemical_element> Elements;
  map<basic_string<char>,chemical_element> chemical_elements;
  map<char,dictionary_amino_acid*> amino_acids;
  typedef pair <string, dictionary_amino_acid_modification*> cod_modification;
  typedef map<string,dictionary_amino_acid_modification*> amino_acid_modification_dictionary;
  map<basic_string<char>, dictionary_amino_acid_modification* > amino_acid_modifications;

public:

  //const dictionary* dataPtr=Data;

  dictionary(void);
  ~dictionary(void);
  dictionary_amino_acid* GetAminoAcid(char cod);
  dictionary_amino_acid_modification* get_amino_acid_modification(string cod);
  void AddAminoAcidModification(const char* cod, double delta_mass, const char* targets);
  vector<dictionary_amino_acid_modification*> get_amino_acid_modification();
  bool IsAminoAcidCod(char cod) const;
  char immonium_ion_cod(const ion* e);
  map<basic_string<char>, dictionary_amino_acid_modification* >* get_amino_acid_modifications(){return &amino_acid_modifications;}
private:

  void init_amino_acid_dictionary(void);

  void clear_amino_acid_dictionary(void);

  void clear_modification_dictionary(void);

};
static dictionary Dictionary;
static chemical_element Hydrogen("H",1.007825);
static chemical_element Oxygen("O",15.994915);
