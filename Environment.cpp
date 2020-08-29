#include "Environment.h"
#include <cassert>
#include <stdexcept>
#include <utility>
#include "LoxError.h"
#include "LoxObject.h"
#include "Token.h"


Environment::Environment(Environment::SharedPtr parent) : parentEnv(std::move(parent)) {}

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

LoxObject Environment::getAt(const Token &identifier, int distance) {
    return getAt(identifier.lexeme, distance);
}

LoxObject Environment::getAt(const std::string &key, int distance) {
    Environment* env = ancestor(distance);
    if (env->variables.count(key) == 0){
        throw std::runtime_error("Variable does not exist. Bug in resolver, this should not be happening");
    }

    return env->variables[key];
}

void Environment::define(const Token &identifier, const LoxObject &val) {
    std::string key = identifier.lexeme;
    if (variables.count(key) == 1){
        throw LoxRuntimeError("Cannot redefine a variable. Variable '" + key + "' has already been defined", identifier.line);
    }

    variables[key] = val;
}

void Environment::define(const std::string &key, const LoxObject &val) {
    if (variables.count(key) == 1){
        throw LoxRuntimeError("Cannot redefine a variable. Variable '" + key + "' has already been defined");
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

void Environment::assignAt(const Token &identifier, const LoxObject &val, int distance) {
    Environment* env = ancestor(distance);
    std::string key = identifier.lexeme;
    if (env->variables.count(key) == 0){
        throw std::runtime_error("Undefined variable when assigning. Bug in the Resolver, this should not be happening");
    }

    env->variables[key] = val;
}

Environment::SharedPtr Environment::parent() {
    return parentEnv;
}

Environment* Environment::ancestor(int distance) {
    Environment* currentEnv = this;
    for (int i = 0; i < distance; i++){
        assert(currentEnv->parent() != nullptr);
        currentEnv = currentEnv->parent().get();
    }

    return currentEnv;
}


ScopedEnvironment::ScopedEnvironment(Environment::SharedPtr &currentEnv, Environment::SharedPtr newEnv) : mainReference(currentEnv), copyOfPreviousEnv(currentEnv) {
    mainReference = std::move(newEnv);
}

ScopedEnvironment::~ScopedEnvironment() {
    mainReference = copyOfPreviousEnv;
}