#ifndef SWISSPROT_DO_H
#define SWISSPROT_DO_H
#include <string>

using namespace std;
namespace swissprot {
    typedef struct {
       string scientific_name;
       string common_name;
       string taxon;
    } organism;
    typedef struct {
        string sequence;
        string checksum;
        int version;
    } sequence;
}
#endif