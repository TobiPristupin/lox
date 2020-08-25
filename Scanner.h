#ifndef JLOX_SCANNER_H
#define JLOX_SCANNER_H

#include <map>
#include <optional>
#include <string>
#include <vector>
#include "Token.h"
#include "TokenType.h"

class Scanner {
public:
    Scanner(const std::string& source);
    std::vector<Token> scanTokens();

private:
    int start = 0, current = 0, line = 1, pos_in_line = 1;
    std::string source;
    std::vector<Token> tokens;
    static std::map<std::string, TokenType> reservedKeywords;

    bool isAtEnd();
    std::optional<Token> scanNextToken();
    void advance();
    bool currentCharMatches(char expected);
    char peek();
    Token createToken(TokenType type);
    Token createStringToken();
    static bool validForIdentifier(char c);
    std::optional<Token> scanString();
    std::optional<Token> scanNumber();
    std::optional<Token> scanIdentifier();
    static bool isWhitespace(char c);
    void nextLine();

};


#endif //JLOX_SCANNER_H
