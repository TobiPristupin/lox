
#include "Token.h"
#include "tools/utils.h"

Token::Token(TokenType type, const std::string &lexeme, const std::string &literal, int line) : type(type), lexeme(lexeme), line(line), literal(literal) {}

Token::Token(TokenType type, const std::string &lexeme, const char *literal, int line) : Token(type, lexeme, std::string(literal), line) {}

Token::Token(TokenType type, const std::string &lexeme, const double &literal, int line) : type(type), lexeme(lexeme), line(line), literal(literal) {}

Token::Token(TokenType type, const std::string &lexeme, const bool &literal, int line) : type(type), lexeme(lexeme), line(line), literal(literal) {}

Token::Token(TokenType type, const std::string &lexeme, int line) : type(type), lexeme(lexeme), line(line) {
    this->literal = nullptr;
}

std::string Token::to_string() {
    return "Token: " + tokenTypeToString(type) + " " + lexeme + " " + utils::literalToString(literal) + " " + std::to_string(line);
}

