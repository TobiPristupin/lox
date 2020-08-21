#ifndef JLOX_LOXCALLABLE_H
#define JLOX_LOXCALLABLE_H


#include <string>
#include <vector>

class LoxObject;
class Interpreter;

class LoxCallable {
public:
    virtual ~LoxCallable() = default;
    virtual LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) = 0;
    virtual int arity() = 0;
    virtual std::string to_string() = 0;
    virtual std::string name() = 0;
};

#endif //JLOX_LOXCALLABLE_H
