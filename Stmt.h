#ifndef JLOX_STMT_H
#define JLOX_STMT_H

#include <vector>
#include "Expr.h"

class ExpressionStmt;
class PrintStmt;
class VarStmt;
class BlockStmt;


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
    virtual void accept(StmtVisitor& visitor) = 0;
};

class ExpressionStmt : public Stmt {
public:
    Expr* expr;

    ExpressionStmt(Expr *expr);
    void accept(StmtVisitor &visitor) override;
};

class PrintStmt : public Stmt {
public:
    Expr* expr;

    PrintStmt(Expr *expr);
    void accept(StmtVisitor &visitor) override;
};

class VarStmt : public Stmt {
public:
    Token identifier;
    Expr *expr;

    VarStmt(Token &identifier, Expr *expr);
    void accept(StmtVisitor &visitor) override;
};

class BlockStmt : public Stmt {
public:
    std::vector<Stmt*> statements;

    BlockStmt(const std::vector<Stmt*> &statements);
    void accept(StmtVisitor &visitor) override;
};


#endif //JLOX_STMT_H
