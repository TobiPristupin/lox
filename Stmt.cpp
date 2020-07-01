#include "Stmt.h"

Stmt::~Stmt() = default;

ExpressionStmt::ExpressionStmt(UniqueExprPtr expr) : expr(std::move(expr)) {}

void ExpressionStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


PrintStmt::PrintStmt(UniqueExprPtr expr) : expr(std::move(expr)) {}

void PrintStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


VarStmt::VarStmt(const Token &identifier, UniqueExprPtr expr) : identifier(identifier), expr(std::move(expr)) {}

void VarStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}

BlockStmt::BlockStmt(std::vector<UniqueStmtPtr> statements) : statements(std::move(statements)) {}

void BlockStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}
