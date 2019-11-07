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

#include "msms_run.h"
#include <dirent.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "sax_xml_data_handler.h"

msms_run::msms_run() {
	this->min_charge=10;
	this->max_charge=0;
}

msms_run::~msms_run() {
}


void msms_run::load_dta_file(const char* fileName) {
    string ion_name="";
    int start_scan;
    int stop_scan;
    double mw;
    int charge;

    string titleStr;
    istringstream ion_title(fileName);

    getline(ion_title, titleStr, '.');

    ion_name+=titleStr+".";
    getline(ion_title, titleStr, '.');
    ion_name+=titleStr+".";
    start_scan=atoi(titleStr.c_str());
    getline(ion_title, titleStr, '.');
    ion_name+=titleStr+".";
    stop_scan=atoi(titleStr.c_str());
    getline(ion_title, titleStr, '.');
    ion_name+=titleStr;
    charge=atoi(titleStr.c_str());

    ifstream in;
    string dta_file_path=this->base_name+"/"+fileName;
    in.open(dta_file_path.c_str(), ios_base::in);


    if(!in.eof()) {
        string ion_headerStr;
        getline(in, ion_headerStr, '\n');
        istringstream ion_header(ion_headerStr.c_str());
        string mwStr;
        string chargeStr;
        getline(ion_header, mwStr, '\t');
        mw=atof(mwStr.c_str());
        mw-=Hydrogen.MonoMass();
        if(mw < minIonMw){minIonMw=mw;}
        if(mw > maxIonMw){maxIonMw=mw;}
        getline(ion_header, chargeStr, '\t');
        charge=atoi(chargeStr.c_str());
        if(this->min_charge > charge){
        	this->min_charge= charge;
        }
        if(this->max_charge < charge){
        	this->max_charge = charge;
        }
        string ion_fragmentStr;
        double mz=mw/charge+Hydrogen.MonoMass();

        experimental_ion exp_ion(ion_name, start_scan, stop_scan, mz, charge, 0.0);

        while(!in.eof()) {
            getline(in, ion_fragmentStr, '\n');
            if (ion_fragmentStr !="") {
                istringstream ion_fragment(ion_fragmentStr.c_str());
                string fragmentMzStr;
                double fragment_mz;
                getline(ion_fragment, fragmentMzStr, '\t');
                fragment_mz=atof(fragmentMzStr.c_str());
                string fragmentAreaStr;
                double fragment_area;
                getline(ion_fragment, fragmentAreaStr, '\t');
                fragment_area=atof(fragmentAreaStr.c_str());
                int chrg=1;
                ion fragment(fragment_mz, chrg, fragment_area);
                exp_ion.add_fragment(&fragment);
            }
        }
        //exp_ion.print_fragments();
        ions.push_back(exp_ion);
        //ions.back().print_fragments();
    }
    in.close();
}


void msms_run::load_dta_data(){
    minIonMw=0.0;
    maxIonMw=0.0;
    //this->base_name=directoryPath;
    //cout<<directoryPath<<endl;
    //vector<experimental_ion>* ions=new vector<experimental_ion>();
    DIR *dp;
    struct dirent *ep;
    dp=opendir(this->base_name.c_str());
    if(dp!=NULL) {
        while((ep=readdir(dp))) {
            //cout<<ep->d_name<<"\n";
            if(strstr(ep->d_name, ".dta")!=NULL) {
                //cout<<"Loading "<<ep->d_name<<"\n";
                string dta_file_path=this->base_name+"/"+ep->d_name;
                load_dta_file(ep->d_name);
            }
        }
        closedir(dp);
    }
    else {
        cout<<"Can't find directory: "<<this->base_name<<"\n";
        exit(0);
    }
    this->pre_process_data();
}


XERCES_CPP_NAMESPACE_USE
void msms_run::load_xml_data(const char* filename){
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        // Do your failure processing here
        exit(0);
    }

    //char* xmlFile = filename.c_str();
    SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
    parser->setFeature(XMLUni::fgSAX2CoreValidation, true);   // optional
    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional

    sax_xml_data_handler* handler = new sax_xml_data_handler(filename);
    parser->setContentHandler(handler);
    parser->setErrorHandler(handler);

    try {
        parser->parse(filename);
        this->ions.clear();
        this->ions.resize(handler->get_ions()->size());
        copy(handler->get_ions()->begin(), handler->get_ions()->end(), this->ions.begin());
        this->data_file=filename;
        this->pre_process_data();
    }  catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"<< message << "\n";
        XMLString::release(&message);
        exit(-1);
    } catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"<< message << "\n";
        XMLString::release(&message);
        exit(-1);
    }

    delete parser;
    delete handler;
    XMLPlatformUtils::Terminate();
}


void msms_run::save_result_xml(search_parameters* param){
    //string base_name=file_name;
    //string base_name_xml=base_name+".out."+".xml";
    string file_name=this->base_name+".xml";
    ofstream out;
    //out.open(base_name_xml.c_str(),ios_base::out);
    out.open(file_name.c_str(), ios_base::out);
    out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<"\n";
    out<<"<?xml-stylesheet type=\"text/xsl\" href=\"/data3/search/akeller/pepXML_protXML/trans_proteomic_pipeline/pepXML_std.xsl\"?>"<<"\n";
    out<<"<msms_pipeline_analysis date=\"2006-03-29T10:43:05\" xmlns=\"http://regis-web.systemsbiology.net/pepXML\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://regis-web.systemsbiology.net/pepXML /data3/search/akeller/pepXML_protXML/trans_proteomic_pipeline/pepXML_v18.xsd\"  summary_xml=\""<<this->base_name<<".xml\">"<<"\n";
    out<<"<msms_run_summary base_name=\""<<this->base_name<<"\" raw_data_type=\"raw\" raw_data=\".mzXML\">"<<"\n";
    out<<"<sample_enzyme name=\"Trypsin\">"<<"\n";
    out<<"<specificity sense=\"C\" cut=\"KR\" no_cut=\"P\"/>"<<"\n";
    out<<"</sample_enzyme>"<<"\n";
    out<<"<search_summary base_name=\""<<this->base_name+".xml"<<"\" search_engine=\"PROBID\" precursor_mass_type=\"monoisotopic\" fragment_mass_type=\"monoisotopic\" out_data_type=\".out\" out_data=\".tgz\" search_id=\"1\">"<<"\n";
    out<<"<search_database local_path=\""<<param->get_search_database()<<"\" type=\"AA\"/>"<<"\n";
    out<<"<enzymatic_search_constraint enzyme=\"Trypsin\" max_num_internal_cleavages=\""<<param->get_max_num_internal_cleavages()<<"\" min_number_termini=\"2\"/>"<<"\n";

    map<string, amino_acid_modification>* mPtr=param->get_amino_acid_modifications();
    map<string, amino_acid_modification>::iterator i;
    for(i=mPtr->begin();i!=mPtr->end();i++){
        amino_acid_modification m=(*i).second;
        string t=m.modification_targets();

        string::iterator j;
        for(j=t.begin();j!=t.end();j++) {
            if(*j == '<'){
                // <terminal_modification terminus="n" massdiff="144.1" mass="145.1078" variable="N" protein_terminus="N"/>
                out<<"<terminal_modification terminus=\"n\" massdiff=\""<<m.DeltaMonoMass()<<"\" mass=\""<<m.DeltaMonoMass()<<"\" variable=\"Y\" protein_terminus=\"N\"/>"<<"\n";
            } else {
                // <aminoacid_modification aminoacid="Q" massdiff="0.984" mass="129.11472" variable="Y" binary="N" symbol="@"/>
                out<<"<aminoacid_modification aminoacid=\""<<*j<<"\" massdiff=\""<<m.DeltaMonoMass()<<"\" mass=\""<<m.DeltaMonoMass()+Dictionary.GetAminoAcid(*j)->ResidueMonoMw()<<"\" variable=\"Y\" binary=\"N\" symbol=\""<<m.Cod()<<"\"/>"<<"\n";
            }
        }
    }

    out<<"<parameter name=\"precursor_mass_tolerance\" value=\""<<param->get_ms_error()<<"\"/>"<<"\n";
    out<<"<parameter name=\"fragment_mass_tolerance\" value=\""<<param->get_msms_error()<<"\"/>"<<"\n";
    out<<"<parameter name=\"ion_series\" value=\"0 1 0 0 0 0 0 1 0\"/>"<<"\n";
    out<<"<parameter name=\"num_output_lines\" value=\""<<param->get_n_to_keep()<<"\"/>"<<"\n";
    out<<"</search_summary>"<<"\n";

    int index=1;
    if(ions.size() != 0) {
        for(vector<experimental_ion>::iterator ion=this->ions.begin();ion!=this->ions.end();ion++) {
            if(ion->get_top_scores()->size() != 0) {
                ion->write_spectrum_query(out, this->base_name, index, param->get_n_to_out());
                index++;
            }
        }
    }
    out<<"</msms_run_summary>"<<"\n";
    out<<"</msms_pipeline_analysis>"<<"\n";
}


void msms_run::pre_process_data(){
    this->maxIonMw=0.0;
    this->minIonMw=100000.0;
    sort(this->ions.begin(), this->ions.end(), less_ion_mw);
    minIonMw=this->ions.front().get_mw();
    maxIonMw=this->ions.back().get_mw();
    this->fragments_range=get_precursor_fragments_range();
    vector<experimental_ion>::iterator i;
    for(i=this->get_ions()->begin();i!=this->get_ions()->end();i++){
        //i->print_fragments();
        i->sort_fragments_by_mz();
        i->set_itraq114(i->get_sum_intensity(114.1, 0.1));
        i->set_itraq115(i->get_sum_intensity(115.1, 0.1));
        i->set_itraq116(i->get_sum_intensity(116.1, 0.1));
        i->set_itraq117(i->get_sum_intensity(117.1, 0.1));
        i->truncate_peak_list();
        i->normalize_peak_list();
    }
    sort(ions.begin(), ions.end(), less_ion_mw);
    // print_ions();
}

void msms_run::print_ions(){
    vector<experimental_ion>::iterator i;
    for(i=ions.begin();i!=ions.end();i++){
        cout<<"Mz "<<i->get_mz()<<" Charge "<<i->get_charge()<<" Mw "<<i->get_mw()<<endl;
    }
}
pair<vector<experimental_ion>::iterator, vector<experimental_ion>::iterator> msms_run::precursor_mw_range(double mz, double delta_mass){
    //print_ions();
    pair<vector<experimental_ion>::iterator, vector<experimental_ion>::iterator> range;
    double lowmz=mz-delta_mass+Hydrogen.MonoMass();
    double highmz=mz+delta_mass+Hydrogen.MonoMass();
    experimental_ion lowion("", 0, 0, lowmz, 1, 0.0);
    experimental_ion highion("", 0, 0, highmz, 1, 0.0);
    //cout<<lowion.get_mw()<<endl;
    //cout<<highion.get_mw()<<endl;
    range.first=lower_bound(this->ions.begin(), this->ions.end(), lowion, less_ion_mw);
    range.second=upper_bound(this->ions.begin(), this->ions.end(), highion, less_ion_mw);
    //cout<<range.first->get_mw()<<endl;
    //cout<<range.second->get_mw()<<endl;
    return range;
}

vector<double> msms_run::get_precursors_mw() const{
	vector<double> v;
	vector<experimental_ion>::const_iterator i;
	for(i=this->ions.begin(); i != this->ions.end(); i++){
		v.push_back(i->get_mw());
	}
	return v;
}


pair<double, double> msms_run::get_precursor_fragments_range(){
	pair<double,double> f_range;
	if(!ions.empty()){
		double min_fragment_mz;
		double max_fragment_mz;
		f_range.first=10000.0;
		f_range.second=0.0;
		vector<experimental_ion>::iterator i;
		for(i=this->ions.begin(); i!=this->ions.end();i++){
			min_fragment_mz=i->min_fragment_mz();
			max_fragment_mz=i->max_fragment_mz();
			if(f_range.first >min_fragment_mz){
				f_range.first=min_fragment_mz;
			}
			if(f_range.second < max_fragment_mz){
				f_range.second = max_fragment_mz;
			}
		}
	}else{
		f_range.first=0.0;
		f_range.second=0.0;
	}
	return f_range;
}

