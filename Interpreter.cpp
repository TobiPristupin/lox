#include <stdexcept>
#include <iostream>
#include <cassert>
#include <gsl/gsl_util>
#include <sstream>
#include "Interpreter.h"
#include "Token.h"
#include "LoxError.h"
#include "LoxCallable.h"
#include "standardlib/StandardFunctions.h"
#include "LoxFunctionWrapper.h"

//TODO: Abstract the environments stack behavior into an environment manager class


Interpreter::Interpreter() {
    environments.push(Environment());
    globalEnv = &environments.top();
    LoxObject function(std::make_shared<standardFunctions::Clock>());
    globalEnv->define("clock", function);
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
        LoxObject result = interpret(exprStmt->expr.get());
        if (result.isNil()){ //don't output anything if the statement had no output
            return;
        }

        std::cout << result << "\n";
    } else {
        execute(stmt);
    }
}


LoxObject Interpreter::interpret(Expr *expr) {
    return expr->accept(*this);
}


void Interpreter::execute(Stmt* stmt) {
    stmt->accept(*this);
}

//STATEMENTS

void Interpreter::visit(VarDeclarationStmt *varDeclarationStmt) {
    if (varDeclarationStmt->expr != nullptr){
        LoxObject initializer = interpret(varDeclarationStmt->expr.get());
        environments.top().define(varDeclarationStmt->identifier, initializer);
    } else {
        environments.top().define(varDeclarationStmt->identifier, LoxObject());
    }
}

LoxObject Interpreter::visit(const AssignmentExpr *assignmentExpr) {
    LoxObject value = interpret(assignmentExpr->value.get());
    environments.top().assign(assignmentExpr->identifier, value);
    return value;
}

void Interpreter::visit(ExpressionStmt *expressionStmt) {
    interpret(expressionStmt->expr.get());
}

void Interpreter::visit(PrintStmt *printStmt) {
    if (printStmt->expr.get() == nullptr){
        std::cout << "\n";
        return;
    }

    LoxObject result = interpret(printStmt->expr.get());
    std::cout << result << "\n";
}

void Interpreter::visit(IfStmt *ifStmt) {
    LoxObject condition = interpret(ifStmt->mainBranch.condition.get());
    if (condition.truthy()){
        execute(ifStmt->mainBranch.statement.get());
        return;
    }

    for (const IfBranch &branch : ifStmt->elifBranches){
        LoxObject elifCondition = interpret(branch.condition.get());
        if (elifCondition.truthy()){
            execute(branch.statement.get());
            return;
        }
    }

    if (ifStmt->elseBranch.get() != nullptr){
        execute(ifStmt->elseBranch.get());
    }
}

void Interpreter::visit(WhileStmt *whileStmt) {
    LoxObject condition = interpret(whileStmt->condition.get());
    while (condition.truthy()){
        try {
            execute(whileStmt->body.get());
        //We use special exceptions to unwind the stack when a break/continue statement is encountered.
        } catch (const BreakException &exception) {
            return;
        } catch (const ContinueException &exception) {
            //empty
        }

        condition = interpret(whileStmt->condition.get());
    }
}

void Interpreter::visit(ForStmt *forStmt) {
    Environment newEnv(&(this->environments.top()));
    environments.push(newEnv);
    //TODO: Could I do this with RAII?
    auto finalAction = gsl::finally([this] {this->environments.pop();}); //Make sure that the new environment is popped even if exceptions are thrown

    if (forStmt->initializer.get() != nullptr) {execute(forStmt->initializer.get());}
    bool noCondition = forStmt->condition.get() == nullptr;

    while (noCondition || interpret(forStmt->condition.get()).truthy()){
        try {
            execute(forStmt->body.get());
        } catch (const BreakException &exception) {
            return;
        } catch (const ContinueException &exception) {
            //empty
        }

        if (forStmt->increment.get() != nullptr) { execute(forStmt->increment.get()); }
    }
}

void Interpreter::visit(BlockStmt *blockStmt) {
    Environment newEnv(&(this->environments.top()));
    executeBlock(blockStmt->statements, newEnv);
}

void Interpreter::visit(BreakStmt *breakStmt) {
    throw BreakException();
}

void Interpreter::visit(ContinueStmt *continueStmt) {
    throw ContinueException();
}

void Interpreter::visit(FunctionDeclStmt *functionStmt) {
    SharedCallablePtr function = std::make_shared<LoxFunctionWrapper>(functionStmt);
    LoxObject functionObject(function);
    environments.top().define(functionStmt->name, functionObject);
}

//EXPRESSIONS

LoxObject Interpreter::visit(const BinaryExpr *binaryExpr) {
    LoxObject left = binaryExpr->left->accept(*this), right = binaryExpr->right->accept(*this);
    try {
        switch (binaryExpr->op.type){
            case TokenType::PLUS: return left + right;
            case TokenType::MINUS: return left - right;
            case TokenType::STAR: return left * right;
            case TokenType::SLASH: return left / right;
            case TokenType::GREATER: return LoxObject(left > right);
            case TokenType::GREATER_EQUAL: return LoxObject(left >= right);
            case TokenType::LESS: return LoxObject(left < right);
            case TokenType::LESS_EQUAL: return LoxObject(left <= right);
            case TokenType::BANG_EQUAL: return LoxObject(left != right);
            case TokenType::EQUAL_EQUAL: return LoxObject(left == right);
        }
    } catch (const std::runtime_error &error) {
        //Binary operations in LoxObject might throw exceptions, but LoxObject has no knowledge of the current line,
        //so we catch the exception here, create a new one with the same message and with the current line, and throw it again.
        throw LoxRuntimeError(error.what(), binaryExpr->op.line);;
    }


    //unreachable but just in case
    throw std::runtime_error("Invalid binary operand");
}

LoxObject Interpreter::visit(const GroupingExpr *groupingExpr) {
    return interpret(groupingExpr->expr.get());
}

LoxObject Interpreter::visit(const UnaryExpr *unaryExpr) {
    LoxObject expr = interpret(unaryExpr->expr.get());
    try {
        switch (unaryExpr->op.type){
            case TokenType::MINUS:
                return -expr;
            case TokenType::BANG:
                return !expr;
        }
    } catch (const std::runtime_error &error) {
        //Binary operations in LoxObject might throw exceptions, but LoxObject has no knowledge of the current line,
        //so we catch the exception here, create a new one with the same message and with the current line, and throw it again.
        throw LoxRuntimeError(error.what(), unaryExpr->op.line);
    }


    //unreachable
    throw std::runtime_error("Invalid unary operand");
}

LoxObject Interpreter::visit(const LiteralExpr *literalExpr) {
    return literalExpr->literal; //FIX THIS
}

LoxObject Interpreter::visit(const VariableExpr *variableExpr) {
    return environments.top().get(variableExpr->identifier);
}

LoxObject Interpreter::visit(const OrExpr *orExpr) {
    LoxObject lhs = interpret(orExpr->left.get());
    if (lhs.truthy()){
        return LoxObject(true);
    }

    LoxObject rhs = interpret(orExpr->right.get());
    return LoxObject(rhs.truthy());
}

LoxObject Interpreter::visit(const AndExpr *andExpr) {
    LoxObject lhs = interpret(andExpr->left.get());
    if (!lhs.truthy()){
        return LoxObject(false);
    }
    LoxObject rhs = interpret(andExpr->right.get());
    return LoxObject(rhs.truthy());
}

LoxObject Interpreter::visit(const FunctionCallExpr *functionCallExpr) {
    LoxObject callee = interpret(functionCallExpr->callee.get());

    std::vector<LoxObject> arguments;
    for (const UniqueExprPtr &arg : functionCallExpr->arguments){
        arguments.push_back(interpret(arg.get()));
    }

    if (!callee.isCallable()){
        throw LoxRuntimeError("Expression is not callable", functionCallExpr->closingParen.line);
    }
    LoxCallable* function = callee.getCallable();
    if (arguments.size() != function->arity()){
        std::stringstream ss;
        ss << "Function " << function->name() << " expected " << function->arity() << " arguments but instead got " << arguments.size();
        throw LoxRuntimeError(ss.str(), functionCallExpr->closingParen.line);
    }

    return function->call(*this, arguments);
}

void Interpreter::executeBlock(const std::vector<UniqueStmtPtr> &stmts, const Environment &newEnv) {
    environments.push(newEnv);
    auto finalAction = gsl::finally([this] {this->environments.pop();}); //Make sure that the new environment is popped even if exceptions are thrown
                                                                            //TODO: Could I do this with RAII?
    for (auto const &stmt : stmts){
        execute(stmt.get());
    }
}