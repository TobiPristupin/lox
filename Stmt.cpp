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


VarDeclarationStmt::VarDeclarationStmt(Token &identifier, Expr *expr) : identifier(identifier), expr(expr) {}

void VarDeclarationStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}
