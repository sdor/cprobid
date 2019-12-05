#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xmlreader.h>
#include <reader.h>

namespace swissprot {
  void read(const char* filename, void (*cb)(void*)) {
    auto reader = xmlReaderForFile(filename,NULL,  XML_PARSE_NOBLANKS);
    if (reader == nullptr) { return; }
    
    while (xmlTextReaderRead(reader) == 1) {
      if( xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT && xmlStrEqual(xmlTextReaderConstLocalName(reader), (const xmlChar *) "entry") == 1) {
        auto entry = xmlTextReaderReadOuterXml(reader);
        cb(entry);
        xmlFree(entry);
      }
    }
    xmlFreeTextReader(reader);
  }  
}
