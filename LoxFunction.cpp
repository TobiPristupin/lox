#include "LoxFunction.h"
#include <cassert>
#include <memory>
#include <sstream>
#include <utility>
#include "Expr.h"
#include "Interpreter.h"
#include "Stmt.h"
#include "Token.h"
#include "typedefs.h"
#include "LoxClass.h"

LoxFunction::LoxFunction(const FunctionDeclStmt *functionDeclStmt, Environment::SharedPtr closure, bool isConstructor)
    : LoxCallable(CallableType::FUNCTION), functionDeclStmt(functionDeclStmt), closure(std::move(closure)), isConstructor(isConstructor) {}


LoxObject LoxFunction::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    Environment::SharedPtr newEnv = std::make_shared<Environment>(closure);
    assert(functionDeclStmt->params.size() == arguments.size()); //This should have already been checked by the interpreter
    for (int i = 0; i < arguments.size(); i++){
        newEnv->define(functionDeclStmt->params[i], arguments[i]);
    }

    try {
        interpreter.executeBlock(functionDeclStmt->body, newEnv);
    } catch (const ReturnException &returnStmt) {
        /*NOTE: We're using exceptions as control flow here because it is the cleanest way to implement return given
        how the book implements the interpreter. This exception was thrown in the visitReturnStmt method of the interpreter*/

        //Constructor should always implicitly return "this".
        if (isConstructor) return closure->getAt("this", 0);

        return returnStmt.value;
    }


    if (isConstructor) {
        //Constructor should always implicitly return "this". This line covers the case where the constructor has no return stmt
        //but we still need to return "this".
        return closure->getAt("this", 0);
    }

    return LoxObject::Nil();
}

LoxFunction *LoxFunction::bindThis(SharedInstancePtr instance) {
    Environment::SharedPtr newEnv = std::make_shared<Environment>(closure);
    LoxObject instanceObj(std::move(instance));
    newEnv->define("this", instanceObj);
    return new LoxFunction(functionDeclStmt, newEnv, isConstructor);
}

int LoxFunction::arity() {
    return functionDeclStmt->params.size();
}

std::string LoxFunction::to_string() {
    return "<function " + name() + ">";
}

std::string LoxFunction::name() {
    return functionDeclStmt->name.lexeme;
}


LoxLambdaWrapper::LoxLambdaWrapper(const LambdaExpr *lambdaExpr, Environment::SharedPtr closure)
    : LoxCallable(CallableType::FUNCTION), lambdaExpr(lambdaExpr), closure(std::move(closure)) {}

LoxObject LoxLambdaWrapper::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    Environment::SharedPtr newEnv = std::make_shared<Environment>(closure);
    assert(lambdaExpr->params.size() == arguments.size()); //This should have already been checked by the interpreter
    for (int i = 0; i < arguments.size(); i++){
        newEnv->define(lambdaExpr->params[i], arguments[i]);
    }


    return interpreter.interpret(lambdaExpr->body.get(), newEnv);
}

int LoxLambdaWrapper::arity() {
    return lambdaExpr->params.size();
}

std::string LoxLambdaWrapper::to_string() {
    return "<function " + name() + ">";
}

std::string LoxLambdaWrapper::name() {
    std::stringstream ss;
    ss << "lambda at " << lambdaExpr;
    return ss.str();
}
