//
// Created by pristu on 4/9/20.
//

#include <iostream>
#include <utility>
#include "ErrorLogger.h"

void ErrorLogger::error(int line, const std::string &message) {
    std::cerr << "[line " << line << "] ";
    error(message);
}

void ErrorLogger::error(const std::string &message) {
    std::cerr << "Error: " << message << "\n";
}
