#ifndef JLOX_ENVIRONMENT_H
#define JLOX_ENVIRONMENT_H


#include <unordered_map>
#include "Token.h"

class Environment {
public:
    void define(const Token &identifier, const lox_literal_t &val);
    lox_literal_t get(const Token &identifier);
    void assign(const Token &identifier, const lox_literal_t &val);

private:
    std::unordered_map<std::string, lox_literal_t> variables;
};


#endif //JLOX_ENVIRONMENT_H
