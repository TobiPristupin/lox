#include "Expr.h"

BinaryExpr::BinaryExpr(Expr *left, Expr *right, Token *op) : left(left), right(right), op(op) {}

void BinaryExpr::accept(ExprVisitor& visitor) {
    visitor.visit(this);
}




GroupingExpr::GroupingExpr(Expr *expr) : expr(expr) {}

void GroupingExpr::accept(ExprVisitor& visitor) {
    visitor.visit(this);
}



UnaryExpr::UnaryExpr(Token *op, Expr *expr) : op(op), expr(expr) {}

void UnaryExpr::accept(ExprVisitor& visitor) {
    visitor.visit(this);
}




LiteralExpr::LiteralExpr(const lox_literal_t &literal) : literal(literal) {}

void LiteralExpr::accept(ExprVisitor& visitor) {
    visitor.visit(this);
}
