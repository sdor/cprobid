#ifndef MZXML_READER_H
#define MZXML_READER_H
#include <string>
#include <libxml/xmlreader.h>
#include <MzXmlIon.h>

namespace MzXML {
    class MzXmlReader {
    private:
        std::string filename;
        xmlTextReaderPtr reader;
    public:
        MzXmlReader(const std::string &filename) {
            this->filename = filename;
            this->reader = xmlReaderForFile(this->filename.c_str(),NULL,  XML_PARSE_NOBLANKS);
        }

        ~MzXmlReader() {
            xmlFreeTextReader(this->reader);
        }

        void read(void (*cb)(const MzXmlIon* ion));
    };
}
#endif