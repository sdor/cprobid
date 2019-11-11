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

#include "protein.h"
#include <sstream>
using namespace std;
protein::protein(void)
{
}

protein::protein(string fasta_entry){
  if (fasta_entry != "")
  {
    istringstream in(fasta_entry.c_str());
    string line;

    getline(in,line,'\n');
    istringstream title(line.c_str());
    string accession;
    getline(title,accession,' ');
    this->set_accession(accession);
    this->description="";
    string tmp;
    while(!title.eof())
    {
      getline(title,tmp,' ');
      if(tmp !="")
        this->description+=tmp+" ";
    }

    // read sequence
    string sequence="";
    while(!in.eof())
    {
      getline(in,line,'\n');
      if(line !="")
        sequence+=line;
    }
    this->set_sequence(sequence);
  }

}

protein::protein(string accession, string description, string sequence)
:amino_acid_sequence(sequence){
	this->accession=accession;
	this->description=description;
}

protein::~protein(void)
{
}

vector<aas_fragment> protein::digest(string sites, int nmissed)
{
  vector<aas_fragment> peptides;
  //	string::size_type npos = -1;
  vector<amino_acid>::iterator fragment_begin;
  vector<amino_acid>::iterator fragment_end;
  if(this->get_sequence()->size()>2)
  {
    vector<amino_acid>::iterator i=this->get_sequence()->begin();
    i++;
    vector<amino_acid>::iterator theEnd=this->get_sequence()->end();
    theEnd--;
    fragment_begin=i;
    fragment_end=i;
    for(;i!=theEnd;i++)
    {
      if(sites.find(i->get_dictionary_amino_acid()->get_cod()) != string::npos)
      {
        fragment_end=i;
        char front_char;
        char end_char;
        vector<amino_acid>::iterator front=fragment_begin;
        front--;
        front_char=front->get_dictionary_amino_acid()->get_cod();
        if(front_char=='<')
        {
          front_char='-';
        }
        vector<amino_acid>::iterator end=fragment_end;
        end++;
        end_char=end->get_dictionary_amino_acid()->get_cod();
        if(end_char=='>')
        {
          end_char='-';
        }
        aas_fragment aasf(this->get_accession(),front_char,fragment_begin,fragment_end,end_char);
        peptides.push_back(aasf);
        fragment_begin=fragment_end;
        fragment_begin++;
      }
    }

    vector<aas_fragment> tmp;
    vector<aas_fragment>::iterator j;
    vector<aas_fragment>::iterator k=peptides.begin();

    int l=0;
    for(j=peptides.begin(); j != peptides.end(); j++)
    {
      if(l==nmissed)
      {
        l=0;
        char front_char;
        char end_char;
        vector<amino_acid>::iterator front=k->begin();
        front--;
        front_char=front->get_dictionary_amino_acid()->get_cod();
        if(front_char=='<')
        {
          front_char='-';
        }

        vector<amino_acid>::iterator end=j->end();
        end++;
        end_char=end->get_dictionary_amino_acid()->get_cod();
        if(end_char=='>')
        {
          end_char='-';
        }

        aas_fragment aasf(this->get_accession(),front_char,k->begin(),j->end(),end_char);
        tmp.push_back(aasf);


        k=j;
      }
      l++;
    }
    peptides.insert(peptides.end(),tmp.begin(),tmp.end());
  }
  return peptides;
}

