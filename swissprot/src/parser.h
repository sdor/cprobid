#ifndef SWISSPROT_PARSER_H
#define SWISSPROT_PARSER_H
#include <string>
using namespace std;
namespace swissprot {
    typedef struct {
        string taxon;
        string name;
    } organism;

    typedef struct {
        string name;
        string seq;
    } protein;

    typedef struct {
        string name;
        organism organism;
    } entry;

    extern string parseName(xmlXPathContextPtr ctx);
    extern string parseProteinRecommendedName(xmlXPathContextPtr ctx);
}

#endif