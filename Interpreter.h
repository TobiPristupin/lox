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
    Environment::SharedPtr globalEnv;
    Environment::SharedPtr environment;

    Interpreter();

    void interpret(const std::vector<UniqueStmtPtr> &statements, bool replMode = false);

    void visit(const ExpressionStmt *expressionStmt) override;
    void visit(const PrintStmt *printStmt) override;
    void visit(const VarDeclarationStmt *varDeclarationStmt) override;
    void visit(const BlockStmt *blockStmt) override;
    void visit(const IfStmt *ifStmt) override;
    void visit(const BreakStmt *breakStmt) override;
    void visit(const WhileStmt *whileStmt) override;
    void visit(const ForStmt *forStmt) override;
    void visit(const ContinueStmt *continueStmt) override;
    void visit(const FunctionDeclStmt *functionStmt) override;
    void visit(const ReturnStmt *returnStmt) override;


    LoxObject visit(const BinaryExpr *binaryExpr) override;
    LoxObject visit(const GroupingExpr *GroupingExpr) override;
    LoxObject visit(const UnaryExpr *unaryExpr) override;
    LoxObject visit(const LiteralExpr *literalExpr) override;
    LoxObject visit(const VariableExpr *literalExpr) override;
    LoxObject visit(const AssignmentExpr *assignmentExpr) override;
    LoxObject visit(const OrExpr *orExpr) override;
    LoxObject visit(const AndExpr *andExpr) override;
    LoxObject visit(const FunctionCallExpr *functionCallExpr) override;
    LoxObject visit(const IncrementExpr *incrementExpr) override;
    LoxObject visit(const DecrementExpr *decrementExpr) override;
    LoxObject visit(const LambdaExpr *lambdaExpr) override;

    void interpretReplMode(Stmt* stmt);
    LoxObject interpret(Expr* expr);
    LoxObject interpret(Expr* expr, Environment::SharedPtr newEnv);
    void execute(Stmt* pStmt);
    void executeBlock(const std::vector<UniqueStmtPtr> &stmts, Environment::SharedPtr newEnv);
    void loadBuiltinFunctions();
};



#endif //JLOX_INTERPRETER_H
