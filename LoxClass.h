#ifndef JLOX_LOXCLASS_H
#define JLOX_LOXCLASS_H


#include <string>
#include <memory>
#include "LoxCallable.h"

class LoxClassWrapper : public LoxCallable, public std::enable_shared_from_this<LoxClassWrapper> {
public:
    std::string className;

    explicit LoxClassWrapper(const std::string &name);

    LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
    int arity() override;
    std::string to_string() override;
    std::string name() override;

};

class LoxClassInstance {
public:
    std::shared_ptr<LoxClassWrapper> loxClass;

    explicit LoxClassInstance(std::shared_ptr<LoxClassWrapper> loxClass);
    std::string to_string();
};


#endif //JLOX_LOXCLASS_H
