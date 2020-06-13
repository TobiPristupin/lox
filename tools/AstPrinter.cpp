#include <iostream>
#include "AstPrinter.h"

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
    return lox_literal_t();
}

lox_literal_t AstPrinter::visit(const GroupingExpr *groupingExpr) {
    ss << "(group ";
    groupingExpr->expr->accept(*this);
    ss << ")";
    return lox_literal_t();
}

lox_literal_t AstPrinter::visit(const UnaryExpr *unaryExpr) {
    ss << "(" << unaryExpr->op.lexeme;
    unaryExpr->expr->accept(*this);
    ss << ")";
    return lox_literal_t();
}

lox_literal_t AstPrinter::visit(const LiteralExpr *literalExpr) {
    lox_literal_t literal = literalExpr->literal;
    if (std::holds_alternative<std::string>(literal)){
        ss << std::get<std::string>(literal);
    } else if (std::holds_alternative<double>(literal)){
        ss << std::to_string(std::get<double>(literal));
    } else if (std::holds_alternative<bool>(literal)){
        ss << std::to_string(std::get<bool>(literal));
    } else if (std::holds_alternative<nullptr_t>(literal)) {
        ss << "nil";
    }
    return lox_literal_t();
}


