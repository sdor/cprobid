#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <swissprot.h>
#include <AminoAcidSeq.h>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>


using namespace std;
using namespace swissprot;
using namespace bsoncxx;

typedef struct {
  mongocxx::database* db;
} metadata;

typedef struct {
  metadata* metadata;
  void* data;
} swissprot_reader_data;

void reader(void *data) {
  using builder::stream::document;
  using builder::stream::array;
  using builder::stream::open_document;
  using builder::stream::close_document;
  using bsoncxx::builder::stream::finalize;
  mongocxx::collection peptides = (*((swissprot_reader_data*) data)->metadata->db)["peptides"];
  auto doc = xmlReadMemory((const char*)data,strlen((const char *)data),NULL,NULL,XML_PARSE_NOBLANKS);
  auto ctx = xmlXPathNewContext(doc);
  xmlXPathRegisterNs(ctx,(const xmlChar*)"sw",(const xmlChar*)"http://uniprot.org/uniprot");
  std::string name = parseName(ctx);
  std::string protein = parseProteinRecommendedName(ctx);
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
 
          peptides.find_one_and_update(document{}
            << "name" << name
            << "organism" << organism.scientific_name
            << "n_missed" << static_cast<int>(n_missed)
            << "peptide" << seq.toString()
            << finalize,
            document{} 
              << "$set" << open_document
                  << "name" << name
                  << "organism" << organism.scientific_name
                  << "n_missed" << static_cast<int>(n_missed)
                  << "peptide" << seq.toString()
                  << close_document  
              << finalize
          );
        }
      }
      
  }
}

int main(int argc, char** argv) {
    read("/Users/sergey/Downloads/uniprot_sprot.xml.gz", reader);
    exit(0);
}