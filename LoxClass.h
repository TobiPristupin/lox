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
    /*Ideally the type of superclass should be std::optional<std::shared_ptr<LoxClass>> because the superclass will always be a LoxClass.
     * Instead we are using SharedCallablePtr which may actually be a LoxClass OR a LoxFunction as both inherit from the Callable class.
     * I tried to solve this by creating a SharedFunctionPtr and a SharedClassPtr in order to be able to distinguish between the two but it
     * caused big problems in other parts. I guess this is what happens when trying to port the weak type system used in the
     * book into C++ type system. As a compromise we are using SharedCallablePtr and checking in the constructor that the correct type
     * is used (LoxClass and not LoxFunction)
     * */
    std::optional<SharedCallablePtr> superclass;
    std::unordered_map<std::string, LoxObject> methods;
    std::string className;

    explicit LoxClass(const std::string &name, const std::unordered_map<std::string, LoxObject> &methods, std::optional<SharedCallablePtr> superclass);
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
