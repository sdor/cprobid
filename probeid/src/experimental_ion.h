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

#ifndef EXPERIMENTAL_ION
#define EXPERIMENTAL_ION
#include <pthread.h>

#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <cln/integer.h>
#include "search_parameters.h"
#include "dictionary.h"
#include "amino_acid_sequence.h"
#include "precursor_ion.h"
#include "immonium_ion.h"
#include "match_score.h"

using namespace std;
using namespace cln;

class experimental_ion: public precursor_ion {
public:
    experimental_ion(void);
    ~experimental_ion(void);
private:

    immonium_map immonium_list;

    vector<double> rscores;

    double itraq114;
    double itraq115;
    double itraq116;
    double itraq117;
    double time;
    string ion_name;
public:
	int num;
	int msLevel;
	int peaksCount;
    int stop_scan;
    int start_scan;
    unsigned int immonium_cod;
    map<unsigned int, double> immonium_intensities;

	vector<double> scores;
	vector<match_score> top_scores;

	cl_I mz_index;
	map<cl_I, pair<double,double> > mz_index_intensity_map;

    experimental_ion(string name, int start, int stop, double mz, int chrg, double area);
    experimental_ion(const experimental_ion& ion);
    experimental_ion(const experimental_ion* ion);
    void add_fragment(const ion* );
    void  truncate_peak_list();
    void  normalize_peak_list();
    void filter_peak_list_by_intensity(int intesity);
    double immonium_score(const amino_acid_sequence* s);
    double immonium_score(unsigned int immoniums);
    match_nmatch_pair matched_ions_score(const vector<double>* v, double msms_error);
    void add_score(double score);
    void add_rscore(double rscore);
    void add_top_score(match_score score, int n_to_keep);
    vector<double>* get_scores(){return &scores;};
    vector<match_score>* get_top_scores(){return &top_scores;};


    double mean_score();
    double score_varience();
    void calculate_zscores();
    void write_spectrum_query(ofstream& out, string msmsrun_name, int index, int max_out);

    double get_itraq114() const {return this->itraq114;};
    double get_itraq115() const {return this->itraq115;};
    double get_itraq116() const {return this->itraq116;};
    double get_itraq117() const {return this->itraq117;};
    int get_start_scan() const {return start_scan;};
    int get_stop_scan() const {return stop_scan;};
    string get_name() const {return this->ion_name;};

    void set_start_scan(int v){start_scan=v;};
    void set_stop_scan(int v){stop_scan=v;};
    void set_name(string value){ion_name=value;};
    void set_itraq114(double value){this->itraq114=value;};
    void set_itraq115(double value){this->itraq115=value;};
    void set_itraq116(double value){this->itraq116=value;};
    void set_itraq117(double value){this->itraq117=value;};

    void digitize(pair<double,double> range,double msms_error);
    match_nmatch_pair matched_score(cl_I index,map<cl_I, double>& mz_map, double msms_error);

protected:
    bool is_immonium_ion(const ion* );
    void write_search_result(ofstream& out, match_score* match, int rank);

};

inline bool less_experimental_ion_mw(const experimental_ion& ion1, const experimental_ion& ion2){
    return ion1.get_mw()<ion2.get_mw();
}
#endif
