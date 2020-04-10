#ifndef JLOX_TOKEN_H
#define JLOX_TOKEN_H

#include <string>
#include <any>
#include "TokenType.h"

struct Token {

    TokenType type;
    std::string lexeme;
    std::any literal;
    int line;

    Token(TokenType type, const std::string &lexeme, const std::any &literal, int line) : type(type), lexeme(lexeme),
                                                                                          literal(literal),
                                                                                          line(line) {}

    std::string to_string(){
        return lexeme;
    }
};


#endif //JLOX_TOKEN_H
