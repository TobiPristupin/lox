#ifndef JLOX_EXPR_H
#define JLOX_EXPR_H

#include "Token.h"

class BinaryExpr;
class GroupingExpr;
class UnaryExpr;
class LiteralExpr;

class ExprVisitor {
public:
    virtual lox_literal_t visit(const BinaryExpr* binaryExpr) = 0;
    virtual lox_literal_t visit(const GroupingExpr* groupingExpr) = 0;
    virtual lox_literal_t visit(const UnaryExpr* unaryExpr) = 0;
    virtual lox_literal_t visit(const LiteralExpr* literalExpr) = 0;
};


class Expr {
public:
    virtual ~Expr() = 0;
    virtual lox_literal_t accept(ExprVisitor& visitor) = 0;
};

class BinaryExpr : public Expr {
public:
    Expr* left;
    Expr* right;
    Token op;

    BinaryExpr (Expr* left, Expr* right, Token op);
    lox_literal_t accept(ExprVisitor& visitor) override;
};

class GroupingExpr : public Expr {
public:
    Expr* expr;

    GroupingExpr(Expr *expr);
    lox_literal_t accept(ExprVisitor& visitor) override;
};

class UnaryExpr : public Expr {
public:
    Token op;
    Expr* expr;

    UnaryExpr(Token op, Expr *expr);
    lox_literal_t accept(ExprVisitor& visitor) override;
};

class LiteralExpr : public Expr {
public:
    lox_literal_t literal;

    LiteralExpr(const lox_literal_t &literal);
    lox_literal_t accept(ExprVisitor& visitor) override;

};


#endif //JLOX_EXPR_H
