
#include "Token.h"

Token::Token(TokenType type, const std::string &lexeme, const std::string &literal, int line) : type(type), lexeme(lexeme), line(line), literal(literal) {}

Token::Token(TokenType type, const std::string &lexeme, const char *literal, int line) : Token(type, lexeme, std::string(literal), line) {}

Token::Token(TokenType type, const std::string &lexeme, const int &literal, int line) : type(type), lexeme(lexeme), line(line), literal(literal) {}

Token::Token(TokenType type, const std::string &lexeme, const float &literal, int line) : type(type), lexeme(lexeme), line(line), literal(literal) {}

Token::Token(TokenType type, const std::string &lexeme, const bool &literal, int line) : type(type), lexeme(lexeme), line(line), literal(literal) {}

Token::Token(TokenType type, const std::string &lexeme, int line) : type(type), lexeme(lexeme), line(line) {
    this->literal = nullptr;
}

std::string Token::to_string() {
    std::string s = "Token: " + tokenTypeToString(type) + " "  + lexeme;
    if (std::holds_alternative<std::string>(literal)){
        s += " " + std::get<std::string>(literal);
    } else if (std::holds_alternative<int>(literal)){
        s += " " + std::to_string(std::get<int>(literal));
    } else if (std::holds_alternative<float>(literal)){
        s += " " + std::to_string(std::get<float>(literal));
    } else if (std::holds_alternative<bool>(literal)){
        s += " " + std::to_string(std::get<bool>(literal));
    } else if (std::holds_alternative<nullptr_t>(literal)) {
        s += " null";
    }

    s += " " + std::to_string(line);
    return  s;
}

