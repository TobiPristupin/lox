#include <iostream>
#include "AstPrinter.h"
#include "utils.h"

std::string AstPrinter::print(Expr *expr) {
    expr->accept(*this);
    return ss.str();
}

lox_literal_t AstPrinter::visit(const BinaryExpr *binaryExpr) {
    ss << "(" << binaryExpr->op.lexeme << " ";
    binaryExpr->left->accept(*this);
    ss << " ";
    binaryExpr->right->accept(*this);
    ss << ")";
    return nullptr;
}

lox_literal_t AstPrinter::visit(const GroupingExpr *groupingExpr) {
    ss << "(group ";
    groupingExpr->expr->accept(*this);
    ss << ")";
    return nullptr;
}

lox_literal_t AstPrinter::visit(const UnaryExpr *unaryExpr) {
    ss << "(" << unaryExpr->op.lexeme;
    unaryExpr->expr->accept(*this);
    ss << ")";
    return nullptr;
}

lox_literal_t AstPrinter::visit(const LiteralExpr *literalExpr) {
    lox_literal_t literal = literalExpr->literal;
    ss << literalToString(literal);
    return nullptr;
}


