#include <iostream>
#include "Parser.h"
#include "TokenType.h"
#include "LoxError.h"
#include "Expr.h"

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

std::vector<UniqueStmtPtr> Parser::parse(bool &successFlag) {
    successFlag = true;
    std::vector<UniqueStmtPtr> statements;
    while (!isAtEnd()){
        UniqueStmtPtr stmt = declaration();
        statements.push_back(std::move(stmt));
    }

    successFlag = !hadError;
    return statements;
}

//If a parsing error is encountered, this function will attempt to synchronize the parser and then return nullptr.
UniqueStmtPtr Parser::declaration() {
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

UniqueStmtPtr Parser::varStatement() {
    Token identifier = expect(TokenType::IDENTIFIER, "Expected identifier");
    UniqueExprPtr initializer = nullptr;
    if (match(TokenType::EQUAL)){
        initializer = expression();
    }

    expect(TokenType::SEMICOLON, "Expect ';' after variable declaration");
    return std::make_unique<VarStmt>(identifier, std::move(initializer));
}

UniqueStmtPtr Parser::statement() {
    if (match(TokenType::PRINT)) return printStatement();
    if (match(TokenType::LEFT_BRACE)) return std::make_unique<BlockStmt>(block());

    return exprStatement();
}

std::vector<UniqueStmtPtr> Parser::block() {
    std::vector<UniqueStmtPtr> statements;
    while (!isAtEnd() && !check(TokenType::RIGHT_BRACE)){
        UniqueStmtPtr stmt = declaration();
        statements.push_back(std::move(stmt));
    }

    expect(TokenType::RIGHT_BRACE, "Expected } after block");
    return statements;
}

UniqueStmtPtr Parser::exprStatement() {
    UniqueExprPtr expr = expression();
    expect(TokenType::SEMICOLON, "Expect ';' after value.");
    return std::make_unique<ExpressionStmt>(std::move(expr));
}

UniqueStmtPtr Parser::printStatement() {
    UniqueExprPtr expr = expression();
    expect(TokenType::SEMICOLON, "Expect ';' after expression.");
    return std::make_unique<PrintStmt>(std::move(expr));
}

UniqueExprPtr Parser::expression() {
    return assignment();
}

UniqueExprPtr Parser::assignment() {
    UniqueExprPtr expr = equality();
    if (match(EQUAL)){
        Token op = previous();
        UniqueExprPtr rvalue = assignment();
        VariableExpr* lvalue = dynamic_cast<VariableExpr*>(expr.get());

        if (lvalue){
            Token identifier = lvalue->identifier;
            return std::make_unique<AssignmentExpr>(identifier, std::move(rvalue));
        }

        throw error("Invalid assignment target", op.line);
    }

    return expr;
}

UniqueExprPtr Parser::equality() {
    UniqueExprPtr expr = comparison();
    std::vector<TokenType> equalityTokens = {TokenType ::EQUAL_EQUAL, TokenType::BANG_EQUAL};
    while (match(equalityTokens)){
        Token op = previous();
        UniqueExprPtr right = comparison();
        expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), op);
    }

    return expr;
}

UniqueExprPtr Parser::comparison() {
    UniqueExprPtr expr = addition();
    std::vector<TokenType> comparisonTokens = {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL};
    while (match(comparisonTokens)){
        Token op = previous();
        UniqueExprPtr right = addition();
        expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), op);
    }

    return expr;
}

UniqueExprPtr Parser::addition() {
    UniqueExprPtr expr = multiplication();
    std::vector<TokenType> additionTokens = {TokenType::MINUS, TokenType::PLUS};
    while (match(additionTokens)){
        Token op = previous();
        UniqueExprPtr right = multiplication();
        expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), op);
    }

    return expr;

}

UniqueExprPtr Parser::multiplication() {
    UniqueExprPtr expr = unary();
    std::vector<TokenType> multiplicationTokens = {TokenType::SLASH, TokenType::STAR};
    while (match(multiplicationTokens)){
        Token op = previous();
        UniqueExprPtr right = unary();
        expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), op);
    }

    return expr;
}

UniqueExprPtr Parser::unary() {
    std::vector<TokenType> unaryTokens = {TokenType::MINUS, TokenType::BANG};
    if (match(unaryTokens)){
        Token op = previous();
        UniqueExprPtr right = unary();
        return std::make_unique<UnaryExpr>(op, std::move(right));
    }

    return primary();
}

UniqueExprPtr Parser::primary() {
    if (match(TokenType::NUMBER)) return std::make_unique<LiteralExpr>(previous().literal);
    if (match(TokenType::STRING)) return std::make_unique<LiteralExpr>(previous().literal);
    if (match(TokenType::TRUE)) return std::make_unique<LiteralExpr>(previous().literal);
    if (match(TokenType::FALSE)) return std::make_unique<LiteralExpr>(previous().literal);
    if (match(TokenType::NIL)) return std::make_unique<LiteralExpr>(previous().literal);
    if (match(TokenType::IDENTIFIER)) return std::make_unique<VariableExpr>(previous());

    if (match(TokenType::LEFT_PAREN)){
        UniqueExprPtr expr = expression();
        expect(TokenType::RIGHT_PAREN, "Expect ')' after expression");
        return std::make_unique<GroupingExpr>(std::move(expr));
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


