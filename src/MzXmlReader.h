#indef MZXML_READER_H
#define MZXML_READER_H
#include <string>

class MzXmlReader
{
private:
    std::string filename;

public:
    MzXmlReader(const std::string &filename)
    {
        this->filename;
    }

    void read();
};
#endif