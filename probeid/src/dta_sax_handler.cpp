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

#include <iostream>
#include <sstream>
#include <xercesc/util/Base64.hpp>
#include "ion.h"
#include "dta_sax_handler.h"



dta_sax_handler::dta_sax_handler() :
	m_createDir(true) {
	dtaReset();
	sumScans=true;
}

dta_sax_handler::~dta_sax_handler() {
}

void dta_sax_handler::startElement(const XMLCh* const uri,
		const XMLCh* const localname, const XMLCh* const qname,
		const Attributes& attrs) {
	char* message = XMLString::transcode(qname);


	if (!strcmp(message, "scan")) {

		char* msLevel_str = XMLString::transcode(attrs.getValue(XMLString::transcode("msLevel")));
		m_cidLevel = atoi(msLevel_str);
		char* scanNum_str=XMLString::transcode(attrs.getValue(XMLString::transcode("num")));
		m_scanNum = atoi(scanNum_str);
		char* peaksCount_str=XMLString::transcode(attrs.getValue(XMLString::transcode("peaksCount")));
		m_peaksCount = atoi(peaksCount_str);
		if ( m_cidLevel > 1) {
			m_isCid = true;
		}else{
			savePrecursors();
		}
		XMLString::release( &msLevel_str);
		XMLString::release( &scanNum_str);
		XMLString::release( &peaksCount_str);
	} else if (!strcmp(message, "peaks") && m_isCid == true) {
		precision=32;
		char
				* precision_str=
						XMLString::transcode(attrs.getValue(XMLString::transcode("precision")));
		if (precision_str != NULL) {
			precision=atoi(precision_str);
		}
		m_isPeaks = true;
		XMLString::release( &precision_str);
	} else if (!strcmp(message, "precursorMz")) {
		m_isPrecursorMz = true;
		char
				* precursorCharge_str=
						XMLString::transcode(attrs.getValue(XMLString::transcode("precursorCharge")));
		if (precursorCharge_str != NULL) {
			m_precursorCharge = atoi(precursorCharge_str);
		} else {
			m_precursorCharge= 1;
		}
		XMLString::release( &precursorCharge_str);

	} else if (!strcmp(message, "software")) {
		char
				* software_type=
						XMLString::transcode(attrs.getValue(XMLString::transcode("type")));
		if (!strcmp(software_type, "conversion")) {
			char
					* software_name=
							XMLString::transcode(attrs.getValue(XMLString::transcode("name")));
			if (!strcmp(software_name, "mzStar")) {
				conversion_software=this->generic_mzXML;
			} else if (!strcmp(software_name, "importWiff")) {
				conversion_software=this->importWiff;
			} else if (!strcmp(software_name, "MassWolf")) {
				conversion_software=this->generic_mzXML;
			} else if (!strcmp(software_name, "Thermo2mzXML")) {
				conversion_software=this->generic_mzXML;
			} else {
				conversion_software=this->generic_mzXML;
			}
			XMLString::release(&software_name);
		}
		XMLString::release(&software_type);
	}

	XMLString::release(&message);
}


//////////////////////////

/////////////////////////
void dta_sax_handler::savePrecursor(experimental_ion precursor){
	int n;
	for (n = this->minPrecursorCharge(); n<= this->maxPrecursorCharge(); n++) {
		std::string foutName;
		std::string::size_type len;
		std::string::size_type pos;

		foutName = m_fileName;
		pos = foutName.rfind("/") + 1; // If file name was given with
		// path let's get rid of it
		len = foutName.size() - pos - 6; // We don't wan't the ending ".xml"

		foutName = foutName.substr(pos, len);

		ostringstream sname;
		sname<<m_dirName<<"/"<<foutName<<"."<<precursor.start_scan<<"."<<precursor.stop_scan<<"."<<n<<".dta";

		m_fout.open(sname.str().c_str());
		if ( !m_fout.good() ) {
			cerr << "Could not open output file\n";
			exit(2);
		}

		m_precursorMH = (precursor.mz * n) - (n - 1)*Hydrogen.MonoMass();
		m_fout.setf(ios::fixed, ios::floatfield);
		m_fout.precision(4);
		m_fout << m_precursorMH << "\t";
		m_fout.precision(0);
		m_fout << n << endl;
		m_fout.precision(4);
		precursor.sort_fragments_by_mz();
		vector<ion>::iterator iion;
		for(iion=precursor.fragments.begin();iion!=precursor.fragments.end();iion++){
			m_fout<<iion->mz<<"\t"<<iion->intensity<<endl;
		}

		m_fout.close();
	}
}

void dta_sax_handler::savePrecursors(){
	if(!precursors.empty()){
		if (m_createDir) {
			m_dirName = generateFoutName(0);
			std::string command = "mkdir ./" + m_dirName;
			system(command.c_str() );
			m_createDir = false;
		}
		if(sumScans){
			experimental_ion precursor;
			vector<experimental_ion>::iterator i;
			precursor.start_scan=precursors.begin()->start_scan;
			precursor.mz=precursors.begin()->mz;
			for(i=precursors.begin();i!=precursors.end();i++){
				vector<ion>::iterator j;
				for(j=i->fragments.begin();j!=i->fragments.end();j++){
					precursor.fragments.push_back(*j);
				}
				precursor.stop_scan=i->stop_scan;
			}
			savePrecursor(precursor);
		}else{
			vector<experimental_ion>::iterator i;
			for(i=precursors.begin();i!=precursors.end();i++){
				savePrecursor(*i);
			}
		}
		precursors.clear();
	}
}
void dta_sax_handler::endElement(const XMLCh *const uri,	const XMLCh *const localname, const XMLCh *const qname) {

	char* message = XMLString::transcode(qname);

	if (!strcmp(message, "scan") && m_peaksCount != 0) {
		if (conversion_software == this->generic_mzXML) {
			if (m_isCid == true) {
				experimental_ion *precursor=new experimental_ion();
				precursor->start_scan=m_scanNum;
				precursor->stop_scan=m_scanNum;
				for (int pkts = 0; pkts < 2 * m_peaksCount;) {
					ion fragment;
					fragment.mz=(float)(m_pData)[pkts];
					fragment.intensity=(float)(m_pData)[pkts + 1];
					precursor->add_fragment(&fragment);
					pkts +=2;
				}
				precursor->mz=m_precursorMz;
				precursors.push_back(*precursor);
				delete precursor;
				delete[] m_pData;
			}
		} else if (this->conversion_software==this->importWiff) {
			if (m_isCid == true) {
				if (m_createDir) {
					m_dirName = generateFoutName(0);
					std::string command = "mkdir ./" + m_dirName;
					system(command.c_str() );
					m_createDir = false;
				}
				if (m_precursorCharge >= this->minPrecursorCharge()
						&& m_precursorCharge <= this->maxPrecursorCharge() ) {

					std::string fileName = generateFoutName(m_precursorCharge);
					fileName = m_dirName + "/" + fileName;
					m_fout.open(fileName.c_str() );
					if ( !m_fout.good() ) {
						cerr << "Could not open output file\n";
						exit(2);
					}
					m_precursorMH = (m_precursorMz * m_precursorCharge)
							- (m_precursorCharge - 1)*1.007825;
					m_fout.setf(ios::fixed, ios::floatfield);
					m_fout.precision(4);
					m_fout << m_precursorMH << "\t";
					m_fout.precision(0);
					m_fout << m_precursorCharge << endl;

					dta_sax_handler::printMassInt();

					m_fout.close();

				}
				delete[] this->m_pData_64;
			}

		}

		dtaReset(); // Clean up for the next scan
	}

	XMLString::release( &message);
}

void dta_sax_handler::fatalError(const SAXParseException& exception) {
	char* message = XMLString::transcode(exception.getMessage());
	cout << "Fatal Error: " << message << " at line: "
			<< exception.getLineNumber() << endl;
}

void dta_sax_handler::characters(const XMLCh* const chars,
		const unsigned int length) {
	if (m_isPeaks && m_isCid && m_peaksCount != 0) {
		if (conversion_software == this->generic_mzXML) {
			char* pData = XMLString::transcode(chars);
			char* pDecoded;
			try {
				pDecoded = (char *) new char[ m_peaksCount * 8 ];
				m_pData = (float *) new float[ m_peaksCount * 8 ];
			}
			catch( std::bad_alloc ) {
				cerr << "Cannot allocate memory for decoding of peaks\n";
				exit(1);
			}
			// Base64 decoding
			b64_decode_mio( (char*) pDecoded , pData);

			// And byte order correction
			int n;
			for (n = 0; n < (2 * m_peaksCount); n++) {
				((u_int32_t *)m_pData)[n] = ntohl( (u_int32_t) ((u_int32_t *)pDecoded)[n]);
			}

			// Free allocated memory
			delete[] pDecoded;
			XMLString::release( &pData);
		} else if (this->conversion_software == this->importWiff) {
			unsigned int decodedLength;
			XMLByte* bytes=Base64::decodeToXMLByte(chars, &decodedLength);
			double* data=(double* )bytes;
			this->m_pData_64=new double[2*m_peaksCount];
			for (int i=0; i< 2*m_peaksCount; i++) {
				this->m_pData_64[i]=data[i];
			}
			XMLString::release(&bytes);
		}

		m_isPeaks = false;
	} else if (m_isPrecursorMz) {
		char* pMass = XMLString::transcode(chars);

		m_precursorMz = (float) atof(pMass);
		XMLString::release( &pMass);

		m_isPrecursorMz = false;
	}

}

int dta_sax_handler::guessCharge() {
	// All this small routine does is trying to gues the charge state of the precursor
	// from the ratio of the integrals of the intensities below and above m_precursorMz

	float intBelow = 0;
	float intAbove = 0;
	int n;
	if (conversion_software == this->generic_mzXML) {
		for (n = 0; n < 2 * m_peaksCount; n++) {
			if (m_pData[n] <= m_precursorMz) {
				n++;
				intBelow += m_pData[n];
			} else {
				n++;
				intAbove += m_pData[n];
			}
		}
	} else if (this->conversion_software == this->importWiff) {
		for (n = 0; n < 2 * m_peaksCount; n++) {
			if (this->m_pData_64[n] <= m_precursorMz) {
				n++;
				intBelow += this->m_pData_64[n];
			} else {
				n++;
				intAbove += this->m_pData_64[n];
			}
		}
	}

	// There is no particular reason for the 0.1 I just choose it
	// randomly. It's there just to compensate for the noise....
	// But you can change it to wathever is best for you
	if (intAbove > 0.1 * intBelow) {
		return 2;
	} else {
		return 1;
	}
}

void dta_sax_handler::printMassInt() {
	if (conversion_software == this->generic_mzXML) {
		for (int pkts = 0; pkts < 2 * m_peaksCount;) {
			/*
			 * printf("%.4f\t", (float) (m_pData)[pkts]);	// Mass and ...
			 * printf("%.0f\n", (float) (m_pData)[pkts + 1]);// intensity.
			 * pkts += 2;
			 */
			m_fout.setf(ios::fixed, ios::floatfield);
			m_fout.precision(4);
			m_fout << (float) (m_pData)[pkts] << "\t";
			m_fout.precision(0);
			m_fout << (float) (m_pData)[pkts + 1] << endl;
			pkts +=2;
		}
	} else if (this->conversion_software == this->importWiff) {
		for (int i=0; i< 2 * m_peaksCount;) {
			m_fout.setf(ios::fixed, ios::floatfield);
			m_fout.precision(4);
			m_fout<<this->m_pData_64[i]<<"\t";
			m_fout.precision(0);
			m_fout <<this->m_pData_64[i + 1] << endl;
			i +=2;
		}
	}
}

std::string dta_sax_handler::generateFoutName(int charge) {
	std::string foutName;
	std::string::size_type len;
	std::string::size_type pos;

	foutName = m_fileName;
	pos = foutName.rfind("/") + 1; // If file name was given with
	// path let's get rid of it
	len = foutName.size() - pos - 6; // We don't wan't the ending ".xml"

	foutName = foutName.substr(pos, len);

	if (charge == 0) // We use this special cas to get just the fileName
	{ // without nrs. So that we can use as our dirName
		return foutName;
	}

	std::stringstream sout;

	std::string chargeStr; // Convert charge from int to string
	sout << charge;
	chargeStr = sout.str();
	sout.clear(); // Clear errors
	sout.str(""); // Clean stream and we are ready to use it again

	std::string startScan;
	std::string endScan;
	sout.fill('0');
	sout.width(4);
	sout << m_scanNum;
	sout >> startScan;
	endScan = startScan; // For the moment we don't integrate multiple spectra

	foutName = foutName + "." + startScan + "." + endScan + "." + chargeStr
			+ ".dta";

	/*
	 * if( m_cidLevel == 2 )
	 * {
	 * foutName = foutName + ".2." + startScan + "." + endScan + "." + chargeStr + ".dta";
	 * }
	 * else if( m_cidLevel == 3 )
	 * {
	 * foutName = foutName + ".3." + startScan + "." + endScan + "." + chargeStr + ".dta";
	 * }
	 */

	return foutName;
}

// This is used when parsing a list of files
void dta_sax_handler::prepareForNextFile() {
	m_createDir = true;
	dtaReset();
}
