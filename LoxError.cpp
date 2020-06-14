//
// Created by pristu on 4/11/20.
//

#include <iostream>
#include "LoxError.h"

LoxError::LoxError(const std::string &message, int line, int pos) : line(line), pos(pos) {
    this->message = "";
    if (line != -1){
        if (pos != -1){
            this->message += "[Line " + std::to_string(line) + ":" + std::to_string(pos) + "] ";
        } else {
            this->message += "[Line " + std::to_string(line) + "] ";
        }
    }

    this->message += "Error: " + message;
}

const char *LoxError::what() const noexcept {
    return message.c_str();
}

LoxScanningError::LoxScanningError(const std::string &message, int line, int pos) : LoxError(message, line, pos) {
    this->message = "[Line " + std::to_string(line) + ":" + std::to_string(pos) + "] " +  "Scanning Error: " + message;
}

const char *LoxScanningError::what() const noexcept {
    return message.c_str();
}

LoxParsingError::LoxParsingError(const std::string &message, int line) : LoxError(message, line) {
    this->message = "[Line " + std::to_string(line) + "] " +  "Parsing Error: " + message;
}

const char *LoxParsingError::what() const noexcept {
    return message.c_str();
}

LoxRuntimeError::LoxRuntimeError(const std::string &message, int line) : LoxError(message, line) {
    this->message = "[Line " + std::to_string(line) + "] " +  "Runtime Error: " + message;
}

const char *LoxRuntimeError::what() const noexcept {
    return message.c_str();
}
