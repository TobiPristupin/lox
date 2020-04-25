#include <optional>
#include <iostream>
#include <algorithm>
#include "Scanner.h"
#include "TokenType.h"
#include "LoxException.h"

std::map<std::string, TokenType> Scanner::reservedKeywords = {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"fun", TokenType::FUN},
        {"for", TokenType::FOR},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE}
};

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
    if (isAtEnd()) {
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
            nextLine();
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
            if (currentCharMatches('/')) {
                while (!isAtEnd() && peek() != '\n') advance();
                return std::nullopt;
            } else {
                return createToken(TokenType::SLASH, nullptr);
            }

            //strings
        case '"':
            return scanString();

        default:
            if (isdigit(c)) {
                return scanNumber();
            } else if (isalpha(c) or c == '_') {
                return scanIdentifier();
            }

            //unexpected character
            std::string errorMessage = "Unexpected character when scanning : ";
            errorMessage.push_back(c);
            throw ScanningException(errorMessage, line, pos_in_line);
    }
}

std::optional<Token> Scanner::scanIdentifier() {
    while (!isAtEnd() && !isWhitespace(peek())) {
        if (!validForIdentifier(peek())) {
            throw ScanningException("Invalid identifier", line, pos_in_line);
        }
        advance();
    }

    std::string identifier = source.substr(start, (current - start));
    if (reservedKeywords.count(identifier) > 0){
        if (identifier == "false"){
            return createToken(TokenType::FALSE, false);
        } else if (identifier == "true"){
            return createToken(TokenType::TRUE, true);
        }

        return createToken(reservedKeywords[identifier], nullptr);
    }
    return createToken(IDENTIFIER, nullptr);
}

std::optional<Token> Scanner::scanNumber() {
    while (!isAtEnd() && !isWhitespace(peek())){
        if (!isdigit(peek()) && peek() != '.'){
            throw ScanningException("Invalid number literal", line, pos_in_line);
        }
        advance();
    }

    std::string number = source.substr(start, (current - start));
    int decimal = std::count(number.begin(), number.end(), '.');
    if (decimal > 1) { //can't have a number with two decimals like 2.1.3
        throw ScanningException("Invalid number literal", line, pos_in_line);
    }

    if (decimal == 1){
        return createToken(NUMBER, std::stof(number));
    }

    return createToken(NUMBER, std::stoi(number));
}

std::optional<Token> Scanner::scanString() {
    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\n') throw ScanningException("Unterminated string", line, pos_in_line);
        advance();
    }


    if (isAtEnd()) {
        throw ScanningException("Unterminated string", line, pos_in_line);
    }

    advance(); //advance closing "
    std::string s = source.substr(start + 1, (current - start - 1 - 1));//+1 and -1 to remove the quotes from each end
    return createToken(STRING, s);
}

bool Scanner::validForIdentifier(char c) {
    return isalpha(c) || isdigit(c) || c == '_';
}

char Scanner::peek() {
    return source[current];
}

void Scanner::advance() {
    current++;
    pos_in_line++;
}

bool Scanner::currentCharMatches(char expected) {
    if (isAtEnd()) return false;
    //check at position current and not current + 1 because advance should have been called before this method,
    //so the peek char to evaluate is at current and not current + 1
    return source[current] == expected;
}

bool Scanner::isWhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

Token Scanner::createToken(TokenType type, const lox_literal_t &literal) {
    return Token(type, source.substr(start, (current - start)), literal, line);
}

void Scanner::nextLine() {
    line++;
    pos_in_line = 1;
}

