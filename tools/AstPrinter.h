//
// Created by pristu on 4/25/20.
//

#ifndef JLOX_ASTPRINTER_H
#define JLOX_ASTPRINTER_H


#include <sstream>
#include "../Expr.h"

class AstPrinter : public ExprVisitor {

public:
    std::string print(Expr *expr);
    lox_literal_t visit(const BinaryExpr *binaryExpr) override;
    lox_literal_t visit(const GroupingExpr *groupingExpr) override;
    lox_literal_t visit(const UnaryExpr *unaryExpr) override;
    lox_literal_t visit(const LiteralExpr *literalExpr) override;

private:
    std::stringstream ss;
};


#endif //JLOX_ASTPRINTER_H
