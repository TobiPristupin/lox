#include <gtest/gtest.h>
#include "../Expr.h"
#include "../Interpreter.h"

class InterpreterTest : public ::testing::Test {
protected:

    Interpreter interpreter;
    LiteralExpr *literalExprTwo;
    LiteralExpr *literalExprFalse;
    GroupingExpr *groupingExpr;
    UnaryExpr *unaryMinus;
    UnaryExpr *unaryBang;

    void SetUp() override {
        literalExprTwo = new LiteralExpr(2.0);
        literalExprFalse = new LiteralExpr(false);
        groupingExpr = new GroupingExpr(literalExprTwo);
        unaryMinus = new UnaryExpr(Token(TokenType::MINUS, "-", 1), literalExprTwo);
        unaryBang = new UnaryExpr(Token(TokenType::BANG, "!", 1), literalExprFalse);
    }

    void TearDown() override {
        delete literalExprTwo;
        delete groupingExpr;
        delete unaryMinus;
        delete unaryBang;
    }

};

TEST_F(InterpreterTest, interpretLiteral){
    EXPECT_EQ(interpreter.interpret(literalExprTwo), literalExprTwo->literal);
}

TEST_F(InterpreterTest, interpretGrouping){
    EXPECT_EQ(interpreter.interpret(groupingExpr), literalExprTwo->literal);
}

TEST_F(InterpreterTest, interpretUnaryMinus){
    double result = std::get<double>(interpreter.interpret(unaryMinus));
    EXPECT_EQ(result, -2.0);
}

TEST_F(InterpreterTest, interpretUnaryBang){
    bool result = std::get<bool>(interpreter.interpret(unaryBang));
    EXPECT_EQ(result, true);
}


