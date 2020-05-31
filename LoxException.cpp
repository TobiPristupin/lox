//
// Created by pristu on 4/11/20.
//

#include <iostream>
#include "LoxException.h"

LoxException::LoxException(std::string message, int line, int pos) : line(line), pos(pos) {
    this->message = "";
    if (line != -1){
        if (pos != -1){
            this->message += "[" + std::to_string(line) + ":" + std::to_string(pos) + "] ";
        } else {
            this->message += "[" + std::to_string(line) + "] ";
        }
    }

    this->message += "Error: " + message;
}

const char *LoxException::what() const noexcept {
    return message.c_str();
}

ScanningException::ScanningException(std::string message, int line, int pos) : LoxException(message, line, pos) {
    this->message = "[" + std::to_string(line) + ":" + std::to_string(pos) + "] " +  "Scanning Error: " + message;
}

const char *ScanningException::what() const noexcept {
    return message.c_str();
}

ParsingException::ParsingException(std::string message, int line) : LoxException(message, line) {
    this->message = "[" + std::to_string(line) + "] " +  "Parsing Error: " + message;
}

const char *ParsingException::what() const noexcept {
    return message.c_str();
}
