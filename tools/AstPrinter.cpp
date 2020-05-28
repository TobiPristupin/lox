//
// Created by pristu on 4/25/20.
//

#include <iostream>
#include "AstPrinter.h"

std::string AstPrinter::print(Expr *expr) {
    expr->accept(*this);
    return ss.str();
}

void AstPrinter::visit(const BinaryExpr *binaryExpr) {
    binaryExpr->left->accept(*this);
    ss << binaryExpr->op->lexeme;
    binaryExpr->right->accept(*this);
}

void AstPrinter::visit(const GroupingExpr *groupingExpr) {
    ss << "(";
    groupingExpr->expr->accept(*this);
    ss << ")";
}

void AstPrinter::visit(const UnaryExpr *unaryExpr) {
    ss << unaryExpr->op->lexeme;
    unaryExpr->expr->accept(*this);
}

void AstPrinter::visit(const LiteralExpr *literalExpr) {
    lox_literal_t literal = literalExpr->literal;
    if (std::holds_alternative<std::string>(literal)){
//        std::cout << "yee\n";
        ss << std::get<std::string>(literal);
    } else if (std::holds_alternative<int>(literal)){
        ss << std::to_string(std::get<int>(literal));
    } else if (std::holds_alternative<float>(literal)){
        ss << std::to_string(std::get<float>(literal));
    } else if (std::holds_alternative<bool>(literal)){
        ss << std::to_string(std::get<bool>(literal));
    } else if (std::holds_alternative<nullptr_t>(literal)) {
        ss << " null";
    }
}


