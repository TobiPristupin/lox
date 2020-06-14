#ifndef JLOX_INTERPRETER_H
#define JLOX_INTERPRETER_H

#include "Expr.h"
#include "LoxError.h"

class Interpreter : public ExprVisitor {
public:
    lox_literal_t interpret(Expr *expr);
    lox_literal_t visit(const BinaryExpr *binaryExpr) override;
    lox_literal_t visit(const GroupingExpr *GroupingExpr) override;
    lox_literal_t visit(const UnaryExpr *unaryExpr) override;
    lox_literal_t visit(const LiteralExpr *literalExpr) override;

private:
    lox_literal_t result;
    lox_literal_t minus(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr);
    lox_literal_t plus(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr);
    lox_literal_t star(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr);
    lox_literal_t slash(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr);
    bool greater(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr);
    bool less(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr);
    bool equal(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr);
    bool isTruthy(const lox_literal_t &literal);
    template <typename T>
    void assertOperandsType(lox_literal_t &left, lox_literal_t &right, LoxRuntimeError error);
};



#endif //JLOX_INTERPRETER_H
