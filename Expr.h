#ifndef JLOX_EXPR_H
#define JLOX_EXPR_H

#include <memory>
#include "Token.h"


class Expr;
class BinaryExpr;
class GroupingExpr;
class UnaryExpr;
class LiteralExpr;
class VariableExpr;
class AssignmentExpr;

using UniqueExprPtr = std::unique_ptr<Expr>;

class ExprVisitor {
public:
    virtual lox_literal_t visit(const BinaryExpr* binaryExpr) = 0;
    virtual lox_literal_t visit(const GroupingExpr* groupingExpr) = 0;
    virtual lox_literal_t visit(const UnaryExpr* unaryExpr) = 0;
    virtual lox_literal_t visit(const LiteralExpr* literalExpr) = 0;
    virtual lox_literal_t visit(const VariableExpr* variableExpr) = 0;
    virtual lox_literal_t visit(const AssignmentExpr* assignmentExpr) = 0;
};


class Expr {
public:
    virtual ~Expr() = 0;
    virtual lox_literal_t accept(ExprVisitor& visitor) = 0;
};

class BinaryExpr : public Expr {
public:
    UniqueExprPtr left;
    UniqueExprPtr right;
    Token op;

    BinaryExpr (UniqueExprPtr left, UniqueExprPtr right, const Token &op);
    lox_literal_t accept(ExprVisitor& visitor) override;
};

class GroupingExpr : public Expr {
public:
    UniqueExprPtr expr;

    GroupingExpr(UniqueExprPtr expr);
    lox_literal_t accept(ExprVisitor& visitor) override;
};

class UnaryExpr : public Expr {
public:
    Token op;
    UniqueExprPtr expr;

    UnaryExpr(const Token &op, UniqueExprPtr expr);
    lox_literal_t accept(ExprVisitor& visitor) override;
};

class LiteralExpr : public Expr {
public:
    lox_literal_t literal;

    LiteralExpr(const lox_literal_t &literal);
    lox_literal_t accept(ExprVisitor& visitor) override;

};


class VariableExpr : public Expr {
public:
    Token identifier;

    VariableExpr(const Token &identifier);
    lox_literal_t accept(ExprVisitor& visitor) override;

};

class AssignmentExpr : public Expr {
public:
    Token identifier;
    UniqueExprPtr value;

    AssignmentExpr(const Token &identifier, UniqueExprPtr value);
    lox_literal_t accept(ExprVisitor &visitor) override;
};


#endif //JLOX_EXPR_H
