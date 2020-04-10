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
    int start = 0, current = 0, line = 1;
    std::string source;
    std::vector<Token> tokens;

    bool isAtEnd();
    std::optional<Token> scanNextToken();
    void advance();
    bool currentCharMatches(char expected);
    char peek();
    Token createToken(TokenType type, const std::variant<int, float, std::string, std::nullptr_t>& literal);
};


#endif //JLOX_SCANNER_H
