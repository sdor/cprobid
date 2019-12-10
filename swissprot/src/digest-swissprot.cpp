#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <swissprot.h>
#include <AminoAcidSeq.h>
#include <bsoncxx/builder/stream/document.hpp>

using namespace std;
using namespace swissprot;
using bsoncxx::builder::stream::document;

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
  if(organism.scientific_name == "Homo sapiens") {
      auto aminoAcidSeq = protein::AminoAcidSeq { sequence.sequence };
      auto digest = aminoAcidSeq.trypsinize(1);
      for (auto it = digest.begin(); it != digest.end(); ++it) {
        auto n_missed = it->first;
        for(auto &seq: it->second) {
          
        }
      }
      
  }
}

int main(int argc, char** argv) {
    read("/Users/sergey/Downloads/uniprot_sprot.xml.gz", reader);
    exit(0);
}