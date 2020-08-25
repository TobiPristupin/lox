#include "LoxFunctionWrapper.h"
#include <cassert>
#include <memory>
#include <sstream>
#include <utility>
#include "Expr.h"
#include "Interpreter.h"
#include "Stmt.h"
#include "Token.h"
#include "typedefs.h"

LoxFunctionWrapper::LoxFunctionWrapper(const FunctionDeclStmt *functionDeclStmt, Environment::SharedPtr closure)  : functionDeclStmt(functionDeclStmt), closure(std::move(closure)) {}


LoxObject LoxFunctionWrapper::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    Environment::SharedPtr newEnv = std::make_shared<Environment>(closure);
    assert(functionDeclStmt->params.size() == arguments.size()); //This should have already been checked.
    for (int i = 0; i < arguments.size(); i++){
        newEnv->define(functionDeclStmt->params[i], arguments[i]);
    }

    try {
        interpreter.executeBlock(functionDeclStmt->body, newEnv);
    } catch (const ReturnException &returnStmt) {
        /*NOTE: We're using exceptions as control flow here because it is the cleanest way to implement return given
        how the book implements the interpreter. This exception was thrown in the visitReturnStmt method of the interpreter*/
        return returnStmt.value;
    }

    return LoxObject::Nil();
}

int LoxFunctionWrapper::arity() {
    return functionDeclStmt->params.size();
}

std::string LoxFunctionWrapper::to_string() {
    return "<function " + name() + ">";
}

std::string LoxFunctionWrapper::name() {
    return functionDeclStmt->name.lexeme;
}


LoxLambdaWrapper::LoxLambdaWrapper(const LambdaExpr *lambdaExpr, Environment::SharedPtr closure) : lambdaExpr(lambdaExpr), closure(std::move(closure)) {}

LoxObject LoxLambdaWrapper::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    Environment::SharedPtr newEnv = std::make_shared<Environment>(closure);
    assert(lambdaExpr->params.size() == arguments.size()); //This should have already been checked.
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
