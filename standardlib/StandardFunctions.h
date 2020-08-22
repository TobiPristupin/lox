#ifndef JLOX_STANDARDFUNCTIONS_H
#define JLOX_STANDARDFUNCTIONS_H

#include <string>
#include "../LoxObject.h"
#include "../LoxCallable.h"
#include "../Interpreter.h"

namespace standardFunctions {

    class Clock : public LoxCallable {
    public:
        LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
        int arity() override;
        std::string to_string() override;
        std::string name() override;
    };

    class Sleep : public LoxCallable {
    public:
        LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
        int arity() override;
        std::string to_string() override;
        std::string name() override;
    };

    class Str : public LoxCallable {
    public:
        LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
        int arity() override;
        std::string to_string() override;
        std::string name() override;
    };


}


#endif //JLOX_STANDARDFUNCTIONS_H
