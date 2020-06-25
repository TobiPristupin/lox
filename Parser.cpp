#include <iostream>
#include "Parser.h"
#include "TokenType.h"
#include "LoxError.h"
#include "Expr.h"

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

std::vector<Stmt *> Parser::parse(bool &successFlag) {
    successFlag = true;
    std::vector<Stmt*> statements;
    while (!isAtEnd()){
        Stmt* stmt = declaration();
        statements.push_back(stmt);
    }

    successFlag = !hadError;
    return statements;
}

//If a parsing error is encountered, this function will attempt to synchronize the parser and then return nullptr.
Stmt *Parser::declaration() {
    try {
        if (match(TokenType::VAR)){
            return varStatement();
        }
        return statement();
    } catch (const LoxParsingError &error) {
        //Report the exception but don't let it bubble up and stop the program. Instead, synchronize the parser and keep parsing.
        std::cout << error.what() << "\n";
        hadError = true;
        synchronize();
    }

    return nullptr;
}

Stmt *Parser::varStatement() {
    Token identifier = expect(TokenType::IDENTIFIER, "Expected identifier");
    Expr* initializer = nullptr;
    if (match(TokenType::EQUAL)){
        initializer = expression();
    }

    expect(TokenType::SEMICOLON, "Expect ';' after variable declaration");
    return new VarStmt(identifier, initializer);
}

Stmt *Parser::statement() {
    if (match(TokenType::PRINT)) return printStatement();
    if (match(TokenType::LEFT_BRACE)) return new BlockStmt(block());

    return exprStatement();
}

std::vector<Stmt*> Parser::block() {
    std::vector<Stmt*> statements;
    while (!isAtEnd() && !check(TokenType::RIGHT_BRACE)){
        Stmt* stmt = declaration();
        statements.push_back(stmt);
    }

    expect(TokenType::RIGHT_BRACE, "Expected } after block");
    return statements;
}



Stmt *Parser::exprStatement() {
    Expr* expr = expression();
    expect(TokenType::SEMICOLON, "Expect ';' after value.");
    return new ExpressionStmt(expr);
}

Stmt *Parser::printStatement() {
    Expr* expr = expression();
    expect(TokenType::SEMICOLON, "Expect ';' after expression.");
    return new PrintStmt(expr);
}

Expr *Parser::expression() {
    return assignment();
}

Expr *Parser::assignment() {
    Expr *expr = equality();
    if (match(EQUAL)){
        Token op = previous();
        Expr* value = assignment();
        VariableExpr* lvalue = dynamic_cast<VariableExpr*>(expr);
        if (lvalue){
            return new AssignmentExpr(lvalue->identifier, value);
        }

        throw error("Invalid assignment target", op.line);
    }

    return expr;
}

Expr *Parser::equality() {
    Expr *expr = comparison();
    std::vector<TokenType> equalityTokens = {TokenType ::EQUAL_EQUAL, TokenType::BANG_EQUAL};
    while (match(equalityTokens)){
        Token op = previous();
        Expr* right = comparison();
        expr = new BinaryExpr(expr, right, op);
    }

    return expr;
}

Expr *Parser::comparison() {
    Expr *expr = addition();
    std::vector<TokenType> comparisonTokens = {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL};
    while (match(comparisonTokens)){
        Token op = previous();
        Expr* right = addition();
        expr = new BinaryExpr(expr, right, op);
    }

    return expr;
}

Expr *Parser::addition() {
    Expr *expr = multiplication();
    std::vector<TokenType> additionTokens = {TokenType::MINUS, TokenType::PLUS};
    while (match(additionTokens)){
        Token op = previous();
        Expr* right = multiplication();
        expr = new BinaryExpr(expr, right, op);
    }

    return expr;

}

Expr *Parser::multiplication() {
    Expr *expr = unary();
    std::vector<TokenType> multiplicationTokens = {TokenType::SLASH, TokenType::STAR};
    while (match(multiplicationTokens)){
        Token op = previous();
        Expr* right = unary();
        expr = new BinaryExpr(expr, right, op);
    }

    return expr;
}

Expr *Parser::unary() {
    std::vector<TokenType> unaryTokens = {TokenType::MINUS, TokenType::BANG};
    if (match(unaryTokens)){
        Token op = previous();
        Expr* right = unary();
        return new UnaryExpr(op, right);
    }

    return primary();
}

Expr *Parser::primary() {
    if (match(TokenType::NUMBER)) return new LiteralExpr(previous().literal);
    if (match(TokenType::STRING)) return new LiteralExpr(previous().literal);
    if (match(TokenType::TRUE)) return new LiteralExpr(previous().literal);
    if (match(TokenType::FALSE)) return new LiteralExpr(previous().literal);
    if (match(TokenType::NIL)) return new LiteralExpr(previous().literal);
    if (match(TokenType::IDENTIFIER)) return new VariableExpr(previous());

    if (match(TokenType::LEFT_PAREN)){
        Expr *expr = expression();
        expect(TokenType::RIGHT_PAREN, "Expect ')' after expression");
        return new GroupingExpr(expr);
    }


    throw error("Expected expression", peek().line);
}

bool Parser::match(const TokenType &type) {
    std::vector<TokenType> vec = {type};
    return match(vec);
}

//Checks if the current token type matches one from types AND CONSUMES IT
bool Parser::match(const std::vector<TokenType> &types) {
    for (const TokenType &type : types){
        if (check(type)){
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(const TokenType &type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current-1];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

//checks if the next token is what's expected. Throws an error if it isn't, returns it if it is.
Token Parser::expect(const TokenType &type, const std::string &error_message){
    if (check(type)) return advance();
    else throw error(error_message, peek().line);
}

LoxParsingError Parser::error(const std::string &message, int line) {
    return LoxParsingError(message, line);
}

void Parser::synchronize() { //synchronizes the parser to the next statement when it finds an error
    while (!isAtEnd()){
        if (previous().type == TokenType::SEMICOLON){
            return; //found new statement
        }

        switch (peek().type) {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
                return; //found new statement;
        }

        advance(); //keep advancing until finding a new statement

    }

}


