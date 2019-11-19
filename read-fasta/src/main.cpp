#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> digest(std::string& seq) {
    std::vector<std::string> fragments;
    std::ostringstream fragment;
    for(int i=0; i< seq.length(); ++i){
        if(seq[i] == 'K' || seq[i] == 'R') {
            fragment << seq[i];
            fragments.push_back(fragment.str());
            fragment.clear();
        } else {
            fragment << seq[i];
        }
    }
    return fragments;
}
int main(int argc, char** argv) {
    for(int i=0; i<argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    if(argc > 1) {
        std::ifstream in{argv[1],std::ios::binary};
        bool inProtein = false;
        std::ostringstream proteinSeq;
        for(std::string line; std::getline(in,line); ) {
          if(line.front() == '>') {
              std::string seq = proteinSeq.str();
              if(seq != "") {
                  std::vector<std::string> fragments = digest(seq);
              }
              std::cout << line << std::endl;
              inProtein = true;
              proteinSeq.clear();
          } else if(inProtein) {
              proteinSeq << line;
          }
        }
        in.close();
    }
    return 0;
}