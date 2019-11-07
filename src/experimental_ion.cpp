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

#include <cmath>

#include "experimental_ion.h"



experimental_ion::experimental_ion(void) {
    this->start_scan=0;
    this->stop_scan=0;
    this->itraq114=0.0;
    this->itraq115=0.0;
    this->itraq116=0.0;
    this->itraq117=0.0;
    immonium_cod=0;
}

experimental_ion::~experimental_ion(void) {
}

experimental_ion::experimental_ion(string name, int start, int stop, double mz, int chrg, double area)
:precursor_ion(mz, chrg, area) {
    this->ion_name=name;
    this->start_scan=start;
    this->stop_scan=stop;
    this->itraq114=0.0;
    this->itraq115=0.0;
    this->itraq116=0.0;
    this->itraq117=0.0;
    immonium_cod=0;
}

experimental_ion::experimental_ion(const experimental_ion& ion)
:precursor_ion(ion.get_mz(), ion.get_charge(), ion.get_intensity()) {
    this->ion_name=ion.get_name();
    this->start_scan=ion.get_start_scan();
    this->stop_scan=ion.get_stop_scan();
    this->fragments.resize(ion.get_fragments()->size());
    copy(ion.get_fragments()->begin(), ion.get_fragments()->end(), this->fragments.begin());
    this->itraq114=ion.get_itraq114();
    this->itraq115=ion.get_itraq115();
    this->itraq116=ion.get_itraq116();
    this->itraq117=ion.get_itraq117();
    immonium_cod=0;
}

experimental_ion::experimental_ion(const experimental_ion* ion)
:precursor_ion(ion->get_mz(), ion->get_charge(), ion->get_intensity()) {
    this->ion_name=ion->get_name();
    this->start_scan=ion->get_start_scan();
    this->stop_scan=ion->get_stop_scan();
    this->fragments.resize(ion->get_fragments()->size()+1);
    copy(ion->get_fragments()->begin(), ion->get_fragments()->end(), this->fragments.begin());
    this->itraq114=ion->get_itraq114();
    this->itraq115=ion->get_itraq115();
    this->itraq116=ion->get_itraq116();
    this->itraq117=ion->get_itraq117();
    immonium_cod=ion->immonium_cod;
}


bool experimental_ion::is_immonium_ion(const ion* e){
    if (e->get_mz()>= 85.8 && e->get_mz() <= 86.2)
        return true;
    if (e->get_mz() >= 69.8 && e->get_mz() <= 70.2)
        return true;
    if (e->get_mz() >= 109.8 && e->get_mz() <= 110.2)
        return true;
    if (e->get_mz() >= 119.8 && e->get_mz() <= 120.2)
        return true;
    if (e->get_mz() >= 135.8 && e->get_mz() <= 136.2)
        return true;
    if (e->get_mz() >= 158.8 && e->get_mz() <= 159.2)
        return true;
    return false;
}

void experimental_ion::add_fragment(const ion* e){

    	unsigned int immonium_L_mask=(1<<0);//L
    	unsigned int immonium_H_mask=(1<<1);//H
    	unsigned int immonium_F_mask=(1<<2);//F;
    	unsigned int immonium_Y_mask=(1<<3);//Y;
    	unsigned int immonium_W_mask=(1<<4);//W;
    	unsigned int immonium_P_mask=(1<<5);//P

    	if (e->get_mz() >= 85.8 && e->get_mz() <= 86.2){
    	    //return 'L';
    		immonium_cod=immonium_cod | immonium_L_mask;
    		if(immonium_intensities.find(immonium_L_mask) != immonium_intensities.end()){
    			immonium_intensities[immonium_L_mask]=immonium_intensities[immonium_L_mask]+e->intensity;
    		}else{
    			immonium_intensities[immonium_L_mask]=e->intensity;
    		}
    	}
    	if (e->get_mz() >= 69.8 && e->get_mz() <= 70.2){
    		//return 'P';
    		immonium_cod=immonium_cod | immonium_P_mask;
    		if(immonium_intensities.find(immonium_P_mask) != immonium_intensities.end()){
    			immonium_intensities[immonium_P_mask]=immonium_intensities[immonium_P_mask]+e->intensity;
    		}else{
    			immonium_intensities[immonium_P_mask]=e->intensity;
    		}

    	}
    	if (e->get_mz() >= 109.8 && e->get_mz() <= 110.2){
    	    //return 'H';
    		immonium_cod=immonium_cod | immonium_H_mask;
    		if(immonium_intensities.find(immonium_H_mask) != immonium_intensities.end()){
    			immonium_intensities[immonium_H_mask]=immonium_intensities[immonium_H_mask]+e->intensity;
    		}else{
    			immonium_intensities[immonium_H_mask]=e->intensity;
    		}
    	}
    	if (e->get_mz() >= 119.8 && e->get_mz() <= 120.2){
    	    //return 'F';
    		immonium_cod=immonium_cod | immonium_F_mask;
    		if(immonium_intensities.find(immonium_F_mask) != immonium_intensities.end()){
    			immonium_intensities[immonium_F_mask]=immonium_intensities[immonium_F_mask]+e->intensity;
    		}else{
    			immonium_intensities[immonium_F_mask]=e->intensity;
    		}
    	}
    	if (e->get_mz() >= 135.8 && e->get_mz() <= 136.2){
    	    //return 'Y';
    		immonium_cod=immonium_cod | immonium_Y_mask;
    		if(immonium_intensities.find(immonium_Y_mask) != immonium_intensities.end()){
    			immonium_intensities[immonium_Y_mask]=immonium_intensities[immonium_Y_mask]+e->intensity;
    		}else{
    			immonium_intensities[immonium_Y_mask]=e->intensity;
    		}
    	}
    	if (e->get_mz() >= 158.8 && e->get_mz() <= 159.2){
    	    //return 'W';
    		immonium_cod=immonium_cod | immonium_W_mask;
    		if(immonium_intensities.find(immonium_L_mask) != immonium_intensities.end()){
    			immonium_intensities[immonium_W_mask]=immonium_intensities[immonium_W_mask]+e->intensity;
    		}else{
    			immonium_intensities[immonium_W_mask]=e->intensity;
    		}
    	}

        char c=Dictionary.immonium_ion_cod(e);
        immonium_ion ie(c, e->get_mz(), e->get_intensity());
        this->immonium_list.insert(cod_immonium_ion_pair(c, ie));

        precursor_ion::add_fragment(e);

}

double experimental_ion::immonium_score(const amino_acid_sequence* s) {
    double score = 0.0;
    for(immonium_map::iterator i=this->immonium_list.begin();i != this->immonium_list.end();i++){
        if(s->contains_amino_acid(i->first)){
            score+=log(i->second.get_intensity());
        }
    }
    return score;
}

double experimental_ion::immonium_score(unsigned int immoniums) {
	unsigned int immonium_L_mask=(1<<0);//L
	unsigned int immonium_H_mask=(1<<1);//H
	unsigned int immonium_F_mask=(1<<2);//F;
	unsigned int immonium_Y_mask=(1<<3);//Y;
	unsigned int immonium_W_mask=(1<<4);//W;
	unsigned int immonium_P_mask=(1<<5);//P

    double score = 0.0;

    unsigned int immonium_cod_common=immoniums & this->immonium_cod;

    if(immonium_cod_common != 0){
		if (immonium_cod_common & immonium_L_mask == immonium_L_mask ) {
			score+=log(this->immonium_intensities[immonium_L_mask]);
		}
		if((immonium_cod_common & immonium_H_mask) == immonium_H_mask) {
			score+=log(this->immonium_intensities[immonium_H_mask]);
		}
		if((immonium_cod_common & immonium_F_mask) == immonium_F_mask) {
			score+=log(this->immonium_intensities[immonium_F_mask]);
		}

		if((immonium_cod_common & immonium_Y_mask) == immonium_Y_mask) {
			score+=log(this->immonium_intensities[immonium_Y_mask]);
		}

		if((immonium_cod_common & immonium_W_mask) == immonium_W_mask) {
			score+=log(this->immonium_intensities[immonium_W_mask]);
		}

		if((immonium_cod_common & immonium_P_mask) == immonium_P_mask) {
			score+=log(this->immonium_intensities[immonium_P_mask]);
		}

    }
    return score;
}

match_nmatch_pair experimental_ion::matched_ions_score(const vector<double>* v, double msms_error){
    match_nmatch_pair match;
    match.nmatched=0;
    match.score=0.0;
    double theta = 0.5*msms_error;
    double log_theta = log(theta);
    double theta_theta=2*theta*theta;
    double pie=log(sqrt(2*3.14159265358979323846));

    if(v->size() !=0) {
        for(vector<double>::const_iterator i=v->begin();i!=v->end();i++){
            pair<vector<ion>::iterator, vector<ion>::iterator> range=mz_range(*i, msms_error);
            double area=0.0;
            double mass=0.0;
            vector<ion>::iterator ion;
            for(ion=range.first;ion!=range.second;ion++){
                if(fabs(*i-ion->get_mz())<=msms_error){
                    if(area<ion->get_intensity() ){
                        area=ion->get_intensity();
                        mass=ion->get_mz();
                    }
                }
            }
            if(mass!=0.0 && area!=0.0){
                double delta=*i-mass;
                match.score+=log(area)-pie-log_theta-(delta*delta)/theta_theta;
                match.nmatched++;
            }
        }
    }

    return match;
}


void experimental_ion::add_top_score(match_score score, int n_to_keep){
    vector<match_score>::iterator i=find(this->top_scores.begin(), this->top_scores.end(), score);
    if(i == this->top_scores.end()){
        this->top_scores.push_back(score);
        if(((int)this->top_scores.size()) > n_to_keep){
            sort(this->top_scores.begin(), this->top_scores.end(), less_score);
            this->top_scores.erase(this->top_scores.begin());
        }
    }

}


void experimental_ion::add_score(double score){

    scores.push_back(score);

};

void experimental_ion::add_rscore(double rscore){
	this->rscores.push_back(rscore);
}

void  experimental_ion::truncate_peak_list(){

    if(this->fragments.size()>300){
        vector<ion> v1;
        vector<ion> v2;
        vector<ion> v3;
        this->sort_fragments_by_mz();
        double low_mass=this->fragments.begin()->get_mz();
        vector<ion>::iterator high_mass_locator=this->fragments.end();
        high_mass_locator--;
        double high_mass=high_mass_locator->get_mz();
        int mass_space=(int)(high_mass-low_mass)/3;
        double break1 = this->fragments.begin()->get_mz() + mass_space;
        double break2 = break1 + mass_space;
        for(vector<ion>::iterator i=this->fragments.begin();i!=this->fragments.end();i++) {
            if(i->get_mz()<break1){
                v1.push_back(*i);
            }else{
                if(i->get_mz()<break2){
                    v2.push_back(*i);
                }else{
                    v3.push_back(*i);
                }
            }
        }

        if(v1.size()>100){
            sort(v1.begin(), v1.end(), less_ion_area);
            v1.erase(v1.begin(), v1.end()-100);
        }
        if(v2.size()>100){
            sort(v2.begin(), v2.end(), less_ion_area);
            v2.erase(v2.begin(), v2.end()-100);
        }

        if(v3.size()>100){
            sort(v3.begin(), v3.end(), less_ion_area);
            v3.erase(v3.begin(), v3.end()-100);
        }

        this->fragments.clear();
        for(vector<ion>::iterator i=v1.begin();i!=v1.end();i++){
            this->fragments.push_back(*i);
        }
        for(vector<ion>::iterator i=v2.begin();i!=v2.end();i++){
            this->fragments.push_back(*i);
        }
        for(vector<ion>::iterator i=v3.begin();i!=v3.end();i++){
            this->fragments.push_back(*i);
        }

    }

}

void  experimental_ion::normalize_peak_list(){
    if(this->immonium_list.size()>0){
        double max_area=0.0;
        for(immonium_map::iterator i=this->immonium_list.begin();i!=this->immonium_list.end();i++){
            if(max_area<i->second.get_intensity()) {
                max_area=i->second.get_intensity();
            }
        }
        if(max_area !=0){
            for(immonium_map::iterator i=this->immonium_list.begin();i!=this->immonium_list.end();i++){
                i->second.set_intensity(i->second.get_intensity()/max_area*200);
            }
        }
    }
    if(this->fragments.size()>5){
        this->sort_fragments_by_mz();
        int space = (int) this->fragments.size() / 5;
        //vector<ion>::iterator  j = 0;
        //
        vector<ion>::iterator i = this->fragments.begin();
        vector<ion>::iterator j;
        while(i!=this->fragments.end()){
            for(int k=0;k<space;k++){
                j=i+1;
                if(j==this->fragments.end()){
                    sort(i, j, less_ion_area);
                    double max_ion_intensity=this->fragments.back().get_intensity();
                    for(vector<ion>::iterator k=i;k!=j;k++){
                        k->set_intensity(k->get_intensity()/max_ion_intensity);
                    }
                    return;
                }
            }
            vector<ion>::iterator max_locator=j;
            j++;
            sort(i, j, less_ion_area);
            double max_ion_intensity=max_locator->get_intensity();
            for(vector<ion>::iterator k=i;k!=j;k++){
                k->set_intensity(k->get_intensity()/max_ion_intensity);
            }
            i=j;
        }
    }
}


void experimental_ion::filter_peak_list_by_intensity(int intesity){
    vector<ion> tmp;
    vector<ion>::iterator i;
    for(i=this->fragments.begin();i != this->fragments.end();i++){
        if(i->get_intensity() > intesity){
            tmp.push_back(*i);
        }
    }
    this->fragments.clear();
    this->fragments.resize(tmp.size());
    copy(tmp.begin(), tmp.end(), this->fragments.begin());
}



void experimental_ion::write_search_result(ofstream& out, match_score* match, int rank){
    int nmissed=0;
    if(match->peptide.length() > 1) {
        string::iterator si;
        string::iterator si_end=match->peptide.end();
        si_end--;
        for(si=match->peptide.begin();si!=si_end;si++) {
            char ch;
            ch=*si;
            if(ch=='K' || ch=='R') {
                nmissed++;
            }
        }
    }


    out<<"<search_hit hit_rank=\""<<rank<<"\" peptide=\""<<match->peptide<<"\" peptide_prev_aa=\""<<match->prev_aa<<"\" peptide_next_aa=\""<<match->next_aa<<"\" protein=\""<<match->accession<<"\" num_tot_proteins=\"1\" num_matched_ions=\""<<match->nmatched<<"\" tot_num_ions=\""<<match->ntotal<<"\" calc_neutral_pep_mass=\""<<match->neutral_mass<<"\" massdiff=\""<<match->delta_mass<<"\" num_tol_term=\"2\" num_missed_cleavages=\""<<nmissed<<"\">"<<"\n";
    out<<"<modification_info";
    if(match->n_term_mass != 0.0){
        out<<" mod_nterm_mass=\""<<match->n_term_mass<<"\"";
    }
    if(match->c_term_mass != 0.0){
        out<<" mod_cterm_mass=\""<<match->c_term_mass<<"\"";
    }
    out<<">"<<endl;
    if(match->vinfo.size() >0) {
        vector<modification_info>::iterator i;
        for(i=match->vinfo.begin();i!=match->vinfo.end();i++) {
            out<<"<mod_aminoacid_mass position=\""<<i->position<<"\" mass=\""<<i->mass<<"\" />"<<"\n";
        }

    }
    out<<"</modification_info>"<<endl;
    out<<"<search_score name=\"bays_score\" value=\""<<match->score<<"\"/>"<<"\n";
    out<<"<search_score name=\"z_score\" value=\""<<match->zscore<<"\"/>"<<"\n";
    out<<"</search_hit>"<<"\n";

}

void experimental_ion::write_spectrum_query(ofstream& out, string base_name, int index, int max_out){
    out<<"<spectrum_query ";

    out<<" spectrum=\""<<this->ion_name<<"\"";
    out<<" start_scan=\""<<this->start_scan<<"\" end_scan=\""<<this->stop_scan<<"\" precursor_neutral_mass=\""<<this->get_mw()<<"\" assumed_charge=\""<<this->get_charge()<<"\" index=\""<<index<<"\">"<<"\n";

    out<<"<search_result>"<<endl;
    vector<match_score>::iterator i;
    int rank=1;
    int n_out=max_out;
    if(this->get_top_scores()->size() < max_out){
        n_out=this->get_top_scores()->size();
    }else if(max_out <= 0){
        n_out=1;
    }
    if(this->get_top_scores()->size() != 0){
        sort(this->get_top_scores()->begin(), this->get_top_scores()->end(), more_zscore);
        for(i=this->top_scores.begin();i!=this->top_scores.end() && rank <= n_out;i++){
            match_score ms=*i;
            this->write_search_result(out, &ms, rank);
            rank++;
        }
    }
    out<<"</search_result>"<<"\n";
    //
//    out<<"<analysis_result analysis=\"iTRAQ\">"<<endl;
//    out<<"<iTRAQ114 value=\""<<this->get_itraq114()<<"\"/>"<<endl;
//    out<<"<iTRAQ115 value=\""<<this->get_itraq115()<<"\"/>"<<endl;
//    out<<"<iTRAQ116 value=\""<<this->get_itraq116()<<"\"/>"<<endl;
//    out<<"<iTRAQ117 value=\""<<this->get_itraq117()<<"\"/>"<<endl;
//    out<<"</analysis_result>"<<endl;
    out<<"</spectrum_query>"<<"\n";
}


void experimental_ion::digitize(pair<double,double> range,double msms_error){
	//TODO check msms_error ne 0, and etc in experimental_ion::digitize
	cl_I index=0;
	cl_I mask=1;

	long long int pos;

	vector<ion>::iterator i;
	for(i=this->fragments.begin();i!=this->fragments.end();i++){
		pos=llround(i->mz/msms_error);
		index=(mask << pos);
		if(mz_index_intensity_map.find(index) != mz_index_intensity_map.end()){
			pair<double,double> mz_int=mz_index_intensity_map[index];
			if(mz_int.second < i->intensity){
				mz_index_intensity_map[index]=pair<double,double>(i->mz,i->intensity);
			}
		}else{
			this->mz_index=this->mz_index | index;
			mz_index_intensity_map[this->mz_index]=pair<double,double>(i->mz,i->intensity);
		}
	}
}


match_nmatch_pair experimental_ion::matched_score(cl_I index, map<cl_I, double>& mz_map, double msms_error){
	match_nmatch_pair match;
	match.nmatched=0;
	match.score=0.0;

	if (index != 0) {
		cl_I mask=1;
		double theta = 0.5*msms_error;
		double log_theta = log(theta);
		double theta_theta=2*theta*theta;
		double pie=log(sqrt(2*3.14159265358979323846));

		cl_I match_index= index | this->mz_index;

		uintC length=integer_length(match_index);

		for(cl_I i=0;i<length; ){
			if(logbitp (i, match_index)){
				cl_I map_index=(mask << i);
				pair<double,double> mz_int=mz_index_intensity_map[map_index];
				double delta=mz_int.first-mz_map[map_index];
				match.score+=log(mz_int.second)-pie-log_theta-(delta*delta)/theta_theta;
				match.nmatched++;
			}
			i=i+1;
		}
	}
    return match;
}

