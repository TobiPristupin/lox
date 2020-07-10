#ifndef JLOX_STMT_H
#define JLOX_STMT_H

#include <vector>
#include "Expr.h"

class Stmt;
class ExpressionStmt;
class PrintStmt;
class VarStmt;
class BlockStmt;
class IfStmt;
class WhileStmt;
class BreakStmt;
class ContinueStmt;

using UniqueStmtPtr = std::unique_ptr<Stmt>;

class StmtVisitor {
public:
    virtual void visit(ExpressionStmt *expressionStmt) = 0;
    virtual void visit(PrintStmt *printStmt) = 0;
    virtual void visit(VarStmt *varStmt) = 0;
    virtual void visit(BlockStmt *blockStmt) = 0;
    virtual void visit(IfStmt *ifStmt) = 0;
    virtual void visit(WhileStmt *whileStmt) = 0;
    virtual void visit(BreakStmt *breakStmt) = 0;
    virtual void visit(ContinueStmt *continueStmt) = 0;

};

class Stmt {
public:
    virtual ~Stmt() = 0;
    virtual void accept(StmtVisitor& visitor)= 0;
};

class ExpressionStmt : public Stmt {
public:
    UniqueExprPtr expr;

    ExpressionStmt(UniqueExprPtr expr);
    void accept(StmtVisitor &visitor) override;
};

class PrintStmt : public Stmt {
public:
    UniqueExprPtr expr;

    PrintStmt(UniqueExprPtr expr);
    void accept(StmtVisitor &visitor) override;
};

class VarStmt : public Stmt {
public:
    Token identifier;
    UniqueExprPtr expr;

    VarStmt(const Token &identifier, UniqueExprPtr expr);
    void accept(StmtVisitor &visitor) override;
};

class BlockStmt : public Stmt {
public:
    std::vector<UniqueStmtPtr> statements;

    BlockStmt(std::vector<UniqueStmtPtr> statements);
    void accept(StmtVisitor &visitor) override;
};

class IfBranch {
public:
    UniqueExprPtr condition;
    UniqueStmtPtr statement;

    IfBranch(UniqueExprPtr condition, UniqueStmtPtr statement);
};

class IfStmt : public Stmt {
public:
    IfBranch mainBranch;
    std::vector<IfBranch> elifBranches;
    UniqueStmtPtr elseBranch;

    IfStmt(IfBranch mainBranch, std::vector<IfBranch> elifBranches, UniqueStmtPtr elseBranch);
    void accept(StmtVisitor &visitor) override;
};

class WhileStmt : public Stmt {
public:
    UniqueExprPtr condition;
    UniqueStmtPtr body;

    WhileStmt(UniqueExprPtr condition, UniqueStmtPtr body);
    void accept(StmtVisitor &visitor) override;
};

class BreakStmt : public Stmt {
public:
    void accept(StmtVisitor &visitor) override;
};

class BreakException {};

class ContinueStmt : public Stmt {
public:
    void accept(StmtVisitor &visitor) override;
};

class ContinueException {};



#endif //JLOX_STMT_H
