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

#include "dictionary.h"

dictionary::dictionary(void)
{
  this->init_amino_acid_dictionary();
}

dictionary::~dictionary(void)
{
  this->clear_amino_acid_dictionary();
  this->clear_modification_dictionary();
}


dictionary_amino_acid* dictionary::GetAminoAcid(char cod)
{
  dictionary_amino_acid* ptr=NULL;
  amino_acid_dictionary:: const_iterator i;
  if((i=this->amino_acids.find(cod)) != this->amino_acids.end())
  {
    ptr=i->second;
    //dictionary_amino_acid aa=this->amino_acids[cod];
    //ptr=this->amino_acids[cod];
  }
  return ptr;
}

// returns pointer for amino acid modification in dictionary
dictionary_amino_acid_modification* dictionary::get_amino_acid_modification(string cod)
{
  dictionary_amino_acid_modification* ptr=NULL;
  amino_acid_modification_dictionary::const_iterator i;
  i=amino_acid_modifications.find(cod);
  if(i != amino_acid_modifications.end()){
    ptr=i->second;
  }
  return ptr;
}

// returns all available amino acid modifications
vector<dictionary_amino_acid_modification*> dictionary::get_amino_acid_modification()
{
  vector<dictionary_amino_acid_modification*> modifications;
  map<basic_string<char>, dictionary_amino_acid_modification* >::iterator i;
  for(i=this->amino_acid_modifications.begin();i != this->amino_acid_modifications.end();i++)
  {
    modifications.push_back(i->second);
  }
  return modifications;
}
// initialize amino acids
void dictionary::init_amino_acid_dictionary(void)
{
  this->amino_acids.insert(cod_amino_acid('<',new dictionary_amino_acid('<', 0.0))); // n-terminal
  this->amino_acids.insert(cod_amino_acid('>',new dictionary_amino_acid('>', 0.0))); // c-terminal
  this->amino_acids.insert(cod_amino_acid('G',new dictionary_amino_acid('G', 57.02146360)));  //G
  this->amino_acids.insert(cod_amino_acid('A',new dictionary_amino_acid('A', 71.03711360)));  //A
  this->amino_acids.insert(cod_amino_acid('S',new dictionary_amino_acid('S', 87.03202820)));  //S
  this->amino_acids.insert(cod_amino_acid('P',new dictionary_amino_acid('P', 97.05276360)));  //P
  this->amino_acids.insert(cod_amino_acid('V',new dictionary_amino_acid('V', 99.06841360)));  //V
  this->amino_acids.insert(cod_amino_acid('T',new dictionary_amino_acid('T', 101.0476782)));  //T
  this->amino_acids.insert(cod_amino_acid('C',new dictionary_amino_acid('C', 103.0091854)));  //C
  this->amino_acids.insert(cod_amino_acid('L',new dictionary_amino_acid('L', 113.0840636)));  //L
  this->amino_acids.insert(cod_amino_acid('I',new dictionary_amino_acid('I', 113.0840636)));  //I
  this->amino_acids.insert(cod_amino_acid('X',new dictionary_amino_acid('X', 113.0840636)));  //X
  this->amino_acids.insert(cod_amino_acid('N',new dictionary_amino_acid('N', 114.0429272)));  //N
  this->amino_acids.insert(cod_amino_acid('O',new dictionary_amino_acid('O', 114.0793126)));  //O
  this->amino_acids.insert(cod_amino_acid('B',new dictionary_amino_acid('B', 114.5349350)));  //B
  this->amino_acids.insert(cod_amino_acid('D',new dictionary_amino_acid('D', 115.0269428)));  //D
  this->amino_acids.insert(cod_amino_acid('Q',new dictionary_amino_acid('Q', 128.0585772)));  //Q
  this->amino_acids.insert(cod_amino_acid('K',new dictionary_amino_acid('K', 128.0949626)));  //K
  this->amino_acids.insert(cod_amino_acid('Z',new dictionary_amino_acid('Z', 128.5505850)));  //Z
  this->amino_acids.insert(cod_amino_acid('E',new dictionary_amino_acid('E', 129.0425928)));  //E
  this->amino_acids.insert(cod_amino_acid('M',new dictionary_amino_acid('M', 131.0404854)));  //M
  this->amino_acids.insert(cod_amino_acid('H',new dictionary_amino_acid('H', 137.0589116)));  //H
  this->amino_acids.insert(cod_amino_acid('F',new dictionary_amino_acid('F', 147.0684136)));  //F
  this->amino_acids.insert(cod_amino_acid('R',new dictionary_amino_acid('R', 156.1011106)));  //R
  this->amino_acids.insert(cod_amino_acid('Y',new dictionary_amino_acid('Y', 163.0633282)));  //Y
  this->amino_acids.insert(cod_amino_acid('W',new dictionary_amino_acid('W', 186.0793126)));  //W
}

void dictionary::clear_amino_acid_dictionary(void)
{
  amino_acid_dictionary::iterator i;
  i=this->amino_acids.begin();
  while(i != this->amino_acids.end())
  {
    dictionary_amino_acid* ptr;
    ptr=i->second;
    delete(ptr);
    i++;
  }
}

// clear amino acid modification dictionary
void dictionary::clear_modification_dictionary(void)
{
  amino_acid_modification_dictionary::iterator i;
  i=this->amino_acid_modifications.begin();
  while(i!=this->amino_acid_modifications.end())
  {
    dictionary_amino_acid_modification* ptr;
    ptr=i->second;
    delete(ptr);
    i++;
  }
}
// adds new amino acid modification in amino acid modification dictionary
void dictionary::AddAminoAcidModification(const char* cod, double delta_mass,const char* targets)
{
  this->amino_acid_modifications.insert(cod_modification(cod,new dictionary_amino_acid_modification(cod, delta_mass,targets)));
}
// returns true if cod is amino acid cod
bool dictionary::IsAminoAcidCod(char cod) const
{
  return amino_acids.find(cod) != amino_acids.end();
}

char dictionary::immonium_ion_cod(const ion* e)
{
  if (e->get_mz() >= 85.8 && e->get_mz() <= 86.2)
    return 'L';
  if (e->get_mz() >= 69.8 && e->get_mz() <= 70.2)
    return 'P';
  if (e->get_mz() >= 109.8 && e->get_mz() <= 110.2)
    return 'H';
  if (e->get_mz() >= 119.8 && e->get_mz() <= 120.2)
    return 'F';
  if (e->get_mz() >= 135.8 && e->get_mz() <= 136.2)
    return 'Y';
  if (e->get_mz() >= 158.8 && e->get_mz() <= 159.2)
    return 'W';
  return 'j';
}
