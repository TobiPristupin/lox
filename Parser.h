//
// Created by pristu on 4/24/20.
//

#ifndef JLOX_PARSER_H
#define JLOX_PARSER_H


#include <vector>
#include <optional>
#include "Token.h"
#include "Expr.h"
#include "LoxError.h"

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
    bool check(TokenType &type);
    void expect(TokenType type, std::string error_message);
    Token peek();
    Token advance();
    Token previous();
    bool isAtEnd();
};


#endif //JLOX_PARSER_H
