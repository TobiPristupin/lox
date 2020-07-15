#include "Environment.h"
#include "LoxError.h"
#include "LoxObject.h"

Environment::Environment(Environment *parent) : parentEnv(parent) {}

LoxObject Environment::get(const Token &identifier) {
    std::string key = identifier.lexeme;
    if (variables.count(key) == 1){
        return variables[key];
    }

    if (parentEnv == nullptr){ //This is the outermost environment
        throw LoxRuntimeError("Undefined variable '" + key + "'", identifier.line);
    }

    return parentEnv->get(identifier);
}

void Environment::define(const Token &identifier, const LoxObject &val) {
    std::string key = identifier.lexeme;
    if (variables.count(key) == 1){
        throw LoxRuntimeError("Cannot redefine a variable. Variable '" + key + "' has already been defined", identifier.line);
    }

    variables[key] = val;
}

void Environment::assign(const Token &identifier, const LoxObject &val) {
    std::string key = identifier.lexeme;
    if (variables.count(key) == 1){
        variables[key] = val;
        return;
    }

    if (parentEnv == nullptr){ //This is the outermost environment
        throw LoxRuntimeError("Undefined variable '" + key + "'", identifier.line);
    }

    parentEnv->assign(identifier, val);
}

Environment *Environment::parent() {
    return parentEnv;
}

