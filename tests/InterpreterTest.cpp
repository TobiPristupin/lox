#include <gtest/gtest.h>
#include "../Expr.h"
#include "../Interpreter.h"

class InterpreterTest : public ::testing::Test {
protected:

    Interpreter interpreter;
    LiteralExpr *literalExprNumber2, *literalExprNumber3, *literalExprFalse, *literaExprStringHello, *literalExprStringAbc;
    GroupingExpr *groupingExpr;
    UnaryExpr *unaryMinus;
    UnaryExpr *unaryBang;

    void SetUp() override {
        literalExprNumber2 = new LiteralExpr(2.0);
        literalExprNumber3 = new LiteralExpr(3.0);
        literalExprFalse = new LiteralExpr(false);
        literaExprStringHello = new LiteralExpr(std::string("Hello"));
        literalExprStringAbc = new LiteralExpr(std::string("Abc"));
        groupingExpr = new GroupingExpr(literalExprNumber2);
        unaryMinus = new UnaryExpr(Token(TokenType::MINUS, "-", 1), literalExprNumber2);
        unaryBang = new UnaryExpr(Token(TokenType::BANG, "!", 1), literalExprFalse);
    }

    void TearDown() override {
        delete literalExprNumber2;
        delete literalExprNumber3;
        delete literalExprFalse;
        delete literaExprStringHello;
        delete literalExprStringAbc;
        delete groupingExpr;
        delete unaryMinus;
        delete unaryBang;
    }

};

TEST_F(InterpreterTest, interpretLiteral){
    EXPECT_EQ(interpreter.interpret(literalExprNumber2), literalExprNumber2->literal);
}

TEST_F(InterpreterTest, interpretGrouping){
    EXPECT_EQ(interpreter.interpret(groupingExpr), literalExprNumber2->literal);
}

TEST_F(InterpreterTest, interpretUnaryMinus){
    double result = std::get<double>(interpreter.interpret(unaryMinus));
    EXPECT_EQ(result, -2.0);
}

TEST_F(InterpreterTest, interpretUnaryBang){
    bool result = std::get<bool>(interpreter.interpret(unaryBang));
    EXPECT_EQ(result, true);
}

TEST_F(InterpreterTest, interpretBinaryExpr){
    BinaryExpr *minus = new BinaryExpr(literalExprNumber2, literalExprNumber2, Token(TokenType::MINUS, "-", 1));
    EXPECT_EQ(std::get<double>(interpreter.interpret(minus)), 0);
    delete minus;

    BinaryExpr *plusNumbers = new BinaryExpr(literalExprNumber2, literalExprNumber2, Token(TokenType::PLUS, "+", 1));
    EXPECT_EQ(std::get<double>(interpreter.interpret(plusNumbers)), 4);
    delete plusNumbers;

    BinaryExpr *plusStrings = new BinaryExpr(literaExprStringHello, literaExprStringHello, Token(TokenType::PLUS, "+", 1));
    EXPECT_EQ(std::get<std::string>(interpreter.interpret(plusNumbers)), "HelloHello");
    delete plusStrings;

    BinaryExpr *greaterNumbers = new BinaryExpr(literalExprNumber3, literalExprNumber2, Token(TokenType::GREATER, ">", 1));
    EXPECT_EQ(std::get<bool>(interpreter.interpret(greaterNumbers)), true);
    delete greaterNumbers;

    BinaryExpr *greaterStrings = new BinaryExpr(literalExprStringAbc, literaExprStringHello, Token(TokenType::GREATER, ">", 1));
    EXPECT_EQ(std::get<bool>(interpreter.interpret(greaterStrings)), false);
    delete greaterStrings;

    BinaryExpr *equalNumbers = new BinaryExpr(literalExprNumber2, literalExprNumber2, Token(TokenType::EQUAL_EQUAL, "==", 1));
    EXPECT_EQ(std::get<bool>(interpreter.interpret(equalNumbers)), true);
    delete equalNumbers;
}


