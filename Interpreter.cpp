#include <stdexcept>
#include <iostream>
#include "Token.h"
#include "Interpreter.h"
#include "LoxError.h"
#include "tools/utils.h"

void Interpreter::interpret(std::vector<Stmt*> statements) {
    for (Stmt* stmt : statements){
        stmt->accept(*this);
    }

}
void Interpreter::visit(ExpressionStmt *expressionStmt) {
    interpret(expressionStmt->expr);
}

void Interpreter::visit(PrintStmt *printStmt) {
    lox_literal_t result = interpret(printStmt->expr);
    std::cout << utils::literalToString(result) << "\n";
}


lox_literal_t Interpreter::interpret(Expr *expr) {
    return expr->accept(*this);
}

lox_literal_t Interpreter::visit(const BinaryExpr *binaryExpr) {
    lox_literal_t left = binaryExpr->left->accept(*this), right = binaryExpr->right->accept(*this);
    switch (binaryExpr->op.type){
        case TokenType::MINUS: return minus(left, right, binaryExpr);
        case TokenType::STAR: return star(left, right, binaryExpr);
        case TokenType::SLASH: return slash(left, right, binaryExpr);
        //Following cases apply to both strings and doubles
        case TokenType::GREATER: return greater(left, right, binaryExpr);
        case TokenType::GREATER_EQUAL: return greaterEqual(left, right, binaryExpr);
        case TokenType::LESS: return less(left, right, binaryExpr);
        case TokenType::LESS_EQUAL: return lessEqual(left, right, binaryExpr);
        case TokenType::BANG_EQUAL: return !equal(left, right, binaryExpr);
        case TokenType::EQUAL_EQUAL: return equal(left, right, binaryExpr);
        case TokenType::PLUS: return plus(left, right, binaryExpr);
    }

    //unreachable
    return nullptr;
}

lox_literal_t Interpreter::visit(const GroupingExpr *groupingExpr) {
    return interpret(groupingExpr->expr);
}

lox_literal_t Interpreter::visit(const UnaryExpr *unaryExpr) {
    lox_literal_t expr = interpret(unaryExpr->expr);
    switch (unaryExpr->op.type){
        case TokenType::MINUS:
            if (std::holds_alternative<double>(expr)){
                return -(std::get<double>(expr));
            } else {
                throw LoxRuntimeError("Cannot apply unary operator '-' to operand of type " + utils::literalType(expr), unaryExpr->op.line);
            }
        case TokenType::BANG:
            return !isTruthy(expr);
    }

    //unreachable
    return nullptr;
}

lox_literal_t Interpreter::visit(const LiteralExpr *literalExpr) {
    return literalExpr->literal;
}

lox_literal_t Interpreter::minus(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '-' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) - std::get<double>(right);
}

lox_literal_t Interpreter::plus(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '+' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) + std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) + std::get<double>(right);
}

lox_literal_t Interpreter::star(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '*' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) * std::get<double>(right);
}

lox_literal_t Interpreter::slash(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '/' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    assertOperandsType<double>(left, right, error);
    if (std::get<double>(right) == 0){
        throw LoxRuntimeError("Cannot divide by zero", expr->op.line);
    }
    return std::get<double>(left) / std::get<double>(right);
}

bool Interpreter::greater(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '>' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) > std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) > std::get<double>(right);
}

bool Interpreter::greaterEqual(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '>=' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) >= std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) >= std::get<double>(right);
}

bool Interpreter::less(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '<' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) < std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) < std::get<double>(right);
}

bool Interpreter::lessEqual(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '<=' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) <= std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) <= std::get<double>(right);
}

bool Interpreter::equal(lox_literal_t &left, lox_literal_t &right, const BinaryExpr *expr) {
    if (left.index() != right.index()){ //different types are never equal
        return false;
    }

    return left == right;
}


bool Interpreter::isTruthy(const lox_literal_t &literal){ //In lox every literal is considered true except NIL and false
    if (std::holds_alternative<bool>(literal)){
        return std::get<bool>(literal);
    } else if (std::holds_alternative<nullptr_t>(literal)){
        return false;
    }

    return true;
}

template<typename T>
void Interpreter::assertOperandsType(lox_literal_t &left, lox_literal_t &right, LoxRuntimeError error) { //Asserts that the type of left and right is T
    if (!(std::holds_alternative<T>(left) && std::holds_alternative<T>(right))){
        throw error;
    }
}


