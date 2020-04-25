//
// Created by pristu on 4/23/20.
//

#ifndef JLOX_EXPRESSION_H
#define JLOX_EXPRESSION_H

#include <sstream>
#include "Token.h"

struct Expression {
    //An empty virtual destructor allows Expression to become a class with polymorphism and generate a v-table
    //which in turn allows the use of dynamic_cast to downcast Expression pointers to pointers of its derived classes (BinaryExpr, GroupingExpr, etc)
    virtual ~Expression() {}
    virtual std::string to_string() = 0;
};

struct BinaryExpr : public Expression {
    Expression* left;
    Expression* right;
    Token* op;

    BinaryExpr (Expression* left, Expression* right, Token* op) : left(left), right(right), op(op) {}

    std::string to_string() override {
        std::stringstream ss;
        ss << "( " << left->to_string() << " " << op->lexeme << " " << right->to_string() << " )";
        return ss.str();
    }
};

struct GroupingExpr : public Expression {
    Expression* expr;

    GroupingExpr(Expression* expr) : expr(expr) {}

    std::string to_string() override {
        std::stringstream ss;
        ss << "( " << expr->to_string() << " )";
        return ss.str();
    }
};

struct UnaryExpr : public Expression {
    Token* op;
    Expression* right;

    UnaryExpr(Token* op, Expression* right) : op(op), right(right) {}

    std::string to_string() override {
        std::stringstream ss;
        ss << op->lexeme << "( " << right->to_string() << " )";
        return ss.str();
    }
};

struct LiteralExpr : public Expression {
    lox_literal_t literal;

    LiteralExpr(lox_literal_t literal) : literal(literal) {}

    std::string to_string() override {
        std::string  s;
        if (std::holds_alternative<std::string>(literal)){
            s = std::get<std::string>(literal);
        } else if (std::holds_alternative<int>(literal)){
            s = std::to_string(std::get<int>(literal));
        } else if (std::holds_alternative<float>(literal)){
            s = std::to_string(std::get<float>(literal));
        } else if (std::holds_alternative<bool>(literal)){
            s = std::to_string(std::get<bool>(literal));
        } else if (std::holds_alternative<nullptr_t>(literal)) {
            s = "null";
        }
        return s;
    }
};


#endif //JLOX_EXPRESSION_H
