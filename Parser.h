//
// Created by pristu on 4/24/20.
//

#ifndef JLOX_PARSER_H
#define JLOX_PARSER_H


#include <vector>
#include <optional>
#include "Token.h"
#include "Expr.h"

class Parser {
public:
    Parser(const std::vector<Token> &tokens);
    Expr* parse();

private:
    std::vector<Token> tokens;
    int current = 0;
    Expr* expression();
    Expr* equality();
    Expr* comparison();
    Expr* addition();
    Expr* multiplication();
    Expr* unary();
    Expr* primary();
    bool match(TokenType type);
    bool match(std::vector<TokenType> &types);
    Token peek();
    void advance();
    bool isAtEnd();
};


#endif //JLOX_PARSER_H
