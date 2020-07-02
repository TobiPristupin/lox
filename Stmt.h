#ifndef JLOX_STMT_H
#define JLOX_STMT_H

#include <vector>
#include "Expr.h"

class Stmt;
class ExpressionStmt;
class PrintStmt;
class VarStmt;
class BlockStmt;

using UniqueStmtPtr = std::unique_ptr<Stmt>;

class StmtVisitor {
public:
    virtual void visit(ExpressionStmt *expressionStmt) = 0;
    virtual void visit(PrintStmt *printStmt) = 0;
    virtual void visit(VarStmt *varStmt) = 0;
    virtual void visit(BlockStmt *blockStmt) = 0;

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


#endif //JLOX_STMT_H
