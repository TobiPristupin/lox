#ifndef JLOX_STMT_H
#define JLOX_STMT_H

#include <vector>
#include <optional>
#include "Token.h"
#include "LoxObject.h"
#include "typedefs.h"

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
class ClassDeclStmt;

class Expr;

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
    virtual void visit(const ClassDeclStmt *classDeclStmt) = 0;
};


class Stmt {
public:
    virtual ~Stmt() = 0;
    virtual void accept(StmtVisitor& visitor)= 0;
};

class ExpressionStmt : public Stmt {
public:
    UniqueExprPtr expr;

    explicit ExpressionStmt(UniqueExprPtr expr);
    void accept(StmtVisitor &visitor) override;
};

class PrintStmt : public Stmt {
public:
    std::optional<UniqueExprPtr> expr;

    explicit PrintStmt(std::optional<UniqueExprPtr> expr);
    void accept(StmtVisitor &visitor) override;
};

class VarDeclarationStmt : public Stmt {
public:
    Token identifier;
    //Optional because you may declare a variable without initializing it.
    std::optional<UniqueExprPtr> expr;

    VarDeclarationStmt(const Token &identifier, std::optional<UniqueExprPtr> expr);
    void accept(StmtVisitor &visitor) override;
};

class BlockStmt : public Stmt {
public:
    std::vector<UniqueStmtPtr> statements;

    explicit BlockStmt(std::vector<UniqueStmtPtr> statements);
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
    std::optional<UniqueStmtPtr> elseBranch;

    IfStmt(IfBranch mainBranch, std::vector<IfBranch> elifBranches, std::optional<UniqueStmtPtr> elseBranch);
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
    std::optional<UniqueStmtPtr> initializer, increment;
    std::optional<UniqueExprPtr> condition;
    UniqueStmtPtr body;

    ForStmt(std::optional<UniqueStmtPtr> initializer, std::optional<UniqueExprPtr> condition, std::optional<UniqueStmtPtr> increment, UniqueStmtPtr body);
    void accept(StmtVisitor &visitor) override;
};

class BreakStmt : public Stmt {
public:
    Token keyword;

    explicit BreakStmt(const Token &keyword);
    void accept(StmtVisitor &visitor) override;
};

class BreakException {};

class ContinueStmt : public Stmt {
public:
    Token keyword;

    explicit ContinueStmt(const Token &keyword);
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
    std::optional<UniqueExprPtr> expr;
    Token keyword;

    explicit ReturnStmt(const Token &keyword, std::optional<UniqueExprPtr> expr);
    void accept(StmtVisitor &visitor) override;
};

class ReturnException {
public:
    LoxObject value;

    explicit ReturnException(const LoxObject& value);
};

class ClassDeclStmt : public Stmt {
public:
    Token identifier;
    std::vector<std::unique_ptr<FunctionDeclStmt>> methods;

    ClassDeclStmt(const Token &identifier, std::vector<std::unique_ptr<FunctionDeclStmt>> methods);
    void accept(StmtVisitor &visitor) override;
};


#endif //JLOX_STMT_H
