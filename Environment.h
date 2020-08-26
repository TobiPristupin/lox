#ifndef JLOX_ENVIRONMENT_H
#define JLOX_ENVIRONMENT_H


#include <memory>
#include <string>
#include <unordered_map>
#include "LoxObject.h"

struct Token;

class Environment {
public:

    using SharedPtr = std::shared_ptr<Environment>;
    explicit Environment(Environment::SharedPtr parent = nullptr);

    //Use the Token overload because it can then report errors using the token's line. Only use the string overload when there's no token.
    void define(const Token &identifier, const LoxObject &val);
    void define(const std::string &key, const LoxObject &val);

    LoxObject get(const Token &identifier);

    //Use the Token overload because it can then report errors using the token's line. Only use the string overload when there's no token.
    LoxObject getAt(const Token &identifier, int distance);
    LoxObject getAt(const std::string &key, int distance);

    void assign(const Token &identifier, const LoxObject &val);
    void assignAt(const Token &identifier, const LoxObject &val, int distance);

    Environment::SharedPtr parent();

private:
    Environment::SharedPtr parentEnv;
    std::unordered_map<std::string, LoxObject> variables;

    Environment* ancestor(int distance);
};

//This class uses a little bit of magic with references to set the environment of the caller to
//a new environment and then restore it to the previous environment when it goes out of scope.
class ScopedEnvironment {
public:
    ScopedEnvironment(Environment::SharedPtr &currentEnv, Environment::SharedPtr newEnv);
    ~ScopedEnvironment();

private:
    //This is the reference to the interpreters environment
    Environment::SharedPtr &mainReference;
    Environment::SharedPtr copyOfPreviousEnv;

};


#endif //JLOX_ENVIRONMENT_H
