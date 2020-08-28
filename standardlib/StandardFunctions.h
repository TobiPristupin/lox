#ifndef JLOX_STANDARDFUNCTIONS_H
#define JLOX_STANDARDFUNCTIONS_H

#include <string>
#include <vector>
#include "../LoxCallable.h"
#include "../LoxObject.h"
class Interpreter;

namespace standardFunctions {

    class Clock : public LoxCallable {
    public:
        Clock();
        LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
        int arity() override;
        std::string to_string() override;
        std::string name() override;
    };

    class Sleep : public LoxCallable {
    public:
        Sleep();
        LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
        int arity() override;
        std::string to_string() override;
        std::string name() override;
    };

    class Str : public LoxCallable {
    public:
        Str();
        LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
        int arity() override;
        std::string to_string() override;
        std::string name() override;
    };


}


#endif //JLOX_STANDARDFUNCTIONS_H
