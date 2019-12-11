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
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>


using namespace std;
using namespace swissprot;
using namespace bsoncxx;


void reader(void *data, void *db) {
  using builder::stream::document;
  using builder::stream::array;
  using builder::stream::open_document;
  using builder::stream::close_document;
  using bsoncxx::builder::stream::finalize;
  
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
      mongocxx::collection peptides = (*(mongocxx::database *)db)["peptides"];
      auto options = mongocxx::options::find_one_and_update();
      options.upsert(true);
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
              << finalize,
              options
          );
        }
      }
      
  }
}

int main(int argc, char** argv) {
    auto biosys_uri = std::getenv("BIOSYS_MONGO_URI");
    auto swissprot_xml = std::getenv("SWISSPROT_XML");
    mongocxx::instance instance{};
    mongocxx::uri uri(biosys_uri);
    mongocxx::client client(uri);
    mongocxx::database db = client["biosys"];
    read(swissprot_xml, reader, &db);
    return 0;
}