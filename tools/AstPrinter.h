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

private:
    std::stringstream ss;
    void visit(const BinaryExpr *binaryExpr) override;
    void visit(const GroupingExpr *groupingExpr) override;
    void visit(const UnaryExpr *unaryExpr) override;
    void visit(const LiteralExpr *literalExpr) override;
};


#endif //JLOX_ASTPRINTER_H
