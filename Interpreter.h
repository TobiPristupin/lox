#ifndef JLOX_INTERPRETER_H
#define JLOX_INTERPRETER_H

#include <vector>
#include <stack>
#include "Expr.h"
#include "LoxError.h"
#include "Stmt.h"
#include "Environment.h"

class Interpreter : public ExprVisitor, public StmtVisitor {
public:
    Interpreter();

    void interpret(const std::vector<UniqueStmtPtr> &statements, bool replMode = false);

    void visit(ExpressionStmt *expressionStmt) override;
    void visit(PrintStmt *printStmt) override;
    void visit(VarDeclarationStmt *varDeclarationStmt) override;
    void visit(BlockStmt *blockStmt) override;
    void visit(IfStmt *ifStmt) override;
    void visit(BreakStmt *breakStmt) override;
    void visit(WhileStmt *whileStmt) override;
    void visit(ForStmt *forStmt) override;
    void visit(ContinueStmt *continueStmt) override;
    void visit(FunctionDeclStmt *functionStmt) override;


    LoxObject visit(const BinaryExpr *binaryExpr) override;
    LoxObject visit(const GroupingExpr *GroupingExpr) override;
    LoxObject visit(const UnaryExpr *unaryExpr) override;
    LoxObject visit(const LiteralExpr *literalExpr) override;
    LoxObject visit(const VariableExpr *literalExpr) override;
    LoxObject visit(const AssignmentExpr *assignmentExpr) override;
    LoxObject visit(const OrExpr *orExpr) override;
    LoxObject visit(const AndExpr *andExpr) override;
    LoxObject visit(const FunctionCallExpr *functionCallExpr) override;


private:
    Environment::SharedPtr globalEnv;
    Environment::SharedPtr environment;

    void interpretReplMode(Stmt* stmt);
    LoxObject interpret(Expr* expr);
    void execute(Stmt* pStmt);
    void executeBlock(const std::vector<UniqueStmtPtr> &stmts, Environment::SharedPtr newEnv);
    void loadBuiltinFunctions();
};



#endif //JLOX_INTERPRETER_H
