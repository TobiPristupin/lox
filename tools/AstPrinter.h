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
    LoxObject visit(const BinaryExpr *binaryExpr) override;
    LoxObject visit(const GroupingExpr *groupingExpr) override;
    LoxObject visit(const UnaryExpr *unaryExpr) override;
    LoxObject visit(const LiteralExpr *literalExpr) override;

private:
    std::stringstream ss;
};


#endif //JLOX_ASTPRINTER_H
