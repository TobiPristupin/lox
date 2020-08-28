#include "Interpreter.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include "LoxClass.h"
#include "LoxError.h"
#include "LoxFunction.h"
#include "TokenType.h"
#include "LoxCallable.h"
#include "standardlib/StandardFunctions.h"

//TODO: Add support for loading standard function in a more clean way


Interpreter::Interpreter() {
    environment = std::make_shared<Environment>();
    globalEnv = environment;
    loadBuiltinFunctions();
}


/*This function unpacks every UniqueStmtPtr into a raw pointer and then executes it. This is because the Interpreter does not
 * own the dynamically allocated statement objects, it only operates on them, so it should use raw pointers instead of a
 * smart pointer to signal that it does not own and has no influence over the lifetime of the objects.
 * */
void Interpreter::interpret(const std::vector<UniqueStmtPtr> &statements, const std::unordered_map<const Expr*, int> &distances, bool replMode) {
    this->localsDistances = distances;

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

LoxObject Interpreter::interpret(Expr *expr, Environment::SharedPtr newEnv) {
    ScopedEnvironment env(environment, newEnv);
    return interpret(expr);
}

void Interpreter::execute(Stmt* stmt) {
    stmt->accept(*this);
}

//STATEMENTS

void Interpreter::visit(const VarDeclarationStmt *varDeclarationStmt) {
    if (varDeclarationStmt->expr.has_value()){
        LoxObject initializer = interpret(varDeclarationStmt->expr.value().get());
        environment->define(varDeclarationStmt->identifier, initializer);
    } else {
        environment->define(varDeclarationStmt->identifier, LoxObject::Nil());
    }
}

LoxObject Interpreter::visit(const AssignmentExpr *assignmentExpr) {
    LoxObject value = interpret(assignmentExpr->value.get());
    if (localsDistances.find(assignmentExpr) != localsDistances.end()){
        environment->assignAt(assignmentExpr->identifier, value, localsDistances[assignmentExpr]);
    } else {
        globalEnv->assign(assignmentExpr->identifier, value);
    }

    return value;
}


void Interpreter::visit(const ExpressionStmt *expressionStmt) {
    interpret(expressionStmt->expr.get());
}

void Interpreter::visit(const PrintStmt *printStmt) {
    if (!printStmt->expr.has_value()){
        std::cout << "\n";
        return;
    }

    LoxObject result = interpret(printStmt->expr.value().get());
    std::cout << result << "\n";
}

void Interpreter::visit(const IfStmt *ifStmt) {
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

    if (ifStmt->elseBranch.has_value()){
        execute(ifStmt->elseBranch.value().get());
    }
}

void Interpreter::visit(const WhileStmt *whileStmt) {
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

void Interpreter::visit(const ForStmt *forStmt) {
    Environment::SharedPtr newEnv = std::make_shared<Environment>(environment);
    ScopedEnvironment scoped(environment, newEnv);

    if (forStmt->initializer.has_value()) {
        execute(forStmt->initializer.value().get());
    }

    bool noCondition = !forStmt->condition.has_value();
    while (noCondition || interpret(forStmt->condition.value().get()).truthy()){
        try {
            execute(forStmt->body.get());
        } catch (const BreakException &exception) {
            return;
        } catch (const ContinueException &exception) {
            //empty
        }

        if (forStmt->increment.has_value()) {
            execute(forStmt->increment.value().get());
        }
    }
}

void Interpreter::visit(const BlockStmt *blockStmt) {
    Environment::SharedPtr newEnv = std::make_shared<Environment>(environment);
    executeBlock(blockStmt->statements, newEnv);
}

void Interpreter::visit(const BreakStmt *breakStmt) {
    /*NOTE: We're using exceptions as control flow here because it is the cleanest way to implement break given
    how the book implements the interpreter. This exception should be catched in the visitForStmt and visitWhileStmt methods*/
    throw BreakException();
}

void Interpreter::visit(const ContinueStmt *continueStmt) {
    /*NOTE: We're using exceptions as control flow here because it is the cleanest way to implement continue given
    how the book implements the interpreter. This exception should be catched in the visitForStmt and visitWhileStmt methods*/
    throw ContinueException();
}

void Interpreter::visit(const FunctionDeclStmt *functionStmt) {
    SharedCallablePtr function = std::make_shared<LoxFunction>(functionStmt, environment);
    LoxObject functionObject(function);
    environment->define(functionStmt->name, functionObject);
}

LoxObject Interpreter::visit(const LambdaExpr *lambdaExpr) {
    SharedCallablePtr function = std::make_shared<LoxLambdaWrapper>(lambdaExpr, environment);
    LoxObject functionObject(function);
    return functionObject;
}

void Interpreter::visit(const ReturnStmt *returnStmt) {
    LoxObject value = LoxObject::Nil();
    if (returnStmt->expr.has_value()){
        value = interpret(returnStmt->expr.value().get());
    }

    /*NOTE: We're using exceptions as control flow here because it is the cleanest way to implement return given
    how the book implements the interpreter. This exception should be catched in the call method of LoxFunction*/
    throw ReturnException(value);
}


void Interpreter::visit(const ClassDeclStmt *classDeclStmt) {
    if (classDeclStmt->superclass.has_value()){
        LoxObject superclass = interpret(classDeclStmt->superclass.value().get());
//        if (superclass.)
    }



    environment->define(classDeclStmt->identifier, LoxObject::Nil());

    std::unordered_map<std::string, LoxObject> methods;
    for (const auto& method : classDeclStmt->methods){
        bool isConstructor = method->name.lexeme == "init";
        SharedCallablePtr callable = std::make_shared<LoxFunction>(method.get(), environment, isConstructor);
        LoxObject functionObject(callable);
        methods[method->name.lexeme] = functionObject;
    }

    SharedCallablePtr klass = std::make_shared<LoxClass>(classDeclStmt->identifier.lexeme, methods);
    LoxObject classObject(klass);
    environment->assign(classDeclStmt->identifier, classObject);
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

LoxObject Interpreter::visit(const IncrementExpr *incrementExpr) {
    LoxObject prev = interpret(incrementExpr->variable.get());
    LoxObject inc = prev + LoxObject(1.0);

    const VariableExpr *variableExpr = incrementExpr->variable.get();
    if (localsDistances.find(variableExpr) != localsDistances.end()){
        environment->assignAt(variableExpr->identifier, inc, localsDistances[variableExpr]);
    } else {
        globalEnv->assign(variableExpr->identifier, inc);
    }

    if (incrementExpr->type == IncrementExpr::Type::POSTFIX){
        return prev;
    }

    return inc;
}

LoxObject Interpreter::visit(const DecrementExpr *decrementExpr) {
    LoxObject prev = interpret(decrementExpr->variable.get());
    LoxObject dec = prev - LoxObject(1.0);

    const VariableExpr *variableExpr = decrementExpr->variable.get();
    if (localsDistances.find(variableExpr) != localsDistances.end()){
        environment->assignAt(variableExpr->identifier, dec, localsDistances[variableExpr]);
    } else {
        globalEnv->assign(variableExpr->identifier, dec);
    }

    if (decrementExpr->type == DecrementExpr::Type::POSTFIX){
        return prev;
    }
    return dec;
}

LoxObject Interpreter::visit(const LiteralExpr *literalExpr) {
    return literalExpr->literal;
}

LoxObject Interpreter::visit(const VariableExpr *variableExpr) {
    LoxObject obj = lookupVariable(variableExpr, variableExpr->identifier);
    return obj;
}

LoxObject Interpreter::lookupVariable(const Expr *variableExpr, const Token &identifier) {
    if (localsDistances.find(variableExpr) != localsDistances.end()){
        return environment->getAt(identifier, localsDistances[variableExpr]);
    }
    return globalEnv->get(identifier);
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

LoxObject Interpreter::visit(const CallExpr *callExpr) {
    LoxObject callee = interpret(callExpr->callee.get());

    std::vector<LoxObject> arguments;
    for (const UniqueExprPtr &arg : callExpr->arguments){
        arguments.push_back(interpret(arg.get()));
    }

    if (!callee.isCallable()){
        throw LoxRuntimeError("Expression is not callable", callExpr->closingParen.line);
    }
    LoxCallable* callable = callee.getCallable();
    if (arguments.size() != callable->arity()){
        std::stringstream ss;
        ss  << callable->name() << " expected " << callable->arity() << " argument(s) but instead got " << arguments.size();
        throw LoxRuntimeError(ss.str(), callExpr->closingParen.line);
    }

    return callable->call(*this, arguments);
}

LoxObject Interpreter::visit(const GetExpr *getExpr) {
    LoxObject obj = interpret(getExpr->expr.get());
    if (!obj.isClassInstance()){
        throw LoxRuntimeError("Only instances have properties", getExpr->identifier.line);
    }

    return obj.getClassInstance()->getProperty(getExpr->identifier);
}

LoxObject Interpreter::visit(const SetExpr *setExpr) {
    LoxObject obj = interpret(setExpr->object.get());
    if (!obj.isClassInstance()){
        throw LoxRuntimeError("Cannot access a field on something that isn't an object instance", setExpr->identifier.line);
    }

    LoxObject value = interpret(setExpr->value.get());
    obj.getClassInstance()->setProperty(setExpr->identifier, value);
    return value;
}

LoxObject Interpreter::visit(const ThisExpr *thisExpr) {
    return lookupVariable(thisExpr, thisExpr->keyword);
}

void Interpreter::executeBlock(const std::vector<UniqueStmtPtr> &stmts, Environment::SharedPtr newEnv) {
    ScopedEnvironment scope(environment, newEnv);
    for (auto const &stmt : stmts){
        execute(stmt.get());
    }
}

void Interpreter::loadBuiltinFunctions() {
    SharedCallablePtr clock = std::make_shared<standardFunctions::Clock>();
    SharedCallablePtr sleep = std::make_shared<standardFunctions::Sleep>();
    SharedCallablePtr str = std::make_shared<standardFunctions::Str>();

    std::vector<LoxObject> functions = {LoxObject(clock), LoxObject(sleep), LoxObject(str)};
    for (const auto &function : functions){
        globalEnv->define(function.getCallable()->name(), function);
    }

}





