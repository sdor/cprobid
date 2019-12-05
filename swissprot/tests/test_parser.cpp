#include <catch.hpp>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string>
#include <parser.h>
using namespace std;
using namespace swissprot;
TEST_CASE( "parse name", "[swissprot,parser]" ) {
    string data = "<entry><name>Name</name></entry>";
    auto doc = xmlReadMemory(data.c_str(),data.length(),NULL,NULL,XML_PARSE_NOBLANKS);
    auto ctx = xmlXPathNewContext(doc);
    string value = parseName(ctx);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    REQUIRE(value == "Name");
}
TEST_CASE( "parse protein name", "[swissprot,parser]" ) {
    string data = "<entry><name>Name</name><protein><recommendedName><fullName>Putative transcription factor 001R</fullName></recommendedName></protein></entry>";
    auto doc = xmlReadMemory(data.c_str(),data.length(),NULL,NULL,XML_PARSE_NOBLANKS);
    auto ctx = xmlXPathNewContext(doc);
    string value = parseProteinRecommendedName(ctx);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    REQUIRE(value == "Putative transcription factor 001R");
}
TEST_CASE( "parse sequence", "[swissprot,parser]" ) {
    string data = "<entry><name>Name</name><protein><recommendedName><fullName>Putative transcription factor 001R</fullName></recommendedName></protein><sequence length=\"256\" mass=\"29735\" checksum=\"B4840739BF7D4121\" modified=\"2004-07-19\" version=\"1\">PEPTIDE</sequence></entry>";
    auto doc = xmlReadMemory(data.c_str(),data.length(),NULL,NULL,XML_PARSE_NOBLANKS);
    auto ctx = xmlXPathNewContext(doc);
    element el = parseSequence(ctx);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    REQUIRE(el.name == "sequence");
    REQUIRE(el.attributes["checksum"] == "B4840739BF7D4121");
    REQUIRE(el.attributes["version"] == "1");
    REQUIRE(el.content == "PEPTIDE");
}

