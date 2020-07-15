
#include "Token.h"

Token::Token(TokenType type, const std::string &lexeme, int line) : type(type), lexeme(lexeme), line(line) {}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << std::string("Token: ") <<  tokenTypeToString(token.type) << std::string(" ")  << token.lexeme  << std::string(" ") << std::to_string(token.line);
    return os;
}

