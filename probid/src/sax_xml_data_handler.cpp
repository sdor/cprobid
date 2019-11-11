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

#include <cstdlib>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/Base64.hpp>
#include "sax_xml_data_handler.h"
#include "base64.h"
#include "ion.h"


sax_xml_data_handler::sax_xml_data_handler(string file_name) {

}

sax_xml_data_handler::~sax_xml_data_handler() {

}

void sax_xml_data_handler::startElement(
const   XMLCh* const    uri,
        const   XMLCh* const    localname,
        const   XMLCh* const    qname,
        const   Attributes&     attrs
) {
    char* message = XMLString::transcode(localname);
    if(!strcmp(message, "mzXML")){
    	this->parser_state=this->MZ_XML;
    } else if(!strcmp(message, "scan")){
        this->parser_state=this->SCAN;
        char* numValue = XMLString::transcode(attrs.getValue(XMLString::transcode("num")));
        char* msLevelValue=XMLString::transcode(attrs.getValue(XMLString::transcode("msLevel")));
        char* peaksCountValue=XMLString::transcode(attrs.getValue(XMLString::transcode("peaksCount")));
        this->precursor_ion=new experimental_ion();
        this->precursor_ion->msLevel=atoi(msLevelValue);
        this->precursor_ion->peaksCount=atoi(peaksCountValue);
        if(this->precursor_ion->msLevel > 1){
        	if(numValue != NULL){
        		precursor_ion->num=atoi(numValue);
        	}else{
        		precursor_ion->num=0;
        	}
        }
        XMLString::release(&numValue);
        XMLString::release(&msLevelValue);
        XMLString::release(&peaksCountValue);
    } else if (!strcmp(message, "peaks")){
        this->parser_state=this->PEAKS;
    } else if(!strcmp(message, "precursorMz")){
        this->parser_state=this->PRECURSOR_MZ;
        char* precursorChargeValue = XMLString::transcode(attrs.getValue(XMLString::transcode("precursorCharge")));
        char* precursorIntensity=XMLString::transcode(attrs.getValue(XMLString::transcode("precursorIntensity")));
        if(precursorChargeValue != NULL){
            this->precursor_ion->charge=atoi(precursorChargeValue);
        }else{
        	this->precursor_ion->charge=0;
        }
        if(precursorIntensity != NULL){
        	this->precursor_ion->intensity=atof(precursorIntensity);
        }
        XMLString::release(&precursorChargeValue);
        XMLString::release(&precursorIntensity);
    }if(!strcmp(message, "software")) {
		char *software_type=XMLString::transcode(attrs.getValue(XMLString::transcode("type")));
		if (!strcmp(software_type, "conversion")) {
			char *software_name=XMLString::transcode(attrs.getValue(XMLString::transcode("name")));
			if (!strcmp(software_name, "mzStar")) {
				this->run.conversion_software=msms_run::generic_mzXML;
			} else if (!strcmp(software_name, "importWiff")) {
				this->run.conversion_software=msms_run::importWiff;
			} else if (!strcmp(software_name, "MassWolf")) {
				this->run.conversion_software=msms_run::generic_mzXML;
			} else if (!strcmp(software_name, "Thermo2mzXML")) {
				this->run.conversion_software=msms_run::generic_mzXML;
			} else {
				this->run.conversion_software=msms_run::generic_mzXML;
			}
			XMLString::release(&software_name);
		}
		XMLString::release(&software_type);
    }
    XMLString::release(&message);
}

void sax_xml_data_handler::endElement(const XMLCh *const uri,
        const XMLCh *const localname,
        const XMLCh *const qname) {
    char* message = XMLString::transcode(localname);
    if(!strcmp(message, "precursorMz")){
        this->parser_state=this->SCAN;
    }else if(!strcmp(message, "scan")){
    	this->run.ions.push_back(*this->precursor_ion);
    	delete this->precursor_ion;
    	this->parser_state=this->MZ_XML;
    }
    XMLString::release(&message);
}

void sax_xml_data_handler::characters(const XMLCh *const chars, const unsigned int length){
	if(this->parser_state==this->PRECURSOR_MZ){
		char* mz = XMLString::transcode(chars);
		if(mz != NULL){
			this->precursor_ion->mz=atof(mz);
		}
		XMLString::release(&mz);
	} else if(this->parser_state==this->PEAKS) {
		if (this->run.conversion_software == msms_run::generic_mzXML) {
			char* data = XMLString::transcode(chars);
			char* decoded_data;
			float *real_data;
			decoded_data = (char *) new char[ this->precursor_ion->peaksCount * 8 ];
			real_data = (float *) new float[ this->precursor_ion->peaksCount * 8 ];
			// Base64 decoding
			b64_decode_mio( (char*) decoded_data , data);

			// byte order correction
			int n;
			for (n = 0; n < (2 * this->precursor_ion->peaksCount); n++) {
				((u_int32_t *)real_data)[n] = ntohl( (u_int32_t) ((u_int32_t *)decoded_data)[n]);
			}

			for(int i=0; i< 2*this->precursor_ion->peaksCount; i++){
				ion fragment;
				fragment.mz=real_data[i];
				i++;
				fragment.intensity=real_data[i];
				this->precursor_ion->fragments.push_back(fragment);
			}
			// Free allocated memory
			delete[] decoded_data;
			delete [] real_data;
			XMLString::release( &data);
		} else if (this->run.conversion_software == msms_run::importWiff) {
			unsigned int decodedLength;
			XMLByte* decoded_data=Base64::decodeToXMLByte(chars, &decodedLength);
			double* real_data=(double* )decoded_data;

			for (int i=0; i< 2*this->precursor_ion->peaksCount; i++) {
				ion fragment;
				fragment.mz=real_data[i];
				i++;
				fragment.intensity=real_data[i];
				this->precursor_ion->fragments.push_back(fragment);
			}
			XMLString::release(&decoded_data);
		}
	}
}

void sax_xml_data_handler::fatalError(const SAXParseException& ex){
    char* message = XMLString::transcode(ex.getMessage());
    cout << "Exception message is: \n"<< message << "\n";
    XMLString::release(&message);
    exit(-1);
}
