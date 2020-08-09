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

    enum class FunctionType {
        FUNCTION, METHOD
    };

private:
    std::vector<Token> tokens;
    int current = 0;
    bool hadError = false;


    UniqueStmtPtr declaration();
    UniqueStmtPtr varDeclStatement();
    UniqueStmtPtr functionDeclStatement(FunctionType type);
    UniqueStmtPtr statement();
    UniqueStmtPtr exprStatement();
    UniqueStmtPtr printStatement();
    UniqueStmtPtr ifStatement();
    UniqueStmtPtr whileStatement();
    UniqueStmtPtr forStatement();
    UniqueStmtPtr breakStatement();
    UniqueStmtPtr continueStatement();
    UniqueStmtPtr returnStatement();

    std::vector<UniqueStmtPtr> block();

    UniqueExprPtr expression();
    UniqueExprPtr assignment();
    UniqueExprPtr lambda();
    UniqueExprPtr logicOr();
    UniqueExprPtr logicAnd();
    UniqueExprPtr equality();
    UniqueExprPtr comparison();
    UniqueExprPtr addition();
    UniqueExprPtr multiplication();
    UniqueExprPtr unary();
    UniqueExprPtr prefix();
    UniqueExprPtr postfix();
    UniqueExprPtr functionCall();
    UniqueExprPtr finishCall(UniqueExprPtr expr);
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
