#ifndef JLOX_EXPR_H
#define JLOX_EXPR_H


#include "Token.h"

class BinaryExpr;
class GroupingExpr;
class UnaryExpr;
class LiteralExpr;

class ExprVisitor {
public:
    virtual void visit(const BinaryExpr* binaryExpr) = 0;
    virtual void visit(const GroupingExpr* binaryExpr) = 0;
    virtual void visit(const UnaryExpr* binaryExpr) = 0;
    virtual void visit(const LiteralExpr* binaryExpr) = 0;
};


class Expr {
public:
    virtual void accept(ExprVisitor& visitor) = 0;
};

class BinaryExpr : public Expr {
public:
    Expr* left;
    Expr* right;
    Token* op;

    BinaryExpr (Expr* left, Expr* right, Token* op);
    void accept(ExprVisitor& visitor) override;
};

class GroupingExpr : public Expr {
public:
    Expr* expr;

    GroupingExpr(Expr *expr);
    void accept(ExprVisitor& visitor) override;
};

class UnaryExpr : public Expr {
public:
    Token* op;
    Expr* expr;

    UnaryExpr(Token *op, Expr *expr);
    void accept(ExprVisitor& visitor) override;
};

class LiteralExpr : public Expr {
public:
    lox_literal_t literal;

    LiteralExpr(const lox_literal_t &literal);
    void accept(ExprVisitor& visitor) override;
};


#endif //JLOX_EXPR_H
