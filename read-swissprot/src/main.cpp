#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <cstring>
#include <iostream>
#include <swissprot.h>
using namespace std;
using namespace swissprot;
void reader(void *data) {
  auto doc = xmlReadMemory((const char*)data,strlen((const char *)data),NULL,NULL,XML_PARSE_NOBLANKS);
  auto ctx = xmlXPathNewContext(doc);
  xmlXPathRegisterNs(ctx,(const xmlChar*)"sw",(const xmlChar*)"http://uniprot.org/uniprot");
  string name = parseName(ctx);
  string protein = parseProteinRecommendedName(ctx);
  organism organism = parseOrganism(ctx);
  sequence sequence = parseSequence(ctx);
  xmlXPathFreeContext(ctx);
  xmlFreeDoc(doc);
  cout << name << "|" << protein << "|" << organism.scientific_name << endl;
}
int main(int argc, char** argv) {
    read("/Users/sergey/Downloads/uniprot_sprot.xml.gz", reader);
    return 0;
}

