#ifndef JLOX_INTERPRETER_H
#define JLOX_INTERPRETER_H

#include <unordered_map>
#include <vector>
#include "Environment.h"
#include "Expr.h"
#include "Stmt.h"
#include "LoxObject.h"
#include "typedefs.h"

class Interpreter : public ExprVisitor, public StmtVisitor {
public:
    Environment::SharedPtr globalEnv;
    Environment::SharedPtr environment;
    //Contains the number of "hops" between the current environment and the environment where the variable referenced by Expr* is stored
    std::unordered_map<const Expr*, int> localsDistances;

    Interpreter();

    void interpret(const std::vector<UniqueStmtPtr> &statements, const std::unordered_map<const Expr*, int> &distances, bool replMode = false);
    void executeBlock(const std::vector<UniqueStmtPtr> &stmts, Environment::SharedPtr newEnv);
    LoxObject interpret(Expr* expr, Environment::SharedPtr newEnv);


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
    void visit(const ClassDeclStmt *classDeclStmt) override;


    LoxObject visit(const BinaryExpr *binaryExpr) override;
    LoxObject visit(const GroupingExpr *GroupingExpr) override;
    LoxObject visit(const UnaryExpr *unaryExpr) override;
    LoxObject visit(const LiteralExpr *literalExpr) override;
    LoxObject visit(const VariableExpr *literalExpr) override;
    LoxObject visit(const AssignmentExpr *assignmentExpr) override;
    LoxObject visit(const OrExpr *orExpr) override;
    LoxObject visit(const AndExpr *andExpr) override;
    LoxObject visit(const CallExpr *callExpr) override;
    LoxObject visit(const IncrementExpr *incrementExpr) override;
    LoxObject visit(const DecrementExpr *decrementExpr) override;
    LoxObject visit(const LambdaExpr *lambdaExpr) override;
    LoxObject visit(const GetExpr *getExpr) override;
    LoxObject visit(const SetExpr *setExpr) override;
    LoxObject visit(const ThisExpr *thisExpr) override;
    LoxObject visit(const SuperExpr *superExpr) override;

private:
    void interpretReplMode(Stmt* stmt);
    LoxObject interpret(Expr* expr);
    void execute(Stmt* pStmt);
    void loadBuiltinFunctions();
    LoxObject lookupVariable(const Expr *pExpr, const Token &identifier);
    std::optional<LoxObject> getSuperclass(const ClassDeclStmt* classDeclStmt);
};



#endif //JLOX_INTERPRETER_H
