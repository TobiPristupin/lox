#ifndef JLOX_SCANNER_H
#define JLOX_SCANNER_H


#include <vector>
#include "Token.h"

class Scanner {
public:
    Scanner(const std::string& source);
    std::vector<Token> scanTokens();

private:
    std::string source;
    std::vector<Token> tokens;

};


#endif //JLOX_SCANNER_H
