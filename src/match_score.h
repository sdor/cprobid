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

#ifndef MATCH_SCORE
#define MATCH_SCORE
#include <vector>
using namespace std;

struct match_score{
	string accession;
	string peptide;
	int nterms;
	//string complete_seq;
	vector<modification_info> vinfo;
	char prev_aa;
	char next_aa;
	double n_term_mass;
	double c_term_mass;
	double score;
	double zscore;
	int nmatched;
	int ntotal;
	double neutral_mass;
	double delta_mass;
};

struct match_nmatch_pair{
	double score;
	int nmatched;
};

inline bool less_score(match_score s1,match_score s2){
	return s1.score<s2.score ;
}

inline bool more_zscore(match_score s1,match_score s2){
	return s1.zscore>s2.zscore;
}

inline bool operator == (const match_score& ms1,const match_score& ms2){
	bool result;
	result= (ms1.peptide == ms2.peptide)&&(ms1.c_term_mass == ms2.c_term_mass)&&(ms1.n_term_mass==ms2.n_term_mass)&&(ms1.vinfo == ms2.vinfo);
	return result;
}
#endif
