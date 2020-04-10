#include <optional>
#include "Scanner.h"
#include "TokenType.h"
#include "ErrorLogger.h"

Scanner::Scanner(const std::string &source) {
    this->source = source;
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = next;
        std::optional<Token> nextToken = scanNextToken();
        if (nextToken.has_value()) tokens.emplace_back(*nextToken);
    }

    Token eof(TokenType::END_OF_FILE, "", nullptr, line);
    tokens.emplace_back(eof);
    return tokens;
}

bool Scanner::isAtEnd() {
    return next >= source.length();
}

std::optional<Token> Scanner::scanNextToken() {
    char c = advanceChar();
    switch (c) {
        //whitespace
        case ' ':
        case '\r':
        case '\t':
            return std::nullopt; //ignore whitespace
        case '\n':
            line++;
            return std::nullopt;

            //one character tokens
        case '(':
            return createToken(TokenType::LEFT_PAREN, nullptr);
        case ')':
            return createToken(TokenType::RIGHT_PAREN, nullptr);
        case '{':
            return createToken(TokenType::LEFT_BRACE, nullptr);
        case '}':
            return createToken(TokenType::RIGHT_BRACE, nullptr);
        case ',':
            return createToken(TokenType::COMMA, nullptr);
        case '.':
            return createToken(TokenType::DOT, nullptr);
        case '-':
            return createToken(TokenType::MINUS, nullptr);
        case '+':
            return createToken(TokenType::PLUS, nullptr);
        case ';':
            return createToken(TokenType::SEMICOLON, nullptr);
        case '*':
            return createToken(TokenType::STAR, nullptr);

            //one or two character tokens
        case '!':
            if (nextCharMatches('=')) {
                advanceChar();
                return createToken(TokenType::BANG_EQUAL, nullptr);
            } else {
                return createToken(TokenType::BANG, nullptr);
            }
        case '=':
            if (nextCharMatches('=')) {
                advanceChar();
                return createToken(TokenType::EQUAL_EQUAL, nullptr);
            } else {
                return createToken(TokenType::EQUAL, nullptr);
            }
        case '>':
            if (nextCharMatches('=')) {
                advanceChar();
                return createToken(TokenType::GREATER_EQUAL, nullptr);
            } else {
                return createToken(TokenType::GREATER, nullptr);
            }
        case '<':
            if (nextCharMatches('=')) {
                advanceChar();
                return createToken(TokenType::LESS_EQUAL, nullptr);
            } else {
                return createToken(TokenType::LESS, nullptr);
            }

        default:
            std::string errorMessage = "Unexpected character when scanning : ";
            errorMessage.push_back(c);
            ErrorLogger::error(line, errorMessage);
            return std::nullopt;
    }
}


char Scanner::advanceChar() {
    next++;
    return source[next - 1];
}

bool Scanner::nextCharMatches(char expected) {
    if (isAtEnd()) return false;
    return source[next] == expected;
}

Token Scanner::createToken(TokenType type, std::any literal) {
    return Token(type, source.substr(start, (next - start)), literal, line);
}

