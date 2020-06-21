#include "Environment.h"
#include "LoxError.h"

lox_literal_t Environment::get(const Token &identifier) {
    std::string key = identifier.lexeme;
    if (variables.count(key) == 0){
        throw LoxRuntimeError("Undefined variable '" + key + "'", identifier.line);
    }

    return variables[key];
}

void Environment::define(const Token &identifier, const lox_literal_t &val) {
    std::string key = identifier.lexeme;
    if (variables.count(key) == 1){
        throw LoxRuntimeError("Cannot redefine a variable. Variable '" + key + "' has already been defined", identifier.line);
    }

    variables[key] = val;
}

void Environment::assign(const Token &identifier, const lox_literal_t &val) {
    std::string key = identifier.lexeme;
    if (variables.count(key) == 0){
        throw LoxRuntimeError("Undefined variable '" + key + "'", identifier.line);
    }

    variables[key] = val;
}

