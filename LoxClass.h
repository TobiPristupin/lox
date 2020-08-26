#ifndef JLOX_LOXCLASS_H
#define JLOX_LOXCLASS_H


#include <memory>         // for shared_ptr, enable_shared_from_this
#include <optional>       // for optional
#include <string>         // for string
#include <unordered_map>  // for unordered_map
#include <vector>         // for vector
#include "LoxCallable.h"  // for LoxCallable
#include "LoxObject.h"    // for LoxObject
class Interpreter;
struct Token;

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

class LoxClassInstance : public std::enable_shared_from_this<LoxClassInstance> {

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
