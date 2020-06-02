#include "gtest/gtest.h"
#include "../Parser.h"

class ParserTest : public ::testing::Test {
protected:

    void SetUp() override {}

    void TearDown() override {}

    Token eof = Token(TokenType::END_OF_FILE, "", 1);
    Token number = Token(TokenType::NUMBER, "123", 2, 1);
    Token string = Token(TokenType::STRING, "hello", std::string("hello"), 1);
    Token trueToken = Token(TokenType::TRUE, "true", true, 1);
    Token falseToken = Token(TokenType::FALSE, "false", false, 1);
    Token nil = Token(TokenType::NIL, "nil", 1);
    Token plus = Token(TokenType::PLUS, "+", 1), minus = Token(TokenType::MINUS, "-", 1);
    Token leftParen = Token(TokenType::LEFT_PAREN, "(", 1), rightParen = Token(TokenType::RIGHT_PAREN, ")", 1);
    Token star = Token(TokenType::STAR, "*", 1);
    Token greater = Token(TokenType::GREATER, ">", 1);
    Token equalequal = Token(TokenType::EQUAL_EQUAL, "==", 1);
    Token bang = Token(TokenType::BANG, "!", 1);
};

TEST_F(ParserTest, parseNumber){
    Parser parser({number, eof});
    LiteralExpr *expr = dynamic_cast<LiteralExpr*>(parser.parse());
    ASSERT_TRUE(expr);
    ASSERT_TRUE(std::holds_alternative<int>(expr->literal));
    EXPECT_EQ(std::get<int>(expr->literal), std::get<int>(number.literal));
}

TEST_F(ParserTest, parseString){
    Parser parser({string, eof});
    LiteralExpr *expr = dynamic_cast<LiteralExpr*>(parser.parse());
    ASSERT_TRUE(expr);
    ASSERT_TRUE(std::holds_alternative<std::string>(expr->literal));
    EXPECT_EQ(std::get<std::string>(expr->literal), "hello");
}

TEST_F(ParserTest, parseBooleans){
    std::vector<Token> tokens = {trueToken, falseToken};
    for (Token &token : tokens){
        Parser parser({token, eof});
        LiteralExpr *expr = dynamic_cast<LiteralExpr*>(parser.parse());
        ASSERT_TRUE(expr);
        ASSERT_TRUE(std::holds_alternative<bool>(expr->literal));
        EXPECT_EQ(std::get<bool>(expr->literal), std::get<bool>(token.literal));
    }
}

TEST_F(ParserTest, parseNull){
    Parser parser({nil, eof});
    LiteralExpr *expr = dynamic_cast<LiteralExpr*>(parser.parse());
    ASSERT_TRUE(expr);
    ASSERT_TRUE(std::holds_alternative<nullptr_t>(expr->literal));
    EXPECT_EQ(std::get<nullptr_t>(expr->literal), nullptr);
}

TEST_F(ParserTest, parseGrouping){
    Parser parser({leftParen, string, rightParen, eof});
    GroupingExpr *expr = dynamic_cast<GroupingExpr*>(parser.parse());
    ASSERT_TRUE(expr);
    LiteralExpr *literalExpr = dynamic_cast<LiteralExpr*>(expr->expr);
    ASSERT_TRUE(literalExpr);
    EXPECT_EQ(std::get<std::string>(literalExpr->literal), std::get<std::string>(string.literal));
}

TEST_F(ParserTest, parseBinaryExpressions){
    std::vector<Token> tokens = {number, plus, number, eof};
    Parser parse(tokens);
    Expr* expr = parse.parse();
    BinaryExpr* binary = dynamic_cast<BinaryExpr*>(expr);
    ASSERT_TRUE(binary);
    EXPECT_EQ(binary->op.type, plus.type);
    LiteralExpr* left = dynamic_cast<LiteralExpr*>(binary->left);
    LiteralExpr* right = dynamic_cast<LiteralExpr*>(binary->right);
    ASSERT_TRUE(left);
    ASSERT_TRUE(right);
    EXPECT_EQ(std::get<int>(left->literal),std::get<int>(number.literal));
    EXPECT_EQ(std::get<int>(right->literal),std::get<int>(number.literal));
}

TEST_F(ParserTest, obeyPrecedence){
    // -2*2 + 2*2 > 2  == true     should be parsed like this ((((-2) * 2) + 2) > 2)  == true
    Parser parser({minus, number, star, number, plus, number, greater, number, equalequal, trueToken, eof});
    Expr *expr = parser.parse();

    BinaryExpr* binaryEqual = dynamic_cast<BinaryExpr*>(expr);
    ASSERT_TRUE(binaryEqual);
    EXPECT_EQ(binaryEqual->op.type, equalequal.type);

    LiteralExpr* literalTrue = dynamic_cast<LiteralExpr*>(binaryEqual->right);
    ASSERT_TRUE(literalTrue);
    EXPECT_EQ(std::get<bool>(literalTrue->literal), true);

    BinaryExpr* binaryGreater = dynamic_cast<BinaryExpr*>(binaryEqual->left);
    ASSERT_TRUE(binaryGreater);
    EXPECT_EQ(binaryGreater->op.type, greater.type);

    LiteralExpr* binaryGreaterRight = dynamic_cast<LiteralExpr*>(binaryGreater->right);
    ASSERT_TRUE(binaryGreaterRight);
    EXPECT_EQ(std::get<int>(binaryGreaterRight->literal), 2);

    BinaryExpr* binaryPlus = dynamic_cast<BinaryExpr*>(binaryGreater->left);
    ASSERT_TRUE(binaryPlus);
    EXPECT_EQ(binaryPlus->op.type, plus.type);

    LiteralExpr* binaryPlusRight = dynamic_cast<LiteralExpr*>(binaryPlus->right);
    ASSERT_TRUE(binaryPlusRight);
    EXPECT_EQ(std::get<int>(binaryPlusRight->literal), 2);

    BinaryExpr* binaryMult = dynamic_cast<BinaryExpr*>(binaryPlus->left);
    ASSERT_TRUE(binaryMult);
    EXPECT_EQ(binaryMult->op.type, star.type);

    UnaryExpr* negative2 = dynamic_cast<UnaryExpr*>(binaryMult->left);
    ASSERT_TRUE(negative2);
    EXPECT_EQ(negative2->op.type, minus.type);
}

TEST_F(ParserTest, obeyParenthesis){
    //(2+2) * 2
    Parser parser({leftParen, number, plus, number, rightParen, star, number, eof});
    Expr* expr = parser.parse();
    BinaryExpr* mult = dynamic_cast<BinaryExpr*>(expr);
    ASSERT_TRUE(mult);
    EXPECT_EQ(mult->op.type, star.type);
}

TEST_F(ParserTest, obeyAssociativityMult){
    //2 * 2 * 3 should be parsed as (2*2)*3
    Token three(TokenType::NUMBER, "3", 3, 1);
    Parser parser({number, star, number, star, three});
    Expr *expr = parser.parse();
    BinaryExpr *binary = dynamic_cast<BinaryExpr*>(expr);
    ASSERT_TRUE(binary);
    EXPECT_EQ(binary->op.type, star.type);
    LiteralExpr* right = dynamic_cast<LiteralExpr*>(binary->right);
    ASSERT_TRUE(right);
    EXPECT_EQ(std::get<int>(right->literal), 3);
}

TEST_F(ParserTest, obeyAssociativityAddition){
    //2 + 2 + 3 should be parsed as (2+2)+3
    Token three(TokenType::NUMBER, "3", 3, 1);
    Parser parser({number, plus, number, plus, three});
    Expr *expr = parser.parse();
    BinaryExpr *binary = dynamic_cast<BinaryExpr*>(expr);
    ASSERT_TRUE(binary);
    EXPECT_EQ(binary->op.type, plus.type);
    LiteralExpr* right = dynamic_cast<LiteralExpr*>(binary->right);
    ASSERT_TRUE(right);
    EXPECT_EQ(std::get<int>(right->literal), 3);
}

TEST_F(ParserTest, obeyAssociativityComparison){
    //2 > 2 > 3 should be parsed as (2>2)>3
    Token three(TokenType::NUMBER, "3", 3, 1);
    Parser parser({number, greater, number, greater, three});
    Expr *expr = parser.parse();
    BinaryExpr *binary = dynamic_cast<BinaryExpr*>(expr);
    ASSERT_TRUE(binary);
    EXPECT_EQ(binary->op.type, greater.type);
    LiteralExpr* right = dynamic_cast<LiteralExpr*>(binary->right);
    ASSERT_TRUE(right);
    EXPECT_EQ(std::get<int>(right->literal), 3);
}

TEST_F(ParserTest, obeyAssociativityEquality){
    //2 == 2 == 3 should be parsed as (2==2)==3
    Token three(TokenType::NUMBER, "3", 3, 1);
    Parser parser({number, equalequal, number, equalequal, three});
    Expr *expr = parser.parse();
    BinaryExpr *binary = dynamic_cast<BinaryExpr*>(expr);
    ASSERT_TRUE(binary);
    EXPECT_EQ(binary->op.type, equalequal.type);
    LiteralExpr* right = dynamic_cast<LiteralExpr*>(binary->right);
    ASSERT_TRUE(right);
    EXPECT_EQ(std::get<int>(right->literal), 3);
}




