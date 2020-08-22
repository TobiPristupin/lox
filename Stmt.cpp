#include "Stmt.h"
#include "Expr.h"

Stmt::~Stmt() = default;

ExpressionStmt::ExpressionStmt(UniqueExprPtr expr) : expr(std::move(expr)) {}

void ExpressionStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


PrintStmt::PrintStmt(std::optional<UniqueExprPtr> expr) : expr(std::move(expr)) {}

void PrintStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


VarDeclarationStmt::VarDeclarationStmt(const Token &identifier, std::optional<UniqueExprPtr> expr) : identifier(identifier), expr(std::move(expr)) {}

void VarDeclarationStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}

BlockStmt::BlockStmt(std::vector<UniqueStmtPtr> statements) : statements(std::move(statements)) {}

void BlockStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


IfBranch::IfBranch(UniqueExprPtr condition, UniqueStmtPtr statement) : condition(std::move(condition)), statement(std::move(statement)) {}

IfStmt::IfStmt(IfBranch mainBranch, std::vector<IfBranch> elifBranches, std::optional<UniqueStmtPtr> elseBranch) : mainBranch(std::move(mainBranch)), elifBranches(std::move(elifBranches)), elseBranch(std::move(elseBranch)){}

void IfStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


WhileStmt::WhileStmt(UniqueExprPtr condition, UniqueStmtPtr body) : condition(std::move(condition)), body(std::move(body)) {}

void WhileStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


ForStmt::ForStmt(std::optional<UniqueStmtPtr> initializer, std::optional<UniqueExprPtr> condition, std::optional<UniqueStmtPtr> increment, UniqueStmtPtr body)
: initializer(std::move(initializer)), condition(std::move(condition)), increment(std::move(increment)), body(std::move(body)) {}

void ForStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


BreakStmt::BreakStmt(const Token &keyword) : keyword(keyword) {}

void BreakStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


ContinueStmt::ContinueStmt(const Token &keyword) : keyword(keyword) {}

void ContinueStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


FunctionDeclStmt::FunctionDeclStmt(const Token &name, const std::vector<Token> &params, std::vector<UniqueStmtPtr> body) : name(name), params(params), body(std::move(body)) {}

void FunctionDeclStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}


ReturnStmt::ReturnStmt(const Token &keyword, std::optional<UniqueExprPtr> expr) : keyword(keyword), expr(std::move(expr)) {}

void ReturnStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}

ReturnException::ReturnException(const LoxObject &value) : value(value) {}


ClassDeclStmt::ClassDeclStmt(const Token &identifier, std::vector<std::unique_ptr<FunctionDeclStmt>> methods) :
    identifier(identifier), methods(std::move(methods)) {}

void ClassDeclStmt::accept(StmtVisitor &visitor) {
    visitor.visit(this);
}
