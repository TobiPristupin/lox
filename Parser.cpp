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
    std::vector<TokenType> equalityTokens = {TokenType ::EQUAL_EQUAL, TokenType::BANG_EQUAL};
    while (match(equalityTokens)){
        Token op = previous();
        Expr* right = comparison();
        expr = new BinaryExpr(expr, right, &op);
    }

    return expr;
}

Expr *Parser::comparison() {
    Expr *expr = addition();
    std::vector<TokenType> comparisonTokens = {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL};
    while (match(comparisonTokens)){
        Token op = previous();
        Expr* right = addition();
        expr = new BinaryExpr(expr, right, &op);
    }

    return expr;
}

Expr *Parser::addition() {
    Expr *expr = multiplication();
    std::vector<TokenType> additionTokens = {TokenType::MINUS, TokenType::PLUS};
    while (match(additionTokens)){
        Token op = previous();
        Expr* right = multiplication();
        expr = new BinaryExpr(expr, right, &op);
    }

    return expr;
}

Expr *Parser::multiplication() {
    Expr *expr = unary();
    std::vector<TokenType> multiplicationTokens = {TokenType::SLASH, TokenType::STAR};
    while (match(multiplicationTokens)){
        Token op = previous();
        Expr* right = unary();
        expr = new BinaryExpr(expr, right, &op);
    }

    return expr;
}

Expr *Parser::unary() {
    std::vector<TokenType> unaryTokens = {TokenType::MINUS, TokenType::BANG};
    if (match(unaryTokens)){
        Token op = previous();
        Expr* right = unary();
        return new UnaryExpr(&op, right);
    }

    return primary();
}

Expr *Parser::primary() {
    if (match(TokenType::NUMBER)) return new LiteralExpr(previous().literal);
    if (match(TokenType::STRING)) return new LiteralExpr(previous().literal);
    if (match(TokenType::TRUE)) return new LiteralExpr(previous().literal);
    if (match(TokenType::FALSE)) return new LiteralExpr(previous().literal);
    if (match(TokenType::NIL)) return new LiteralExpr(previous().literal);

    if (match(TokenType::LEFT_PAREN)){
        Expr *expr = expression();
        expect(TokenType::RIGHT_PAREN, "Expect ')' after expression");
        return new GroupingExpr(expr);
    }

    throw ParsingException("Expected expression", peek().line);
}

bool Parser::match(TokenType type) {
    std::vector<TokenType> vec = {type};
    return match(vec);
}

//Checks if the current token type matches one from types AND CONSUMES IT
bool Parser::match(std::vector<TokenType> &types) {
    for (TokenType &type : types){
        if (check(type)){
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType &type) {
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

void Parser::expect(TokenType type, std::string error_message){
    if (check(type)) advance();
    else throw ParsingException(error_message, peek().line);
}


