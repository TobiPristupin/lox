#include "LoxFunctionWrapper.h"

LoxObject LoxFunctionWrapper::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    return LoxObject(name());
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
