#ifndef JLOX_TOKEN_H
#define JLOX_TOKEN_H

#include <string>
#include <any>
#include <variant>
#include "TokenType.h"

using lox_literal_t = std::variant<int, float, std::string, std::nullptr_t>;

struct Token {

    TokenType type;
    std::string lexeme;
    lox_literal_t literal;
    int line{};

    Token(TokenType type, const std::string &lexeme, const lox_literal_t &literal,
          int line) : type(type), lexeme(lexeme), literal(literal), line(line) {}

    std::string to_string() {
        std::string s = "Token: " + tokenTypeToString(type) + " "  + lexeme;
        if (std::holds_alternative<std::string>(literal)){
            s += " " + std::get<std::string>(literal);
        } else if (std::holds_alternative<int>(literal)){
            s += " " + std::to_string(std::get<int>(literal));
        } else if (std::holds_alternative<float>(literal)){
            s += " " + std::to_string(std::get<float >(literal));
        }

        s += " " + std::to_string(line);
        return  s;
    }

};


#endif //JLOX_TOKEN_H
