#include <optional>
#include <iostream>
#include "Scanner.h"
#include "TokenType.h"
#include "ErrorLogger.h"

Scanner::Scanner(const std::string &source) {
    this->source = source;
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        std::optional<Token> nextToken = scanNextToken();
        if (nextToken.has_value()) tokens.emplace_back(*nextToken);
    }

    Token eof(TokenType::END_OF_FILE, "", nullptr, line);
    tokens.emplace_back(eof);
    return tokens;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

std::optional<Token> Scanner::scanNextToken() {
    if (isAtEnd()){
        return std::nullopt;
    }

    char c = peek();
    advance();
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
            if (currentCharMatches('=')) {
                advance();
                return createToken(TokenType::BANG_EQUAL, nullptr);
            } else {
                return createToken(TokenType::BANG, nullptr);
            }
        case '=':
            if (currentCharMatches('=')) {
                advance();
                return createToken(TokenType::EQUAL_EQUAL, nullptr);
            } else {
                return createToken(TokenType::EQUAL, nullptr);
            }
        case '>':
            if (currentCharMatches('=')) {
                advance();
                return createToken(TokenType::GREATER_EQUAL, nullptr);
            } else {
                return createToken(TokenType::GREATER, nullptr);
            }
        case '<':
            if (currentCharMatches('=')) {
                advance();
                return createToken(TokenType::LESS_EQUAL, nullptr);
            } else {
                return createToken(TokenType::LESS, nullptr);
            }
        case '/':
            if (currentCharMatches('/')){
                while (!isAtEnd() && peek() != '\n') advance();
                return std::nullopt;
            } else {
                return createToken(TokenType::SLASH, nullptr);
            }

            //strings
        case '"': {
            while (!isAtEnd() && peek() != '"') {
                if (peek() == '\n') line++; //support for multi-line strings
                advance();
            }

            if (isAtEnd()) {
                ErrorLogger::error(line, "Unterminated string");
                return std::nullopt;
            }

            advance(); //consume closing "
            std::string s = source.substr(start + 1, (current - start - 2));//+1 and -1 to remove the quotes from each end
            return createToken(TokenType::STRING, s);
        }

        default:
            std::string errorMessage = "Unexpected character when scanning : ";
            errorMessage.push_back(c);
            ErrorLogger::error(line, errorMessage);
            return std::nullopt;
    }
}

char Scanner::peek(){
    return source[current];
}

void Scanner::advance() {
    current++;
}

bool Scanner::currentCharMatches(char expected) {
    if (isAtEnd()) return false;
    //check at position current and not current + 1 because advance should have been called before this method,
    //so the next char to evaluate is at current and not current + 1
    return source[current] == expected;
}

Token Scanner::createToken(TokenType type, const std::variant<int, float, std::string, std::nullptr_t>& literal) {
    return Token(type, source.substr(start, (current - start)), literal, line);
}

