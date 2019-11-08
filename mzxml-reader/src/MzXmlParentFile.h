#ifndef MzXML_ParentFile_H
#define MzXML_ParentFile_H
#include <string>
namespace MzXML {
    class ParentFile {
        private:
        std::string fileName;
        std::string fileType;
        std::string fileSHA1;
        public:
        ParentFile(const std::string& fileName, const std::string& fileType, const std::string& fileSHA1) {
            this->fileName = fileName;
            this->fileType = fileType;
            this->fileSHA1 = fileSHA1;
        }
        std::string getFileName() const { return this->fileName;}
        std::string getFileType() const { return this->fileType;}
        std::string getFileSHA1() const { return this->fileSHA1;}
    };
}
#endif