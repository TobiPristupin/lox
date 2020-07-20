#ifndef JLOX_FILEREADER_H
#define JLOX_FILEREADER_H

#include <string>
#include <fstream>

class FileReader {
public:
    FileReader(const std::string &filename);
    ~FileReader();
    std::string readAll();

private:
    std::string filename;
    std::ifstream fileStream;
};


#endif //JLOX_FILEREADER_H
