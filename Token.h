#ifndef JLOX_TOKEN_H
#define JLOX_TOKEN_H

#include <string>
#include <iosfwd>
#include "TokenType.h"


struct Token {

    TokenType type;
    std::string lexeme;
    int line{};

    Token(TokenType type, const std::string &lexeme, int line);
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

#endif //JLOX_TOKEN_H
