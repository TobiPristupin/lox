#ifndef JLOX_RESOLVER_H
#define JLOX_RESOLVER_H


#include <stack>
#include <unordered_map>
#include "Stmt.h"
#include "Expr.h"

class Resolver : public ExprVisitor, StmtVisitor {

public:
    std::unordered_map<const Expr*, int> resolve(const std::vector<UniqueStmtPtr> &stmts);

    LoxObject visit(const BinaryExpr *binaryExpr) override;
    LoxObject visit(const GroupingExpr *groupingExpr) override;
    LoxObject visit(const UnaryExpr *unaryExpr) override;
    LoxObject visit(const LiteralExpr *literalExpr) override;
    LoxObject visit(const VariableExpr *variableExpr) override;
    LoxObject visit(const AssignmentExpr *assignmentExpr) override;
    LoxObject visit(const OrExpr *orExpr) override;
    LoxObject visit(const AndExpr *andExpr) override;
    LoxObject visit(const FunctionCallExpr *functionCallExpr) override;
    LoxObject visit(const IncrementExpr *incrementExpr) override;
    LoxObject visit(const DecrementExpr *decrementExpr) override;
    LoxObject visit(const LambdaExpr *lambdaExpr) override;

    void visit(const ExpressionStmt *expressionStmt) override;
    void visit(const PrintStmt *printStmt) override;
    void visit(const VarDeclarationStmt *varStmt) override;
    void visit(const BlockStmt *blockStmt) override;
    void visit(const IfStmt *ifStmt) override;
    void visit(const WhileStmt *whileStmt) override;
    void visit(const BreakStmt *breakStmt) override;
    void visit(const ContinueStmt *continueStmt) override;
    void visit(const ForStmt *forStmt) override;
    void visit(const FunctionDeclStmt *functionStmt) override;
    void visit(const ReturnStmt *returnStmt) override;

private:
    std::unordered_map<const Expr*, int> distances;

    //the string is the variable name, the boolean is true if the variable has been initialized, false otherwise
    using Scope = std::unordered_map<std::string, bool>;
    std::vector<Scope> scopes;

    void resolve(Stmt* stmt);
    void resolve(Expr* expr);
    void resolveLocal(const Expr* expr, const Token &name);
    void resolveFunction(const FunctionDeclStmt *functionStmt);
    void beginScope();
    void endScope();
    void declare(const Token &name);
    void define(const Token &name);

};


#endif //JLOX_RESOLVER_H