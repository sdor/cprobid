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
TEST_CASE( "parse name", "[swissprot,parser]" ) {
    string data = "<entry><name>Name</name></entry>";
    auto doc = xmlReadMemory(data.c_str(),data.length(),NULL,NULL,XML_PARSE_NOBLANKS);
    auto ctx = xmlXPathNewContext(doc);
    string value = parseProteinRecommendedName(ctx);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    REQUIRE(value == "Name");
}