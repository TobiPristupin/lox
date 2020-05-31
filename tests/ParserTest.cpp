#include "gtest/gtest.h"
#include "../Scanner.h"
#include "../Parser.h"
#include "../tools/AstPrinter.h"

class ParserTest : public ::testing::Test {
protected:

    void SetUp() override {}

    void TearDown() override {}

    Token eof = Token(TokenType::END_OF_FILE, "", 1);
};

TEST_F(ParserTest, parseNumber){
    Token token(TokenType::NUMBER, "123", 123, 1);
    Parser parser({token, eof});
    LiteralExpr *expr = dynamic_cast<LiteralExpr*>(parser.parse());
    ASSERT_TRUE(expr);
    ASSERT_TRUE(std::holds_alternative<int>(expr->literal));
    EXPECT_EQ(std::get<int>(expr->literal), 123);
}

TEST_F(ParserTest, parseString){
    Token token(TokenType::STRING, "hello", std::string("hello"), 1);
    Parser parser({token, eof});
    LiteralExpr *expr = dynamic_cast<LiteralExpr*>(parser.parse());
    ASSERT_TRUE(expr);
    ASSERT_TRUE(std::holds_alternative<std::string>(expr->literal));
    EXPECT_EQ(std::get<std::string>(expr->literal), "hello");
}

TEST_F(ParserTest, parseBooleans){
    std::vector<Token> tokens = {Token(TokenType::TRUE, "true", true, 1), Token(TokenType::FALSE, "false", false, 1)};
    for (Token &token : tokens){
        Parser parser({token, eof});
        LiteralExpr *expr = dynamic_cast<LiteralExpr*>(parser.parse());
        ASSERT_TRUE(expr);
        ASSERT_TRUE(std::holds_alternative<bool>(expr->literal));
        EXPECT_EQ(std::get<bool>(expr->literal), std::get<bool>(token.literal));
    }
}

TEST_F(ParserTest, parseNull){
    Token token(TokenType::NIL, "nil", 1);
    Parser parser({token, eof});
    LiteralExpr *expr = dynamic_cast<LiteralExpr*>(parser.parse());
    ASSERT_TRUE(expr);
    ASSERT_TRUE(std::holds_alternative<nullptr_t>(expr->literal));
    EXPECT_EQ(std::get<nullptr_t>(expr->literal), nullptr);
}


