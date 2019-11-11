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

#if !defined(DTASAX2HANDLER_HPP)
#define DTASAX2HANDLER_HPP

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <fstream>	// file output
#include <iostream>
#include <iomanip>	// output formatting
#include <sstream>
#include <string>	// strcpm
#include <netinet/in.h>
#include <stdlib.h>	// atoi
#include "base64.h"
#include "experimental_ion.h"

XERCES_CPP_NAMESPACE_USE
using namespace std;

class dta_sax_handler : public DefaultHandler {
	enum conversion_software_type {
		mzStar,
		importWiff,
		massWolf,
		thermo2mzXML,
		generic_mzXML
	};
private:

	conversion_software_type conversion_software;
	string m_fileName;

	bool m_isCid;
	bool m_isPrecursorMz;
	bool m_isPeaks;

	int m_scanNum;
	int m_peaksCount;
	int m_precursorCharge;
	int m_cidLevel;

	float* m_pData;
	float m_precursorMz;
	float m_precursorMH;

	std::ofstream m_fout;

	bool m_createDir;
	std::string m_dirName; // Name of the output directory = (XML fileName) - .xml + _dta
	int precision;
	double* m_pData_64;

	int min_precursor_charge;
	int max_precursor_charge;

	//experimental_ion *precursor;
	vector<experimental_ion> precursors;
	bool sumScans;

public:

	int minPrecursorCharge() const {
		return min_precursor_charge;
	}

	int& minPrecursorCharge() {
		return min_precursor_charge;
	}


	int maxPrecursorCharge() const {
		return max_precursor_charge;
	}

	int& maxPrecursorCharge() {
		return max_precursor_charge;
	}

	dta_sax_handler();
	~dta_sax_handler();

	void startElement(const XMLCh* const uri, const XMLCh* const localname,
			const XMLCh* const qname, const Attributes& attrs);

	void endElement(const XMLCh *const uri, const XMLCh *const localname,
			const XMLCh *const qname);

	void characters(const XMLCh* const chars, const unsigned int length);

	void fatalError(const SAXParseException&);

	void prepareForNextFile();

	inline void setFileName(const char* fileName) {
		m_fileName = fileName;
	}

private:
	inline void dtaReset() {
		m_isCid = false;
		m_isPrecursorMz = false;
		m_isPeaks = false;

		m_peaksCount = 0;
		m_precursorCharge = -1;
		m_precursorMz = 0;
		m_precursorMH = 0;
	}

	int guessCharge();
	void printMassInt();
	string generateFoutName(int charge);
	void savePrecursors();
	void savePrecursor(experimental_ion ion);
};

#endif
