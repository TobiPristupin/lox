//
// Created by pristu on 4/23/20.
//

#ifndef JLOX_EXPRESSION_H
#define JLOX_EXPRESSION_H

#include "Token.h"

struct Expression {};

struct BinaryExpr : public Expression {
    Expression* left;
    Expression* right;
    Token* op;

    BinaryExpr (Expression* left, Expression* right, Token* op) : left(left), right(right), op(op) {}
};

struct GroupingExpr : public Expression {
    Expression* expr;

    GroupingExpr(Expression* expr) : expr(expr) {}
};

struct UnaryExpr : public Expression {
    Token* op;
    Expression* right;

    UnaryExpr(Token* op, Expression* right) : op(op), right(right) {}
};

struct LiteralExpr : public Expression {
    lox_literal_t* literal;

    LiteralExpr(lox_literal_t* literal) : literal(literal) {}
};


#endif //JLOX_EXPRESSION_H
