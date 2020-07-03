#include <iostream>
#include "Expr.h"


Expr::~Expr() = default;

BinaryExpr::BinaryExpr(UniqueExprPtr left, UniqueExprPtr right, const Token &op) : left(std::move(left)), right(std::move(right)), op(op) {}

lox_literal_t BinaryExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}

GroupingExpr::GroupingExpr(UniqueExprPtr expr) : expr(std::move(expr)) {}

lox_literal_t GroupingExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}


UnaryExpr::UnaryExpr(const Token &op, UniqueExprPtr expr) : op(op), expr(std::move(expr)) {}

lox_literal_t UnaryExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}

LiteralExpr::LiteralExpr(const lox_literal_t &literal) : literal(literal) {}

lox_literal_t LiteralExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}


VariableExpr::VariableExpr(const Token &identifier) : identifier(identifier) {}

lox_literal_t VariableExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}


AssignmentExpr::AssignmentExpr(const Token &identifier, UniqueExprPtr value) : identifier(identifier), value(std::move(value)) {}

lox_literal_t AssignmentExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

OrExpr::OrExpr(UniqueExprPtr left, UniqueExprPtr right) : left(std::move(left)), right(std::move(right)) {}

lox_literal_t OrExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

AndExpr::AndExpr(UniqueExprPtr left, UniqueExprPtr right) : left(std::move(left)), right(std::move(right)) {}

lox_literal_t AndExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

