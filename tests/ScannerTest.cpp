#include "gtest/gtest.h"
#include "../Runner.h"
#include "../FileReader.h"
#include "../Scanner.h"
#include "../LoxException.h"

class ScannerTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ScannerTest, hasEOF){
    Scanner scanner("");
    std::vector<Token> tokens = scanner.scanTokens();
    EXPECT_EQ(tokens[0].type, TokenType::END_OF_FILE);
}

TEST_F(ScannerTest, scanOneCharTokens){
    std::map<std::string, TokenType> oneCharTokens = {
            {"(", TokenType ::LEFT_PAREN},
            {")", TokenType ::RIGHT_PAREN},
            {"{", TokenType ::LEFT_BRACE},
            {"}", TokenType ::RIGHT_BRACE},
            {",", TokenType ::COMMA},
            {".", TokenType ::DOT},
            {"-", TokenType ::MINUS},
            {"+", TokenType ::PLUS},
            {";", TokenType ::SEMICOLON},
            {"*", TokenType ::STAR},
            {"/", TokenType::SLASH}

    };

    for (auto& kv : oneCharTokens){
        Scanner scanner(kv.first);
        EXPECT_EQ(scanner.scanTokens()[0].type, kv.second);
    }
}

TEST_F(ScannerTest, scanOneOrTwoCharTokens){
    std::map<std::string, TokenType> oneCharTokens = {
            {"!", TokenType ::BANG},
            {"!=", TokenType ::BANG_EQUAL},
            {"=", TokenType ::EQUAL},
            {"==", TokenType ::EQUAL_EQUAL},
            {">", TokenType ::GREATER},
            {">=", TokenType ::GREATER_EQUAL},
            {"<", TokenType ::LESS},
            {"<=", TokenType ::LESS_EQUAL}
    };

    for (auto& kv : oneCharTokens){
        Scanner scanner(kv.first);
        EXPECT_EQ(scanner.scanTokens()[0].type, kv.second);
    }
}

TEST_F(ScannerTest, scanStrings){
    std::vector<std::string> valid = {"\"hello\"", "\"h\"", "\"\"", "\"1\"", "\"sdh1\"", "\"_&#$%\""};
    std::vector<std::string> invalid = {"\"", "\"h", "h\""};
    for (std::string str : valid){
        Scanner scanner(str);
        Token token = scanner.scanTokens()[0];
        EXPECT_EQ(token.type, TokenType::STRING);
        EXPECT_EQ(token.lexeme, str);
    }
    for (std::string str : invalid){
        Scanner scanner(str);
        EXPECT_THROW(scanner.scanTokens(), ScanningException);
    }
}

TEST_F(ScannerTest, scanNumbers){
    std::vector<std::string> valid = {"1", "1243", "1.1", "1.1238", "3476.45"};
    for (std::string str : valid) {
        Scanner scanner(str);
        Token token = scanner.scanTokens()[0];
        EXPECT_EQ(token.type, TokenType::NUMBER);
        EXPECT_EQ(token.lexeme, str);
        if (str.find(".") != std::string::npos){ //contains a decimal
            ASSERT_TRUE(std::holds_alternative<float>(token.literal));
            EXPECT_EQ(std::get<float>(token.literal), std::stof(str));
        } else {
            ASSERT_TRUE(std::holds_alternative<int>(token.literal));
            EXPECT_EQ(std::get<int>(token.literal), std::stoi(str));
        }
    }
}

TEST_F(ScannerTest, scanIdentifier){
    std::vector<std::string> valid = {"h", "hello", "h1", "H", "h_12", "h12", "_h468"};
    for (std::string str : valid){
        Scanner scanner(str);
        Token token = scanner.scanTokens()[0];
        EXPECT_EQ(token.type, TokenType::IDENTIFIER);
        EXPECT_EQ(token.lexeme, str);
    }
}

TEST_F(ScannerTest, scanKeywords){
    std::map<std::string, TokenType> reservedKeywords = {
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
    for (auto& kv : reservedKeywords){
        Scanner scanner(kv.first);
        Token token = scanner.scanTokens()[0];
        EXPECT_EQ(token.type, kv.second);
    }
}

TEST_F(ScannerTest, ignoreComments){
    std::string code = "//this is a comment  \n //second line \n 123 \n //line 4";
    Scanner scanner(code);
    std::vector<Token> tokens = scanner.scanTokens();
    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[0].lexeme, "123");
}

TEST_F(ScannerTest, createLiteralTokens){
    Scanner scanner1("false");
    Token _false = scanner1.scanTokens()[0];
    ASSERT_EQ(_false.type, TokenType::FALSE);
    EXPECT_EQ(std::get<bool>(_false.literal), false);

    Scanner scanner2("true");
    Token _true = scanner2.scanTokens()[0];
    ASSERT_EQ(_true.type, TokenType::TRUE);
    EXPECT_EQ(std::get<bool>(_true.literal), true);

    Scanner scanner3("123");
    Token number = scanner3.scanTokens()[0];
    ASSERT_EQ(number.type, TokenType::NUMBER);
    EXPECT_EQ(std::get<int>(number.literal), 123);

    Scanner scanner4("0.25");
    Token number2 = scanner4.scanTokens()[0];
    ASSERT_EQ(number2.type, TokenType::NUMBER);
    EXPECT_EQ(std::get<float>(number2.literal), 0.25);
}

TEST_F(ScannerTest, lines){
    std::string code = "hello 123 \n hello \n 123";
    Scanner scanner(code);
    std::vector<Token> tokens = scanner.scanTokens();
    EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[0].line, 1);
    EXPECT_EQ(tokens[1].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[1].line, 1);
    EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].line, 2);
    EXPECT_EQ(tokens[3].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[3].line, 3);
}

TEST_F(ScannerTest, general){
    std::string code = "var x = 1; \n if (true) { \n var x = 1+1; \n }";
    Scanner scanner(code);
    std::vector<Token> tokens = scanner.scanTokens();
    EXPECT_EQ(tokens[0].type, TokenType::VAR);
    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].type, TokenType::EQUAL);
    EXPECT_EQ(tokens[3].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[4].type, TokenType::SEMICOLON);

    EXPECT_EQ(tokens[5].type, TokenType::IF);
    EXPECT_EQ(tokens[6].type, TokenType::LEFT_PAREN);
    EXPECT_EQ(tokens[7].type, TokenType::TRUE);
    EXPECT_EQ(tokens[8].type, TokenType::RIGHT_PAREN);
    EXPECT_EQ(tokens[9].type, TokenType::LEFT_BRACE);
    EXPECT_EQ(tokens[10].type, TokenType::VAR);
    EXPECT_EQ(tokens[11].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[12].type, TokenType::EQUAL);
    EXPECT_EQ(tokens[13].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[14].type, TokenType::PLUS);
    EXPECT_EQ(tokens[15].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[16].type, TokenType::SEMICOLON);
    EXPECT_EQ(tokens[17].type, TokenType::RIGHT_BRACE);
}