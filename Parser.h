//
// Created by pristu on 4/24/20.
//

#ifndef JLOX_PARSER_H
#define JLOX_PARSER_H


#include <vector>
#include <optional>
#include "Token.h"
#include "Expression.h"

class Parser {
public:
    Parser(const std::vector<Token> &tokens);
    Expression* parse();

private:
    std::vector<Token> tokens;
    int current = 0;
    Expression* expression();
    Expression* equality();
    Expression* comparison();
    Expression* addition();
    Expression* multiplication();
    Expression* unary();
    Expression* primary();
    bool match(TokenType type);
    bool match(std::vector<TokenType> &types);
    Token peek();
    void advance();
    bool isAtEnd();
};


#endif //JLOX_PARSER_H
