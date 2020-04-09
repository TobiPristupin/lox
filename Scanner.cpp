//
// Created by pristu on 4/9/20.
//

#include "Scanner.h"

Scanner::Scanner(const std::string &source) {
    this->source = source;
}

std::vector<Token> Scanner::scanTokens() {
    return tokens;
}
