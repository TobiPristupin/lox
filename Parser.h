#ifndef JLOX_PARSER_H
#define JLOX_PARSER_H


#include <vector>
#include <optional>
#include "Token.h"
#include "Expr.h"
#include "LoxError.h"
#include "Stmt.h"

class Parser {
public:
    Parser(const std::vector<Token> &tokens);
    std::vector<UniqueStmtPtr> parse(bool &successFlag);


private:
    std::vector<Token> tokens;
    int current = 0;
    bool hadError = false;

    UniqueStmtPtr declaration();
    UniqueStmtPtr varStatement();
    UniqueStmtPtr statement();
    UniqueStmtPtr exprStatement();
    UniqueStmtPtr printStatement();
    UniqueStmtPtr ifStatement();

    std::vector<UniqueStmtPtr> block();

    UniqueExprPtr expression();
    UniqueExprPtr assignment();
    UniqueExprPtr equality();
    UniqueExprPtr comparison();
    UniqueExprPtr addition();
    UniqueExprPtr multiplication();
    UniqueExprPtr unary();
    UniqueExprPtr primary();

    bool match(const TokenType &type);
    bool match(const std::vector<TokenType> &types);
    bool check(const TokenType &type);
    Token expect(const TokenType &type, const std::string &error_message);
    Token peek();
    Token advance();
    Token previous();
    bool isAtEnd();
    LoxParsingError error(const std::string &message, int line) noexcept(false);
    void synchronize();
};


#endif //JLOX_PARSER_H
