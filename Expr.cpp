#include <iostream>
#include "Expr.h"
#include "Stmt.h"




BinaryExpr::BinaryExpr(UniqueExprPtr left, UniqueExprPtr right, const Token &op) : left(std::move(left)), right(std::move(right)), op(op) {}

LoxObject BinaryExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}

GroupingExpr::GroupingExpr(UniqueExprPtr expr) : expr(std::move(expr)) {}

LoxObject GroupingExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}


UnaryExpr::UnaryExpr(const Token &op, UniqueExprPtr expr) : op(op), expr(std::move(expr)) {}

LoxObject UnaryExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}

LiteralExpr::LiteralExpr(const LoxObject &literal) : literal(literal) {}

LoxObject LiteralExpr::accept(ExprVisitor& visitor) {
    return visitor.visit(this);
}

VariableExpr::VariableExpr(const Token &identifier) : identifier(identifier) {}

LoxObject VariableExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}


AssignmentExpr::AssignmentExpr(const Token &identifier, UniqueExprPtr value) : identifier(identifier), value(std::move(value)) {}

LoxObject AssignmentExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

OrExpr::OrExpr(UniqueExprPtr left, UniqueExprPtr right) : left(std::move(left)), right(std::move(right)) {}

LoxObject OrExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

AndExpr::AndExpr(UniqueExprPtr left, UniqueExprPtr right) : left(std::move(left)), right(std::move(right)) {}

LoxObject AndExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}


FunctionCallExpr::FunctionCallExpr(UniqueExprPtr callee, const Token &closingParen,
                                   std::vector<UniqueExprPtr> arguments) : callee(std::move(callee)), closingParen(closingParen), arguments(std::move(arguments)){}

LoxObject FunctionCallExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

IncrementExpr::IncrementExpr(const Token &identifier, IncrementExpr::Type type) : identifier(identifier), type(type) {}

LoxObject IncrementExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

DecrementExpr::DecrementExpr(const Token &identifier, DecrementExpr::Type type) : identifier(identifier), type(type) {}

LoxObject DecrementExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}


LambdaExpr::LambdaExpr(const std::vector<Token> &params, UniqueExprPtr body) : params(params), body(std::move(body)){}

LoxObject LambdaExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}
