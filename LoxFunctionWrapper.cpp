#include <cassert>
#include "LoxFunctionWrapper.h"

LoxObject LoxFunctionWrapper::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    Environment::SharedPtr newEnv = std::make_shared<Environment>(interpreter.globalEnv);
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
