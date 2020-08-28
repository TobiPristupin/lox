#ifndef JLOX_LOXCLASS_H
#define JLOX_LOXCLASS_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "LoxCallable.h"
#include "LoxObject.h"
class Interpreter;
struct Token;

class LoxClass : public LoxCallable, public std::enable_shared_from_this<LoxClass> {

public:
    std::unordered_map<std::string, LoxObject> methods;
    std::string className;

    explicit LoxClass(const std::string &name, const std::unordered_map<std::string, LoxObject> &methods);
    LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
    std::optional<LoxObject> findMethod(const std::string &key);
    int arity() override;
    std::string to_string() override;
    std::string name() override;

};

class LoxClassInstance : public std::enable_shared_from_this<LoxClassInstance> {

public:
    explicit LoxClassInstance(std::shared_ptr<LoxClass> loxClass);
    LoxObject getProperty(const Token &identifier);
    void setProperty(const Token &identifier, const LoxObject &value);
    std::string to_string();

private:
    std::shared_ptr<LoxClass> loxClass;
    std::unordered_map<std::string, LoxObject> fields;

};


#endif //JLOX_LOXCLASS_H
