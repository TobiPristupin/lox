#ifndef JLOX_STMT_H
#define JLOX_STMT_H

#include <vector>
#include "Expr.h"

class Stmt;
class ExpressionStmt;
class PrintStmt;
class VarDeclarationStmt;
class BlockStmt;
class IfStmt;
class WhileStmt;
class ForStmt;
class BreakStmt;
class ContinueStmt;
class FunctionDeclStmt;
class ReturnStmt;

using UniqueStmtPtr = std::unique_ptr<Stmt>;

class StmtVisitor {
public:
    virtual void visit(const ExpressionStmt *expressionStmt) = 0;
    virtual void visit(const PrintStmt *printStmt) = 0;
    virtual void visit(const VarDeclarationStmt *varStmt) = 0;
    virtual void visit(const BlockStmt *blockStmt) = 0;
    virtual void visit(const IfStmt *ifStmt) = 0;
    virtual void visit(const WhileStmt *whileStmt) = 0;
    virtual void visit(const BreakStmt *breakStmt) = 0;
    virtual void visit(const ContinueStmt *continueStmt) = 0;
    virtual void visit(const ForStmt *forStmt) = 0;
    virtual void visit(const FunctionDeclStmt *functionStmt) = 0;
    virtual void visit(const ReturnStmt *returnStmt) = 0;

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

class VarDeclarationStmt : public Stmt {
public:
    Token identifier;
    UniqueExprPtr expr; //may be nullptr when declaring a variable without initializing

    VarDeclarationStmt(const Token &identifier, UniqueExprPtr expr);
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

class ForStmt : public Stmt {
public:
    UniqueStmtPtr initializer, body, increment;
    UniqueExprPtr condition;

    ForStmt(UniqueStmtPtr initializer, UniqueExprPtr condition, UniqueStmtPtr increment, UniqueStmtPtr body);
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

class FunctionDeclStmt : public Stmt {
public:
    Token name;
    std::vector<Token> params;
    std::vector<UniqueStmtPtr> body;

    FunctionDeclStmt(const Token &name, const std::vector<Token> &params, std::vector<UniqueStmtPtr> body);
    void accept(StmtVisitor &visitor) override;
};

class ReturnStmt : public Stmt {
public:
    UniqueExprPtr expr;
    Token keyword;

    explicit ReturnStmt(const Token &keyword, UniqueExprPtr expr);
    void accept(StmtVisitor &visitor) override;
};

class ReturnException {
public:
    LoxObject value;

    explicit ReturnException(const LoxObject& value);
};



#endif //JLOX_STMT_H
