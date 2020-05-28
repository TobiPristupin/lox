#include "Parser.h"
#include "TokenType.h"
#include "LoxException.h"
#include "Expr.h"

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

Expr *Parser::parse() {
    return expression();
}

Expr *Parser::expression() {
    return equality();
}

Expr *Parser::equality() {
    Expr *expr = comparison();
    std::vector<TokenType> equalityTokens = {TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL};
    while (match(equalityTokens)){
        Token op = peek();
        advance();
        Expr* e = comparison();
        expr = new BinaryExpr(expr, e, &op);
    }

    return expr;
}

Expr *Parser::comparison() {
    Expr *expr = addition();
    std::vector<TokenType> comparisonTokens = {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL};
    while (match(comparisonTokens)){
        Token op = peek();
        advance();
        Expr *e = addition();
        expr = new BinaryExpr(expr, e, &op);
    }

    return expr;
}

Expr *Parser::addition() {
    Expr *expr = multiplication();
    std::vector<TokenType> additionTokens = {TokenType::MINUS, TokenType::PLUS};
    while (match(additionTokens)){
        Token op = peek();
        advance();
        Expr *e = multiplication();
        expr = new BinaryExpr(expr, e, &op);
    }

    return expr;
}

Expr *Parser::multiplication() {
    Expr *expr = unary();
    std::vector<TokenType> multiplicationTokens = {TokenType::SLASH, TokenType::STAR};
    while (match(multiplicationTokens)){
        Token op = peek();
        advance();
        Expr *e = unary();
        expr = new BinaryExpr(expr, e, &op);
    }

    return expr;
}

Expr *Parser::unary() {
    std::vector<TokenType> unaryTokens = {TokenType::MINUS, TokenType::BANG};
    if (match(unaryTokens)){
        Token op = peek();
        advance();
        Expr *right = unary();
        Expr *expr = new UnaryExpr(&op, right);
        return expr;
    }

    return primary();
}

Expr *Parser::primary() {
    std::vector<TokenType> primaryTokens = {TokenType::TRUE, TokenType::FALSE, TokenType::NIL, TokenType::NUMBER, TokenType::STRING};
    if (match(primaryTokens)){
        advance();
        return new LiteralExpr(peek().literal);
    }

    if (match(TokenType::LEFT_PAREN)){
        Expr *expr = expression();
        if (!match(TokenType::RIGHT_PAREN)){
            throw LoxException("Missing closing parenthesis", peek().line);
        }
        advance();
        return new GroupingExpr(expr);
    }

    throw LoxException("Expected expression");
}

bool Parser::match(TokenType type) {
    Token t = peek();
    return t.type == type;
}

bool Parser::match(std::vector<TokenType> &types) {
    for (TokenType type : types){
        if (match(type)){
            return true;
        }
    }

    return false;
}

Token Parser::peek() {
    return tokens[current];
}

void Parser::advance() {
    current++;
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}




