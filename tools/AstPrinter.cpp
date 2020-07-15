#include <iostream>
#include "AstPrinter.h"

std::string AstPrinter::print(Expr *expr) {
    expr->accept(*this);
    return ss.str();
}

LoxObject AstPrinter::visit(const BinaryExpr *binaryExpr) {
    ss << "(" << binaryExpr->op.lexeme << " ";
    binaryExpr->left->accept(*this);
    ss << " ";
    binaryExpr->right->accept(*this);
    ss << ")";
    return LoxObject();
}

LoxObject AstPrinter::visit(const GroupingExpr *groupingExpr) {
    ss << "(group ";
    groupingExpr->expr->accept(*this);
    ss << ")";
    return LoxObject();
}

LoxObject AstPrinter::visit(const UnaryExpr *unaryExpr) {
    ss << "(" << unaryExpr->op.lexeme;
    unaryExpr->expr->accept(*this);
    ss << ")";
    return LoxObject();
}

LoxObject AstPrinter::visit(const LiteralExpr *literalExpr) {
    LoxObject literal = literalExpr->literal;
    ss << literal;
    return LoxObject();
}


