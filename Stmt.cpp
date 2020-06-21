#include "Stmt.h"

Stmt::~Stmt() = default;

ExpressionStmt::ExpressionStmt(Expr *expr) : expr(expr) {}

void ExpressionStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


PrintStmt::PrintStmt(Expr *expr) : expr(expr) {}

void PrintStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


VarStmt::VarStmt(Token &identifier, Expr *expr) : identifier(identifier), expr(expr) {}

void VarStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}
