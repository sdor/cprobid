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

#include "search_parameters.h"
#include <cstdlib>
#include <cstdio>
search_parameters::search_parameters()
{
}

search_parameters::~search_parameters()
{
}

void search_parameters::read_parametrs(char* file_name)
{
  if(access (file_name, R_OK) !=-1){
    string line;
    ifstream in;
    in.open(file_name,ios_base::in);
    do
    {
      getline(in,line,'\n');
      process_parameter_line(line);
    }
    while(!in.eof());
    in.close();
  }else{
    cout<<"File "<<file_name<<" does not exist or access is not permited\n";
    exit(0);
  }
}

void search_parameters::process_parameter_line(string s)
{

  istringstream in(s.c_str());
  string line;
  getline(in,line,'=');

  if(line == "ms_error")
  {
    string ms_error_str;
    getline(in,ms_error_str,'\n');
    ms_error=atof(ms_error_str.c_str());
  }else if(line == "msms_error")  {
    string msms_error_str;
    getline(in,msms_error_str,'\n');
    msms_error=atof(msms_error_str.c_str());
  }else if (line == "modification")  {
    string name;
    string delta_mass_str;
    string targets;
    getline(in,name,',');
    getline(in,delta_mass_str,',');
    double delta_mass=atof(delta_mass_str.c_str());
    getline(in,targets,'\n');
    Dictionary.AddAminoAcidModification(name.c_str(),delta_mass,targets.c_str());
    this->add_amino_acid_modification(name.c_str(),delta_mass,targets.c_str());
  }else if(line == "search_database") {
    getline(in,search_database);
  }else if(line == "base_name")  {
  	string base_name;
    getline(in,base_name);
    //istrstream summary_in(base_name.c_str());
    istringstream summary_in(base_name.c_str());
    this->data_files.push_back(base_name);
//    string summary_line;
//    while(!summary_in.eof())
//    {
//      getline(summary_in,summary_line,'/');
//    }
//    summary_name=summary_line;
  }else if(line == "max_num_internal_cleavages")  {
    string max_num_internal_cleavages_str;
    getline(in,max_num_internal_cleavages_str,'\n');
    max_num_internal_cleavages=atoi(max_num_internal_cleavages_str.c_str());
  }else if(line == "n_to_keep")  {
    string n_to_keep_str;
    getline(in,n_to_keep_str,'\n');
    n_to_keep=atoi(n_to_keep_str.c_str());
  }else  if(line == "n_to_out")  {
    string n_to_out_str;
    getline(in,n_to_out_str,'\n');
    n_to_out=atoi(n_to_out_str.c_str());
  }else if(line == "maximum_number_modification"){
  	string maximum_number_modification_str;
  	getline(in,maximum_number_modification_str,'\n');
  	maximum_number_modification=atoi(maximum_number_modification_str.c_str());
  }

}

void search_parameters::add_amino_acid_modification(const char* cod, double delta_mass, const char* targets){
	amino_acid_modification aam(cod, delta_mass,targets);
	this->amino_acid_modifications[cod]=aam;
}
