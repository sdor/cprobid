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

#ifndef SEARCH_PARAMETERS_H_
#define SEARCH_PARAMETERS_H_
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "dictionary.h"
using namespace std;
class search_parameters
{
	typedef pair<string, amino_acid_modification> cod_modification;
	double ms_error;
	double msms_error;
	int n_to_keep;
	int n_to_out;
	int max_num_internal_cleavages;
	int maximum_number_modification;
	string search_database;
	vector<string> data_files;
	map<string, amino_acid_modification> amino_acid_modifications;
public:
	search_parameters();
	virtual ~search_parameters();

	void set_ms_error(double value){ms_error=value;};
	void set_msms_error(double value){msms_error=value;};
	void set_n_to_keep(int value){n_to_keep=value;};
	void set_n_to_out(int value){n_to_out=value;};
	void set_max_num_internal_cleavages(int value){max_num_internal_cleavages=value;};
	void set_maximum_number_modification(int value){maximum_number_modification=value;};

	double get_ms_error(){return ms_error;}
	double get_msms_error(){return msms_error;}
	int get_n_to_keep(){return n_to_keep;};
	int get_n_to_out(){return n_to_out;};
	int get_max_num_internal_cleavages(){return max_num_internal_cleavages;};
	int get_maximum_number_modification(){return maximum_number_modification;};
	string get_search_database(){return search_database;};
	map<string, amino_acid_modification>* get_amino_acid_modifications(){return &this->amino_acid_modifications;};
	void add_amino_acid_modification(const char* cod, double delta_mass, const char* targets);
	vector<string>* get_data_files(){return &data_files;}
	void read_parametrs(char* file_name);
private:
    void process_parameter_line(string s);
};

#endif /*SEARCH_PARAMETERS_H_*/
