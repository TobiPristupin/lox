#include <stdexcept>
#include "Token.h"
#include "Interpreter.h"


lox_literal_t Interpreter::interpret(Expr *expr) {
    return expr->accept(*this);
}

lox_literal_t Interpreter::visit(const BinaryExpr *binaryExpr) {
    lox_literal_t left = binaryExpr->left->accept(*this), right = binaryExpr->right->accept(*this);
    switch (binaryExpr->op.type){
        case TokenType::MINUS: return minus(left, right);
        case TokenType::STAR: return star(left, right);
        case TokenType::SLASH: return slash(left, right);
        //Following cases apply to both strings and doubles
        case TokenType::GREATER: return greater(left, right);
        case TokenType::GREATER_EQUAL: return greater(left, right) || equal(left, right);
        case TokenType::LESS: return less(left, right);
        case TokenType::LESS_EQUAL: return less(left, right) || equal(left, right);
        case TokenType::BANG_EQUAL: return !equal(left, right);
        case TokenType::EQUAL_EQUAL: return equal(left, right);
        case TokenType::PLUS: return plus(left, right);
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
                //TODO: Invalid operand
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

lox_literal_t Interpreter::minus(lox_literal_t &left, lox_literal_t &right) {
    assertOperandsType<double>(left, right);
    return std::get<double>(left) + std::get<double>(right);
}

lox_literal_t Interpreter::plus(lox_literal_t &left, lox_literal_t &right) {
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right);
        return std::get<std::string>(left) + std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right);
    return std::get<double>(left) + std::get<double>(right);
}

lox_literal_t Interpreter::star(lox_literal_t &left, lox_literal_t &right) {
    assertOperandsType<double>(left, right);
    return std::get<double>(left) * std::get<double>(right);
}

lox_literal_t Interpreter::slash(lox_literal_t &left, lox_literal_t &right) {
    assertOperandsType<double>(left, right);
    if (std::get<double>(right) == 0){
        throw std::runtime_error("Cannot divide by zero");
        //TODO: Improve
    }
    return std::get<double>(left) / std::get<double>(right);
}

bool Interpreter::greater(lox_literal_t &left, lox_literal_t &right) {
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right);
        return std::get<std::string>(left) > std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right);
    return std::get<double>(left) > std::get<double>(right);
}

bool Interpreter::less(lox_literal_t &left, lox_literal_t &right) {
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right);
        return std::get<std::string>(left) < std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right);
    return std::get<double>(left) < std::get<double>(right);
}

bool Interpreter::equal(lox_literal_t &left, lox_literal_t &right) {
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
void Interpreter::assertOperandsType(lox_literal_t &left, lox_literal_t &right) { //Asserts that the type of left and right is T
    if (!(std::holds_alternative<T>(left) && std::holds_alternative<T>(right))){
        throw std::runtime_error("Operands must match");
        //TODO: Improve error detection
    }
}
