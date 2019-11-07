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

#ifndef SAX_XML_DATA_HANDLER_H_
#define SAX_XML_DATA_HANDLER_H_

#include <xercesc/sax2/DefaultHandler.hpp>
#include "experimental_ion.h"
#include "msms_run.h"
XERCES_CPP_NAMESPACE_USE
class sax_xml_data_handler : public DefaultHandler {

    enum {
    	MZ_XML,
        SURVEY_SCAN,
        MASS_ARRAY,
        INTENSITY_ARRAY,
        CHARGE_ARRAY,
        SCAN,
        PEAKS,
        PRECURSOR_MZ,
        MSMS_SCAN,
        MSMS_MASS,
        MSMS_INTENSITY,
        MSMS_CHARGE,
        DOCUMENT
    };

    int parser_state;

    experimental_ion *precursor_ion;
    msms_run run;
    vector<experimental_ion> ions;

public:
    sax_xml_data_handler(string file_name);
    virtual ~sax_xml_data_handler();
    void startElement(
    const   XMLCh* const    uri,
            const   XMLCh* const    localname,
            const   XMLCh* const    qname,
            const   Attributes&     attrs
    );
    void endElement(const XMLCh *const uri,
            const XMLCh *const localname,
            const XMLCh *const qname);
    void characters(const XMLCh *const chars, const unsigned int length);
    void fatalError(const SAXParseException&);
    vector<experimental_ion>* get_ions(){return &ions;};
};

#endif /*SAX_XML_DATA_HANDLER_H_*/
