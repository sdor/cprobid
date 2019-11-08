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

#include <dirent.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_combination.h>
#include "search_parameters.h"
#include "dictionary.h"
#include "experimental_ion.h"
#include "amino_acid_sequence.h"
#include "amino_acid_sequence_fragment.h"
#include "protein.h"
#include "ion.h"
#include "precursor_ion.h"
#include "experimental_ion.h"
#include "msms_run.h"
#include <MzXmlReader.h>
#include <boost/filesystem.hpp>

// XERCES_CPP_NAMESPACE_USE
using namespace std;
string version="cprobid 0.1.0";
double ms_error=0.25;
double msms_error=0.15;
int n_to_keep=10;
int n_to_out=1;
string search_database;
string base_name;
string summary_name;
int max_num_internal_cleavages=1;
unsigned int maximum_number_modification=3;
int max_num_derivatives=10000;
bool count_derivatives=false;
int min_precursor_charge=2;
int max_precursor_charge=5;
double minIonMw=10000;
double maxIonMw=0.0;

vector<experimental_ion> ions;
vector<string> data_files;
string fasta="";

void process_parameter_line(string s) {

	//istrstream in(s.c_str());
	istringstream in(s.c_str());
	string line;
	getline(in, line, '=');

	if (line == "ms_error") {
		string ms_error_str;
		getline(in, ms_error_str, '\n');
		ms_error=atof(ms_error_str.c_str());
	}

	if (line == "msms_error") {
		string msms_error_str;
		getline(in, msms_error_str, '\n');
		msms_error=atof(msms_error_str.c_str());
	}

	if (line == "modification") {
		string name;
		string delta_mass_str;
		string targets;
		getline(in, name, ',');
		getline(in, delta_mass_str, ',');
		double delta_mass=atof(delta_mass_str.c_str());
		getline(in, targets, '\n');
		Dictionary.AddAminoAcidModification(name.c_str(), delta_mass,
				targets.c_str());
	}
	if (line == "search_database") {
		getline(in, search_database);
	}
	if (line == "base_name") {
		getline(in, base_name);
		//istrstream summary_in(base_name.c_str());
		data_files.push_back(base_name);
		istringstream summary_in(base_name.c_str());
		//data_files.push_back(base_name);
		string summary_line;
		while (!summary_in.eof()) {
			getline(summary_in, summary_line, '/');
		}
		summary_name=summary_line;
	}
	if (line == "max_num_internal_cleavages") {
		string max_num_internal_cleavages_str;
		getline(in, max_num_internal_cleavages_str, '\n');
		max_num_internal_cleavages=atoi(max_num_internal_cleavages_str.c_str());
	}
	if (line == "n_to_keep") {
		string n_to_keep_str;
		getline(in, n_to_keep_str, '\n');
		n_to_keep=atoi(n_to_keep_str.c_str());
	}

	if (line == "n_to_out") {
		string n_to_out_str;
		getline(in, n_to_out_str, '\n');
		n_to_out=atoi(n_to_out_str.c_str());
	}
	if (line == "maximum_number_modification") {
		string maximum_number_modification_str;
		getline(in, maximum_number_modification_str, '\n');
		maximum_number_modification
				=atoi(maximum_number_modification_str.c_str());
	}

	if (line == "min_precursor_charge") {
		string min_precursor_charge_str;
		getline(in, min_precursor_charge_str, '\n');
		min_precursor_charge=atoi(min_precursor_charge_str.c_str());
	}

	if (line == "max_precursor_charge") {
		string max_precursor_charge_str;
		getline(in, max_precursor_charge_str, '\n');
		max_precursor_charge=atoi(max_precursor_charge_str.c_str());
	}

}
void read_parameters(char* file_name) {
	if(boost::filesystem::exists(file_name)) {
		string line;
		ifstream in;
		in.open(file_name, ios_base::in);
		do {
			getline(in, line, '\n');
			process_parameter_line(line);
		} while (!in.eof());
		in.close();		
	} else {
		cout<<"File "<<file_name<<" does not exist or access is not permited\n";
		exit(0);		
	}
	// if (access(file_name, R_OK) !=-1) {
	// 	string line;
	// 	ifstream in;
	// 	in.open(file_name, ios_base::in);
	// 	do {
	// 		getline(in, line, '\n');
	// 		process_parameter_line(line);
	// 	} while (!in.eof());
	// 	in.close();
	// } else {
	// 	cout<<"File "<<file_name<<" does not exist or access is not permited\n";
	// 	exit(0);
	// }
}

protein process_fasta_entry(string entry) {
	//protein *p=NULL;
	if (entry != "") {
		istringstream in(entry.c_str());
		string line;

		getline(in, line, '\n');
		istringstream title(line.c_str());
		string accession;
		getline(title, accession, ' ');
		string description="";
		string tmp;
		while (!title.eof()) {
			getline(title, tmp, ' ');
			if (tmp !="")
				description+=tmp+" ";
		}

		// read sequence
		string sequence="";
		while (!in.eof()) {
			getline(in, line, '\n');
			if (line !="")
				sequence+=line;
		}
		return protein(accession, description, sequence);
	}
	return protein();
}

//
vector<aas_fragment> digest(amino_acid_sequence* aas, string sites, int nmissed) {
	vector<aas_fragment> fragments;
	//	string::size_type npos = -1;
	vector<amino_acid>::iterator fragment_begin;
	vector<amino_acid>::iterator fragment_end;
	if (aas->get_sequence()->size()>2) {

		vector<amino_acid>::iterator i=aas->get_sequence()->begin();
		i++;
		vector<amino_acid>::iterator theEnd=aas->get_sequence()->end();
		theEnd--;
		fragment_begin=i;
		fragment_end=i;
		for (; i!=theEnd; i++) {
			if (sites.find(i->get_dictionary_amino_acid()->get_cod()) != string::npos) {
				fragment_end=i;
				char front_char;
				char end_char;
				vector<amino_acid>::iterator front=fragment_begin;
				front--;
				front_char=front->get_dictionary_amino_acid()->get_cod();
				if (front_char=='<') {
					front_char='-';
				}
				vector<amino_acid>::iterator end=fragment_end;
				end++;
				end_char=end->get_dictionary_amino_acid()->get_cod();
				if (end_char=='>') {
					end_char='-';
				}
				aas_fragment aasf("", front_char, fragment_begin, fragment_end,
						end_char);
				fragments.push_back(aasf);
				fragment_begin=fragment_end;
				fragment_begin++;
			}
		}

		vector<aas_fragment> tmp;
		vector<aas_fragment>::iterator j;
		vector<aas_fragment>::iterator k=fragments.begin();

		int l=0;
		for (j=fragments.begin(); j != fragments.end(); j++) {
			if (l==nmissed) {
				l=0;
				char front_char;
				char end_char;
				vector<amino_acid>::iterator front=k->begin();
				front--;
				front_char=front->get_dictionary_amino_acid()->get_cod();
				if (front_char=='<') {
					front_char='-';
				}

				vector<amino_acid>::iterator end=j->end();
				end++;
				end_char=end->get_dictionary_amino_acid()->get_cod();
				if (end_char=='>') {
					end_char='-';
				}

				aas_fragment aasf("", front_char, k->begin(), j->end(),
						end_char);
				tmp.push_back(aasf);

				k=j;
			}
			l++;
		}
		fragments.insert(fragments.end(), tmp.begin(), tmp.end());
	}
	return fragments;
}



void match(protein *proteinPtr, char front_cod, const amino_acid_sequence* s, vector< vector<double> >& vv,
		unsigned int immonium_cod, char back_cod, string ion_name, experimental_ion* a) {

	double miss_match_score=0.0;
	double matchScore=0.0;
	double immonium_score=0.0;
	double total_score=0.0;

	if (vv[0].size() !=0) {
		match_nmatch_pair match1=a->matched_ions_score(&vv[0], msms_error);
		matchScore=match1.score;
		if (match1.nmatched != 0) {
			if (vv[1].size() != 0 && a->charge > 1) {
				match_nmatch_pair match2=a->matched_ions_score(&vv[1],msms_error);
				if (match2.nmatched != 0) {
					matchScore+=match2.score;
				}
			}

			if (vv[2].size() != 0 && a->charge > 2) {
				match_nmatch_pair match2=a->matched_ions_score(&vv[2],
						msms_error);
				if (match2.nmatched != 0) {
					matchScore+=match2.score;
				}
			}

			matchScore+=match1.nmatched *log((double)match1.nmatched);

			int totalN;
			int missedN;
			totalN=vv[0].size();
			missedN=totalN-match1.nmatched;

			miss_match_score=missedN*(-log(a->max_fragment_mz()
					-a->min_fragment_mz()));

			immonium_score=a->immonium_score(immonium_cod);

			total_score=matchScore+miss_match_score+immonium_score;

			a->add_score(total_score);

			match_score mscore;
			mscore.accession=proteinPtr->get_accession();
			mscore.neutral_mass=a->get_mw();
			mscore.delta_mass=s->MonoMw()-a->get_mw();
			mscore.nmatched=match1.nmatched;
			mscore.ntotal=totalN;
			mscore.prev_aa=front_cod;
			mscore.peptide=s->SequenceString();
			mscore.vinfo=s->get_modification_info();
			mscore.next_aa=back_cod;
			mscore.score=total_score;
			mscore.n_term_mass=0.0;
			mscore.c_term_mass=0.0;
			if (s->getNTerminalModification() != NULL) {
				mscore.n_term_mass=s->getNTerminalModification()->DeltaMonoMass();
			}

			if (s->getCTerminalModification() != NULL) {
				mscore.c_term_mass=s->getCTerminalModification()->DeltaMonoMass();
			}

			a->add_top_score(mscore, n_to_keep);
		}
	}
}



int missed_cleavage_sites(string peptide) {
	int nmissed=0;
	if (peptide.length() > 1) {
		string::iterator si;
		string::iterator si_end=peptide.end();
		si_end--;
		for (si=peptide.begin(); si!=si_end; si++) {
			char ch;
			ch=*si;
			if (ch=='K' || ch=='R') {
				nmissed++;
			}
		}
	}
	return nmissed;
}


void load_fasta(string file_name) {
	fasta="";
	string line;

	ifstream in;
	in.open(file_name.c_str(), ios_base::in);
	while (!in.eof()) {
		getline(in, line);
		fasta+=line;
		fasta+="\n";
	}
	in.close();
}

/**
 *
 * @param msmsrun
 */
void run(msms_run* msmsrun) {
	cout<<"Processing :"<<msmsrun->getBaseName()<<".mzXML"<<endl;
	vector<amino_acid_modification*> modifications=	Dictionary.get_amino_acid_modification();

	istringstream protein_in(fasta.c_str());

	int i=0;
	string line;
	do {
		getline(protein_in, line, '>');
		if (line !="") {
			protein p=process_fasta_entry(line);
			if (p.length() > 0) {
				//cout<<"Processing "<<i<<" "+p.get_accession()<<endl;
				vector<aas_fragment> fragments=digest(&p, "KR",	max_num_internal_cleavages);

				for (vector<aas_fragment>::iterator j=fragments.begin(); j!= fragments.end(); j++) {
					aas_fragment fragment=*j;
					double mw=fragment.MonoMw();

					if (fragment.length()>2 && mw <= msmsrun->get_max_precursor_mw()+ms_error) {
						unsigned int immonuim_cod=fragment.immonium_cod();
						vector< vector<double> > fvvv=fragment.cidf();
						vector<experimental_ion>::iterator ion_iterator;
						pair<vector<experimental_ion>::iterator,vector<experimental_ion>::iterator>	range=msmsrun->precursor_mw_range(mw,ms_error);
						for (ion_iterator=range.first; ion_iterator	!=range.second; ion_iterator++) {
							match(&p,fragment.front_aa_cod(),&fragment,fvvv,immonuim_cod,fragment.back_aa_cod(),ion_iterator->get_name(),&(*ion_iterator));
						}
						if (!modifications.empty()) {
							vector<modification_info> sites=fragment.modification_sites(&modifications);
							size_t n=sites.size();
							if (!sites.empty()) {
								vector<unsigned int> positions;
								positions.resize(fragment.size());
								size_t k;
								if (n<maximum_number_modification) {
									k=n;
								}else{
									k=maximum_number_modification;
								}
								for (size_t j=0; j<=k; j++) {
									gsl_combination * c=gsl_combination_calloc(n, j);
									if (c != NULL) {
										do {
											positions.assign(positions.size(),0);
											unsigned int max_mod_per_site=0;
											vector<int> mindex;
											mindex.resize(j);
											for (size_t i=0; i<j; i++) {
												size_t cel=gsl_combination_get(c, i);
												modification_info site;
												site=sites[cel];
												positions[site.position]+=1;
												if (max_mod_per_site<positions[site.position]) {
													max_mod_per_site=positions[site.position];
												}
												mindex[i]=cel;
											}
											if (max_mod_per_site<2) {
												double delta_mw=0.0;
												vector<int>::iterator imindex;
												for (imindex=mindex.begin(); imindex
														!=mindex.end(); imindex++) {
													delta_mw
															+=(sites[*imindex]).aam->DeltaMonoMass();
												}
												double smw=mw+delta_mw;
												if (smw	<=msmsrun->get_max_precursor_mw()&& smw>=msmsrun->get_min_precursor_mw()) {
													aas_fragment s=fragment;
													for (imindex=mindex.begin(); imindex
															!=mindex.end(); imindex++) {
														s[(sites[*imindex]).position].modify((sites[*imindex]).aam);
													}
													vector< vector<double> > vvv=s.cidf();
													pair<vector<experimental_ion>::iterator,vector<experimental_ion>::iterator>	range=msmsrun->precursor_mw_range(smw,ms_error);
													for (ion_iterator=range.first; ion_iterator!=range.second; ion_iterator++) {
														match(&p,s.front_aa_cod(),&s,vvv,immonuim_cod,s.back_aa_cod(),ion_iterator->get_name(),&(*ion_iterator));
													}
												}
											}
										} while (gsl_combination_next(c)== GSL_SUCCESS );
									}
									gsl_combination_free(c);
								}
							}
						}

					}
				}
			}

			i++;
		}
	} while (!protein_in.eof());

	vector<experimental_ion>::iterator iion;
	for (iion = msmsrun->ions.begin(); iion != msmsrun->ions.end(); iion++) {
		if (!iion->scores.empty()) {
			gsl_vector *scores=gsl_vector_alloc(iion->scores.size());
			copy(iion->scores.begin(), iion->scores.end(), scores->data);
			double smean=gsl_stats_mean(scores->data, scores->stride, scores->size);
			double sstdev=gsl_stats_sd_m(scores->data, scores->stride,	scores->size, smean);
			gsl_vector_free(scores);
			if (sstdev != 0.0) {
				vector<match_score>::iterator its;
				for (its=iion->top_scores.begin(); its!=iion->top_scores.end(); its++) {
					double zval=(its->score-smean)/sstdev;
					if (zval > 25) {
						zval=0.0;
					}
					its->zscore=zval;
				}
			} else {
				vector<match_score>::iterator its;
				for (its=iion->top_scores.begin(); its!=iion->top_scores.end(); its++) {
					its->zscore=0.0;
				}
			}
		}
	}

	cout<<"Statistic is done\n";
}

// void convertToDta(const string& fileName) {
// 	// try {
// 		MzXML::MzXmlReader reader(fileName);
// 		reader.read([](const MzXML::MzXmlIon* ion) {

// 		});
// 		// XMLPlatformUtils::Initialize();
// 		// dta_sax_handler* handler;
// 		// handler = new dta_sax_handler();
// 		// handler->minPrecursorCharge()=min_precursor_charge;
// 		// handler->maxPrecursorCharge()=max_precursor_charge;
// 		// handler->setFileName(fileName.c_str());
// 		// cout << "Converting " << fileName << " to thermofinnigan dta\n";
// 		// SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
// 		// parser->setFeature(XMLUni::fgSAX2CoreValidation, false);
// 		// parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, false);
// 		// parser->setFeature(XMLUni::fgXercesSchema, false);
// 		// parser->setFeature(XMLUni::fgXercesSchemaFullChecking, false);
// 		// parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, false);
// 		// parser->setFeature(XMLUni::fgXercesContinueAfterFatalError, true);
// 		// parser->setContentHandler( handler );
// 		// parser->setErrorHandler( handler );
// 		// parser->parse( fileName.c_str() );
// 		// delete parser;
// 		// delete handler;
// 		// XMLPlatformUtils::Terminate();
// 	// } catch (const XMLException& toCatch) {
// 		// char* message = XMLString::transcode(toCatch.getMessage());
// 		// cout << "Error during initialization! :\n"
// 		// << "Exception message is: \n"
// 		// << message << "\n";
// 		// XMLString::release(&message);
// 		// exit(1);
// 	// }

// }
/**
 *
 * @param argc
 * @param argv[]
 * @return
 */
int main(int argc, char* argv[]) {
	cout<<version<<endl;
	if (argc > 0) {
		double execution_time=0.0;
		read_parameters(argv[1]);
		cout<<"Loading proteins from "<<search_database<<endl;
		load_fasta(search_database);
		search_parameters param;
		param.read_parametrs(argv[1]);
		vector<string>::iterator data_iterator;
		for (data_iterator = data_files.begin(); data_iterator != data_files.end(); data_iterator++) {
			time_t start_time;
			time_t end_time;
			time(&start_time);
			string mzXMLFile=(*data_iterator)+".mzXML";
			// convertToDta(mzXMLFile);
			msms_run r;
			cout<<"Loading msms-data:"<<data_iterator->c_str()<<endl;
			r.setBaseName(*data_iterator);
			r.load_dta_data();
			run(&r);
			r.save_result_xml(&param);
			time(&end_time);
			double elapsed_time=difftime (end_time, start_time);
			cout<<"Elapsed time: "<<elapsed_time<<" seconds."<<endl;
			execution_time+=elapsed_time;
		}
		cout<<"Total execution time: "<<execution_time<<" seconds."<<endl;
	} else {
		cout<<"Use cprobid <parameter_file>\n";
	}
	return 0;
}

