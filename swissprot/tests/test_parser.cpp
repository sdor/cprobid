#include <catch.hpp>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string>
#include <do.h>
#include <parser.h>
#include <libxml/xpathInternals.h>
using namespace std;
using namespace swissprot;
TEST_CASE( "parse name", "[swissprot,parser]" ) {
    string data = "<entry xmlns=\"http://uniprot.org/uniprot\"><name>Name</name></entry>";
    auto doc = xmlReadMemory(data.c_str(),data.length(),NULL,NULL,XML_PARSE_NOBLANKS | XML_PARSE_NOCDATA);
    auto ctx = xmlXPathNewContext(doc);
    xmlXPathRegisterNs(ctx,(const xmlChar*)"sw",(const xmlChar*)"http://uniprot.org/uniprot");
    string value = parseName(ctx);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    REQUIRE(value == "Name");
}

TEST_CASE( "parse protein name", "[swissprot,parser]" ) {
    string data = "<entry xmlns=\"http://uniprot.org/uniprot\"><name>Name</name><protein><recommendedName><fullName>Putative transcription factor 001R</fullName></recommendedName></protein></entry>";
    auto doc = xmlReadMemory(data.c_str(),data.length(),NULL,NULL,XML_PARSE_NOBLANKS);
    auto ctx = xmlXPathNewContext(doc);
    xmlXPathRegisterNs(ctx,(const xmlChar*)"sw",(const xmlChar*)"http://uniprot.org/uniprot");
    string value = parseProteinRecommendedName(ctx);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    REQUIRE(value == "Putative transcription factor 001R");
}

TEST_CASE( "parse organism", "[swissprot,parser]" ) {
    string data = "<entry xmlns=\"http://uniprot.org/uniprot\"><name>Name</name><organism><name type=\"scientific\">Frog virus 3 (isolate Goorha)</name><name type=\"common\">FV-3</name><dbReference type=\"NCBI Taxonomy\" id=\"654924\"/><lineage><taxon>Viruses</taxon><taxon>Iridoviridae</taxon><taxon>Alphairidovirinae</taxon><taxon>Ranavirus</taxon></lineage></organism><protein><recommendedName><fullName>Putative transcription factor 001R</fullName></recommendedName></protein></entry>";
    auto doc = xmlReadMemory(data.c_str(),data.length(),NULL,NULL,XML_PARSE_NOBLANKS);
    auto ctx = xmlXPathNewContext(doc);
    xmlXPathRegisterNs(ctx,(const xmlChar*)"sw",(const xmlChar*)"http://uniprot.org/uniprot");
    organism value = parseOrganism(ctx);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    REQUIRE(value.scientific_name == "Frog virus 3 (isolate Goorha)");
    REQUIRE(value.common_name == "FV-3");
    REQUIRE(value.taxon == "654924");
}



TEST_CASE( "parse sequence", "[swissprot,parser]" ) {
    string data = "<entry xmlns=\"http://uniprot.org/uniprot\"><name>Name</name><protein><recommendedName><fullName>Putative transcription factor 001R</fullName></recommendedName></protein><sequence length=\"256\" mass=\"29735\" checksum=\"B4840739BF7D4121\" modified=\"2004-07-19\" version=\"1\">PEPTIDE</sequence></entry>";
    auto doc = xmlReadMemory(data.c_str(),data.length(),NULL,NULL,XML_PARSE_NOBLANKS);
    auto ctx = xmlXPathNewContext(doc);
    xmlXPathRegisterNs(ctx,(const xmlChar*)"sw",(const xmlChar*)"http://uniprot.org/uniprot");
    sequence el = parseSequence(ctx);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    // REQUIRE(el.name == "sequence");
    REQUIRE(el.checksum == "B4840739BF7D4121");
    REQUIRE(el.version == 1);
    REQUIRE(el.modified == "2004-07-19");
    REQUIRE(el.sequence == "PEPTIDE");
}

