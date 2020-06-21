#ifndef JLOX_STMT_H
#define JLOX_STMT_H

#include "Expr.h"

class ExpressionStmt;
class PrintStmt;
class VarStmt;


class StmtVisitor {
public:
    virtual void visit(ExpressionStmt *expressionStmt) = 0;
    virtual void visit(PrintStmt *printStmt) = 0;
    virtual void visit(VarStmt *printStmt) = 0;

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


#endif //JLOX_STMT_H
