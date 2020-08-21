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


CallExpr::CallExpr(UniqueExprPtr callee, const Token &closingParen,
                   std::vector<UniqueExprPtr> arguments) : callee(std::move(callee)), closingParen(closingParen), arguments(std::move(arguments)){}

LoxObject CallExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

IncrementExpr::IncrementExpr(std::unique_ptr<VariableExpr> variable, IncrementExpr::Type type) : variable(std::move(variable)), type(type) {}

LoxObject IncrementExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

DecrementExpr::DecrementExpr(std::unique_ptr<VariableExpr> variable, DecrementExpr::Type type) : variable(std::move(variable)), type(type) {}

LoxObject DecrementExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}


LambdaExpr::LambdaExpr(const std::vector<Token> &params, UniqueExprPtr body) : params(params), body(std::move(body)){}

LoxObject LambdaExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

GetExpr::GetExpr(UniqueExprPtr expr, const Token &identifier) : expr(std::move(expr)), identifier(identifier) {}

LoxObject GetExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}

SetExpr::SetExpr(UniqueExprPtr object, const Token &identifier, UniqueExprPtr value) : object(std::move(object)),
    identifier(identifier), value(std::move(value)) {}

LoxObject SetExpr::accept(ExprVisitor &visitor) {
    return visitor.visit(this);
}
