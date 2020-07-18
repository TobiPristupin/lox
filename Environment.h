#ifndef JLOX_ENVIRONMENT_H
#define JLOX_ENVIRONMENT_H


#include <unordered_map>
#include <string>
#include "Token.h"
#include "LoxObject.h"

class Environment {
public:


    Environment(Environment* parent = nullptr);
    void define(const Token &identifier, const LoxObject &val);
    void define(const std::string &key, const LoxObject &val);
    LoxObject get(const Token &identifier);
    void assign(const Token &identifier, const LoxObject &val);
    Environment* parent();

private:
    Environment* parentEnv;
    std::unordered_map<std::string, LoxObject> variables;
};


#endif //JLOX_ENVIRONMENT_H
