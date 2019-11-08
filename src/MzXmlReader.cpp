#include <MzXmlReader.h>
#include <base64.h>
#include <sstream>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xmlreader.h>
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
void MzXmlReader::read() {
  auto state = MZ_XML;
  int precision = 32;
  char* peaksValue;
  int peaksCount;
  char* peaksBuffer;  
  auto reader =  xmlReaderForFile(this->filename.c_str(),NULL,  XML_PARSE_NOBLANKS);
  std::stringstream peaksBuff;
  if (reader == nullptr) { return; }
  while (xmlTextReaderRead(reader) == 1) {
      if( xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT && xmlStrEqual(xmlTextReaderConstLocalName(reader), (const xmlChar *) "scan") == 1) {
        auto _num =  xmlTextReaderGetAttribute(reader,(xmlChar*)"num");
        auto _peaksCount = xmlTextReaderGetAttribute(reader,(xmlChar*)"num");
        peaksCount = std::atoi((const char*)_peaksCount);
        xmlFree(_peaksCount);
        xmlFree(_num);
      } else if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT && xmlStrEqual(xmlTextReaderConstLocalName(reader), (const xmlChar *) "peaks") == 1) {
        state = PEAKS;
        peaksBuff.clear();
        auto _precision =  xmlTextReaderGetAttribute(reader,(xmlChar*)"precision");
        precision = std::atoi((const char*)_precision);
        peaksValue = (char *)xmlTextReaderReadInnerXml(reader);
        if(precision == 32){
          peaksBuff = (char *)new char[8*peaksCount];
        } else if(precision == 64) {
          peaksBuff = (char *)new char[16*peaksCount];
        }
        xmlFree(_precision);
      } else if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT && xmlStrEqual(xmlTextReaderConstLocalName(reader), (const xmlChar *) "peaks") == 1) {
          state = SCAN;
      } else if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT && xmlStrEqual(xmlTextReaderConstLocalName(reader), (const xmlChar *) "scan") == 1) {
        state = MZ_XML;
      }
  }
};