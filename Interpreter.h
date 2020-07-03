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
    void visit(VarStmt *varStmt) override;
    void visit(BlockStmt *blockStmt) override;
    void visit(IfStmt *ifStmt) override;

    lox_literal_t visit(const BinaryExpr *binaryExpr) override;
    lox_literal_t visit(const GroupingExpr *GroupingExpr) override;
    lox_literal_t visit(const UnaryExpr *unaryExpr) override;
    lox_literal_t visit(const LiteralExpr *literalExpr) override;
    lox_literal_t visit(const VariableExpr *literalExpr) override;
    lox_literal_t visit(const AssignmentExpr *assignmentExpr) override;


private:
    std::stack<Environment> environments;

    void interpretReplMode(Stmt* stmt);
    lox_literal_t interpret(Expr* expr);
    void execute(Stmt* pStmt);
    void executeBlock(const std::vector<UniqueStmtPtr> &stmts, const Environment &newEnv);

    lox_literal_t minus(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr);
    lox_literal_t plus(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr);
    lox_literal_t star(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr);
    lox_literal_t slash(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr);
    bool greater(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr);
    bool greaterEqual(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr);
    bool less(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr);
    bool lessEqual(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr);
    bool equal(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr);
    bool isTruthy(const lox_literal_t &literal);
    template <typename T>
    void assertOperandsType(const lox_literal_t &left, const lox_literal_t &right, const LoxRuntimeError &error);

};



#endif //JLOX_INTERPRETER_H
