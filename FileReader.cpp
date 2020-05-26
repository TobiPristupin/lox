//
// Created by pristu on 5/21/20.
//

#include "FileReader.h"
#include "LoxException.h"

FileReader::FileReader(const std::string &filename) : filename(filename) {
    fileStream.open(filename);
    if (!fileStream.is_open()){
        throw LoxException("File " + filename + " not found");
    }
}

std::string FileReader::readAll() {
    std::string data((std::istreambuf_iterator<char>(fileStream)),std::istreambuf_iterator<char>());
    return data;
}

FileReader::~FileReader() {
    fileStream.close();
}


