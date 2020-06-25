#ifndef JLOX_ENVIRONMENT_H
#define JLOX_ENVIRONMENT_H


#include <unordered_map>
#include "Token.h"

class Environment {
public:


    Environment(Environment* parent = nullptr);
    void define(const Token &identifier, const lox_literal_t &val);
    lox_literal_t get(const Token &identifier);
    void assign(const Token &identifier, const lox_literal_t &val);
    Environment* parent();

private:
    Environment* parentEnv;
    std::unordered_map<std::string, lox_literal_t> variables;
};


#endif //JLOX_ENVIRONMENT_H
