#include <cassert>
#include "LoxFunctionWrapper.h"

LoxObject LoxFunctionWrapper::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    Environment::SharedPtr newEnv = std::make_shared<Environment>(interpreter.globalEnv);
    assert(functionDeclStmt->params.size() == arguments.size()); //This should have aleady been checked.
    for (int i = 0; i < arguments.size(); i++){
        newEnv->define(functionDeclStmt->params[i], arguments[i]);
    }

    interpreter.executeBlock(functionDeclStmt->body, newEnv);
    return LoxObject();
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
