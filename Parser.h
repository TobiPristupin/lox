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

    //This variable keeps track of  the amount of loops (for or while) the parser is currently nested in. It is used to avoid break
    //and continue statements outside of any loop.
    int loopNestingLevel = 0;

    UniqueStmtPtr declaration();
    UniqueStmtPtr varStatement();
    UniqueStmtPtr statement();
    UniqueStmtPtr exprStatement();
    UniqueStmtPtr printStatement();
    UniqueStmtPtr ifStatement();
    UniqueStmtPtr whileStatement();
    UniqueStmtPtr forStatement();


    std::vector<UniqueStmtPtr> block();

    UniqueExprPtr expression();
    UniqueExprPtr assignment();
    UniqueExprPtr logicOr();
    UniqueExprPtr logicAnd();
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


    UniqueStmtPtr breakStatement();

    UniqueStmtPtr continueStatement();
};


#endif //JLOX_PARSER_H
