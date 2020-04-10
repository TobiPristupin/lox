#ifndef JLOX_SCANNER_H
#define JLOX_SCANNER_H
#include <vector>
#include "Token.h"
#include <optional>

class Scanner {
public:
    Scanner(const std::string& source);
    std::vector<Token> scanTokens();

private:
    int start = 0, next = 0, line = 1;
    std::string source;
    std::vector<Token> tokens;

    bool isAtEnd();
    std::optional<Token> scanNextToken();
    char advanceChar();
    bool nextCharMatches(char expected);
    Token createToken(TokenType type, std::any literal);
};


#endif //JLOX_SCANNER_H
