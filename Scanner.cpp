#include <optional>
#include <iostream>
#include <algorithm>
#include "Scanner.h"
#include "TokenType.h"
#include "LoxError.h"

std::map<std::string, TokenType> Scanner::reservedKeywords = {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"elif", TokenType::ELIF},
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
        {"while", TokenType::WHILE},
        {"break", TokenType::BREAK},
        {"continue", TokenType::CONTINUE}
};

Scanner::Scanner(const std::string &source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        std::optional<Token> nextToken = scanNextToken();
        if (nextToken.has_value()) tokens.emplace_back(*nextToken);
    }

    Token eof(TokenType::END_OF_FILE, "", line);
    tokens.push_back(eof);
    return tokens;
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
            return createToken(TokenType::LEFT_PAREN);
        case ')':
            return createToken(TokenType::RIGHT_PAREN);
        case '{':
            return createToken(TokenType::LEFT_BRACE);
        case '}':
            return createToken(TokenType::RIGHT_BRACE);
        case ',':
            return createToken(TokenType::COMMA);
        case '.':
            return createToken(TokenType::DOT);
        case '-':
            return createToken(TokenType::MINUS);
        case '+':
            return createToken(TokenType::PLUS);
        case ';':
            return createToken(TokenType::SEMICOLON);
        case '*':
            return createToken(TokenType::STAR);

            //one or two character tokens
        case '!':
            if (currentCharMatches('=')) {
                advance();
                return createToken(TokenType::BANG_EQUAL);
            } else {
                return createToken(TokenType::BANG);
            }
        case '=':
            if (currentCharMatches('=')) {
                advance();
                return createToken(TokenType::EQUAL_EQUAL);
            } else {
                return createToken(TokenType::EQUAL);
            }
        case '>':
            if (currentCharMatches('=')) {
                advance();
                return createToken(TokenType::GREATER_EQUAL);
            } else {
                return createToken(TokenType::GREATER);
            }
        case '<':
            if (currentCharMatches('=')) {
                advance();
                return createToken(TokenType::LESS_EQUAL);
            } else {
                return createToken(TokenType::LESS);
            }
        case '/':
            if (currentCharMatches('/')) {
                while (!isAtEnd() && peek() != '\n') advance();
                return std::nullopt;
            } else {
                return createToken(TokenType::SLASH);
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
            throw LoxScanningError(errorMessage, line, pos_in_line);
    }
}

std::optional<Token> Scanner::scanIdentifier() {
    while (!isAtEnd() && validForIdentifier(peek())){
        advance();
    }

    std::string identifier = source.substr(start, (current - start));
    if (reservedKeywords.count(identifier) > 0){
        if (identifier == "false"){
            return createToken(TokenType::FALSE);
        } else if (identifier == "true"){
            return createToken(TokenType::TRUE);
        }

        return createToken(reservedKeywords[identifier]);
    }
    return createToken(IDENTIFIER);
}

std::optional<Token> Scanner::scanNumber() {
    while (!isAtEnd() && isdigit(peek())){
        advance();
    }

    if (peek() == '.'){
        advance();
        while (!isAtEnd() && isdigit(peek())){
            advance();
        }
    }

    std::string number = source.substr(start, (current - start));
    int decimal = std::count(number.begin(), number.end(), '.');

    if (decimal == 1){
        return createToken(NUMBER);
    }

    return createToken(NUMBER);
}

std::optional<Token> Scanner::scanString() {
    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\n') throw LoxScanningError("Unterminated string", line, pos_in_line);
        advance();
    }


    if (isAtEnd()) {
        throw LoxScanningError("Unterminated string", line, pos_in_line);
    }

    advance(); //advance closing "
    return createStringToken();
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

Token Scanner::createToken(TokenType type) {
    return Token(type, source.substr(start, (current - start)), line);
}

void Scanner::nextLine() {
    line++;
    pos_in_line = 1;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

Token Scanner::createStringToken() {
    return Token(TokenType::STRING, source.substr(start + 1, (current - start - 1 - 1)), line);
    //The +1 and -1 is to remove the quotes
}




