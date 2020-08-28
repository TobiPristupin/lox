#ifndef JLOX_LOXCALLABLE_H
#define JLOX_LOXCALLABLE_H


#include <string>
#include <vector>

class LoxObject;
class Interpreter;


class LoxCallable {
public:
    enum class CallableType {
        FUNCTION, CLASS
    };

    CallableType type;

    virtual ~LoxCallable() = default;
    virtual LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) = 0;
    virtual int arity() = 0;
    virtual std::string to_string() = 0;
    virtual std::string name() = 0;

protected:
    explicit LoxCallable(CallableType type) : type(type) {};
};

#endif //JLOX_LOXCALLABLE_H
