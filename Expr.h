#ifndef JLOX_EXPR_H
#define JLOX_EXPR_H

#include <memory>
#include <vector>
#include "Token.h"
#include "LoxObject.h"
#include "typedefs.h"

class BinaryExpr;
class GroupingExpr;
class UnaryExpr;
class LiteralExpr;
class VariableExpr;
class AssignmentExpr;
class OrExpr;
class AndExpr;
class CallExpr;
class IncrementExpr;
class DecrementExpr;
class LambdaExpr;
class GetExpr;
class SetExpr;

class ExprVisitor {
public:
    virtual LoxObject visit(const BinaryExpr* binaryExpr) = 0;
    virtual LoxObject visit(const GroupingExpr* groupingExpr) = 0;
    virtual LoxObject visit(const UnaryExpr* unaryExpr) = 0;
    virtual LoxObject visit(const LiteralExpr* literalExpr) = 0;
    virtual LoxObject visit(const VariableExpr* variableExpr) = 0;
    virtual LoxObject visit(const AssignmentExpr* assignmentExpr) = 0;
    virtual LoxObject visit(const OrExpr* orExpr) = 0;
    virtual LoxObject visit(const AndExpr* andExpr) = 0;
    virtual LoxObject visit(const CallExpr* functionCallExpr) = 0;
    virtual LoxObject visit(const IncrementExpr* incrementExpr) = 0;
    virtual LoxObject visit(const DecrementExpr* decrementExpr) = 0;
    virtual LoxObject visit(const LambdaExpr* lambdaExpr) = 0;
    virtual LoxObject visit(const GetExpr* getExpr) = 0;
    virtual LoxObject visit(const SetExpr* setExpr) = 0;
};


class Expr {
public:
    virtual ~Expr() = default;
    virtual LoxObject accept(ExprVisitor& visitor) = 0;
};

class BinaryExpr : public Expr {
public:
    UniqueExprPtr left;
    UniqueExprPtr right;
    Token op;

    BinaryExpr (UniqueExprPtr left, UniqueExprPtr right, const Token &op);
    LoxObject accept(ExprVisitor& visitor) override;
};

class GroupingExpr : public Expr {
public:
    UniqueExprPtr expr;

    explicit GroupingExpr(UniqueExprPtr expr);
    LoxObject accept(ExprVisitor& visitor) override;
};

class UnaryExpr : public Expr {
public:
    Token op;
    UniqueExprPtr expr;

    UnaryExpr(const Token &op, UniqueExprPtr expr);
    LoxObject accept(ExprVisitor& visitor) override;
};

class LiteralExpr : public Expr {
public:
    LoxObject literal;

    explicit LiteralExpr(const LoxObject &literal);
    LoxObject accept(ExprVisitor& visitor) override;

};

class VariableExpr : public Expr {
public:
    Token identifier;

    explicit VariableExpr(const Token &identifier);
    LoxObject accept(ExprVisitor& visitor) override;

};

class AssignmentExpr : public Expr {
public:
    Token identifier;
    UniqueExprPtr value;

    AssignmentExpr(const Token &identifier, UniqueExprPtr value);
    LoxObject accept(ExprVisitor &visitor) override;
};

class OrExpr : public Expr {
public:
    UniqueExprPtr left, right;

    OrExpr(UniqueExprPtr left, UniqueExprPtr right);
    LoxObject accept(ExprVisitor &visitor) override;
};

class AndExpr : public Expr {
public:
    UniqueExprPtr left, right;

    AndExpr(UniqueExprPtr left, UniqueExprPtr right);
    LoxObject accept(ExprVisitor &visitor) override;
};

class CallExpr : public Expr {
public:
    UniqueExprPtr callee;
    Token closingParen;
    std::vector<UniqueExprPtr> arguments;

    CallExpr(UniqueExprPtr callee, const Token &closingParen, std::vector<UniqueExprPtr> arguments);
    LoxObject accept(ExprVisitor &visitor) override;
};

class IncrementExpr : public Expr {
public:
    enum class Type {
        POSTFIX, PREFIX
    };

    std::unique_ptr<VariableExpr> variable;
    IncrementExpr::Type type;

    IncrementExpr(std::unique_ptr<VariableExpr> variable, IncrementExpr::Type type);
    LoxObject accept(ExprVisitor &visitor) override;
};

class DecrementExpr : public Expr {
public:
    enum class Type {
        POSTFIX, PREFIX
    };

    std::unique_ptr<VariableExpr>  variable;
    DecrementExpr::Type type;

    DecrementExpr(std::unique_ptr<VariableExpr> variable, Type type);
    LoxObject accept(ExprVisitor &visitor) override;
};

class LambdaExpr : public Expr {
public:
    std::vector<Token> params;
    UniqueExprPtr body;

    LambdaExpr(const std::vector<Token> &params, UniqueExprPtr body);
    LoxObject accept(ExprVisitor &visitor) override;
};

class GetExpr : public Expr {
public:
    /*VariableExpr that refers to the object (not the field!) that is being accessed. For example if the parsed code were
     * 'obj.a' then this variable would hold a pointer to 'obj' */
    UniqueExprPtr expr;
    /*Token of the identifier of the field being accessed. If the parsed code were 'obj.a' then this variable would contain
     * the token corresponding to 'a' */
    Token identifier;

    GetExpr(UniqueExprPtr expr, const Token &identifier);
    LoxObject accept(ExprVisitor &visitor) override;
};

class SetExpr : public Expr {
public:
    /*VariableExpr that refers to the object (not the field!) that is being accessed. For example if the parsed code were
     * 'obj.a' then this variable would hold a pointer to 'obj' */
    UniqueExprPtr object;
    /*Token of the identifier of the field being accessed. If the parsed code were 'obj.a' then this variable would contain
     * the token corresponding to 'a' */
    Token identifier;

    UniqueExprPtr value;


    SetExpr(UniqueExprPtr object, const Token &identifier, UniqueExprPtr value);
    LoxObject accept(ExprVisitor &visitor) override;
};

#endif //JLOX_EXPR_H
