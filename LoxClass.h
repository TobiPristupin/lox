#ifndef JLOX_LOXCLASS_H
#define JLOX_LOXCLASS_H


#include <string>
#include <memory>
#include <unordered_map>
#include "LoxCallable.h"
#include "LoxObject.h"

class LoxClassWrapper : public LoxCallable, public std::enable_shared_from_this<LoxClassWrapper> {

public:
    std::unordered_map<std::string, LoxObject> methods;
    std::string className;

    explicit LoxClassWrapper(const std::string &name, const std::unordered_map<std::string, LoxObject> &methods);
    LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
    int arity() override;
    std::string to_string() override;
    std::string name() override;

};

class LoxClassInstance {

public:
    explicit LoxClassInstance(std::shared_ptr<LoxClassWrapper> loxClass);
    LoxObject getProperty(const Token &identifier);
    void setProperty(const Token &identifier, const LoxObject &value);
    std::string to_string();

private:
    std::shared_ptr<LoxClassWrapper> loxClass;
    std::unordered_map<std::string, LoxObject> fields;

    std::optional<LoxObject> findMethod(const std::string &key);
};


#endif //JLOX_LOXCLASS_H
