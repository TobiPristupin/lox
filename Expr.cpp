#include "Expr.h"


Expr::~Expr() = default;

BinaryExpr::BinaryExpr(Expr *left, Expr *right, Token op) : left(left), right(right), op(op) {}

lox_literal_t BinaryExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}

GroupingExpr::GroupingExpr(Expr *expr) : expr(expr) {}

lox_literal_t GroupingExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}


UnaryExpr::UnaryExpr(Token op, Expr *expr) : op(op), expr(expr) {}

lox_literal_t UnaryExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}

LiteralExpr::LiteralExpr(const lox_literal_t &literal) : literal(literal) {}

lox_literal_t LiteralExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}

