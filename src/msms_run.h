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

#ifndef MSMS_RUN_H_
#define MSMS_RUN_H_
#include <string>
#include <vector>
#include <map>
#include "experimental_ion.h"
#include "search_parameters.h"
using namespace std;


class msms_run {
    string base_name;

    double minIonMw;
    double maxIonMw;
    string data_file;
public:

	enum conversion_software_type {
		mzStar,
		importWiff,
		massWolf,
		thermo2mzXML,
		generic_mzXML
	};

	conversion_software_type conversion_software;

    int min_charge;
    int max_charge;
    vector<experimental_ion> ions;
    pair<double,double> fragments_range;

    msms_run();
    virtual ~msms_run();
    void setBaseName(string base_name){this->base_name=base_name;}
    string getBaseName() const {return this->base_name;}
    void load_xml_data(const char* filename);
    void load_dta_data();
    vector<experimental_ion>* get_ions(){return &this->ions;};

    vector<double> get_precursors_mw() const;

    pair<vector<experimental_ion>::iterator, vector<experimental_ion>::iterator> precursor_mw_range(double mz, double delta_mass);
    void calculate_zscores();
    void save_result_xml(search_parameters* param);


    double get_max_precursor_mw(){return maxIonMw;}
    double get_min_precursor_mw(){return minIonMw;};

    string get_data_file_name() const {return data_file;};
    void print_ions();
private:
    void pre_process_data();
    void load_dta_file(const char* fileName);

    pair<double, double> get_precursor_fragments_range();

};

#endif /*MSMS_RUN_H_*/
