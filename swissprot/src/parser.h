#ifndef SWISSPROT_PARSER_H
#define SWISSPROT_PARSER_H
#include <string>
#include <map>
#include <do.h>
using namespace std;
namespace swissprot {
    // typedef struct {
    //     string taxon;
    //     string name;
    // } organism;

    // typedef struct {
    //     string name;
    //     string seq;
    // } protein;

    // typedef struct {
    //     string name;
    //     organism organism;
    // } entry;

    typedef struct {
        string name;
        map<string,string> attributes;
        string content;
    } element;

    extern string parseName(xmlXPathContextPtr ctx);
    extern string parseProteinRecommendedName(xmlXPathContextPtr ctx);
    extern sequence parseSequence(xmlXPathContextPtr ctx);
    extern organism parseOrganism(xmlXPathContextPtr ctx);
}

#endif