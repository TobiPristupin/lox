#include <stdexcept>
#include <iostream>
#include <cassert>
#include "Token.h"
#include "Interpreter.h"
#include "LoxError.h"
#include "tools/utils.h"

//TODO: Abstract the environments stack behavior into an environment manager class


Interpreter::Interpreter() {
    environments.push(Environment());
}


/*This function unpacks every UniqueStmtPtr into a raw pointer and then executes it. This is because the Interpreter does not
 * own the dynamically allocated statement objects, it only operates on them, so it should use raw pointers instead of a
 * smart pointer to signal that it does not own and has no influence over the lifetime of the objects.
 * */
void Interpreter::interpret(const std::vector<UniqueStmtPtr> &statements, bool replMode) {
    if (replMode){
        assert(statements.size() == 1);
        interpretReplMode(statements[0].get());
        return;
    }

    for (auto const &stmt : statements){
        execute(stmt.get());
    }
}

void Interpreter::interpretReplMode(Stmt *stmt) {
    auto* exprStmt = dynamic_cast<ExpressionStmt*>(stmt);
    if (exprStmt){ //If we are dealing with an expression statement such as "1+2" evaluate the expression and output it.
        lox_literal_t result = interpret(exprStmt->expr.get());
        if (std::holds_alternative<nullptr_t>(result)){
            return;
        }

        std::cout << utils::literalToString(result) << "\n";
    } else {
        execute(stmt);
    }
}


lox_literal_t Interpreter::interpret(Expr *expr) {
    return expr->accept(*this);
}

void Interpreter::execute(Stmt* stmt) {
    stmt->accept(*this);
}

void Interpreter::visit(VarStmt *varStmt) {
    lox_literal_t value = nullptr;
    if (varStmt->expr != nullptr){
        value = interpret(varStmt->expr.get());
    }

    environments.top().define(varStmt->identifier, value);
}

lox_literal_t Interpreter::visit(const AssignmentExpr *assignmentExpr) {
    lox_literal_t value = interpret(assignmentExpr->value.get());
    environments.top().assign(assignmentExpr->identifier, value);
    return value;
}

void Interpreter::visit(ExpressionStmt *expressionStmt) {
    interpret(expressionStmt->expr.get());
}

void Interpreter::visit(PrintStmt *printStmt) {
    lox_literal_t result = interpret(printStmt->expr.get());
    std::cout << utils::literalToString(result) << "\n";
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
    return interpret(groupingExpr->expr.get());
}

lox_literal_t Interpreter::visit(const UnaryExpr *unaryExpr) {
    lox_literal_t expr = interpret(unaryExpr->expr.get());
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

lox_literal_t Interpreter::visit(const VariableExpr *variableExpr) {
    return environments.top().get(variableExpr->identifier);
}

void Interpreter::visit(BlockStmt *blockStmt) {
    Environment newEnv(&(this->environments.top()));
    executeBlock(blockStmt->statements, newEnv);
}

void Interpreter::executeBlock(const std::vector<UniqueStmtPtr> &stmts, const Environment &newEnv) {
    environments.push(newEnv);
    for (auto const &stmt : stmts){
        execute(stmt.get());
    }
    environments.pop();
}


lox_literal_t Interpreter::minus(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '-' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) - std::get<double>(right);
}

lox_literal_t Interpreter::plus(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '+' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) + std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) + std::get<double>(right);
}

lox_literal_t Interpreter::star(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '*' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) * std::get<double>(right);
}

lox_literal_t Interpreter::slash(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '/' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    assertOperandsType<double>(left, right, error);
    if (std::get<double>(right) == 0){
        throw LoxRuntimeError("Cannot divide by zero", expr->op.line);
    }
    return std::get<double>(left) / std::get<double>(right);
}

bool Interpreter::greater(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '>' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) > std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) > std::get<double>(right);
}

bool Interpreter::greaterEqual(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '>=' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) >= std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) >= std::get<double>(right);
}

bool Interpreter::less(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '<' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) < std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) < std::get<double>(right);
}

bool Interpreter::lessEqual(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr) {
    LoxRuntimeError error("Cannot apply operator '<=' to operands of type " + utils::literalType(left) + " and " + utils::literalType(right), expr->op.line);
    if (std::holds_alternative<std::string>(left)){
        assertOperandsType<std::string>(left, right, error);
        return std::get<std::string>(left) <= std::get<std::string>(right);
    }

    assertOperandsType<double>(left, right, error);
    return std::get<double>(left) <= std::get<double>(right);
}

bool Interpreter::equal(const lox_literal_t &left, const lox_literal_t &right, const BinaryExpr *expr) {
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
void Interpreter::assertOperandsType(const lox_literal_t &left, const lox_literal_t &right, const LoxRuntimeError &error) { //Asserts that the type of left and right is T
    if (!(std::holds_alternative<T>(left) && std::holds_alternative<T>(right))){
        throw error;
    }
}











