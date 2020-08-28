#include "LoxClass.h"
#include <iostream>     // for operator<<, basic_ostream, stringstream, basi...
#include <utility>      // for move
#include <sstream>      // for move
#include "LoxError.h"   // for LoxRuntimeError
#include "LoxObject.h"  // for LoxObject, SharedInstancePtr
#include "Token.h"      // for Token
#include "LoxFunction.h"


class Interpreter;


LoxClass::LoxClass(const std::string &name, const std::unordered_map<std::string, LoxObject> &methods)
    : className(name), methods(methods) {}

LoxObject LoxClass::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    SharedInstancePtr instance = std::make_shared<LoxClassInstance>(shared_from_this());
    std::optional<LoxObject> constructor = findMethod("init");
    if (constructor.has_value()){
        LoxFunction *function = dynamic_cast<LoxFunction*>(constructor.value().getCallable());

        //Create a new version of the constructor with "this" bound
        LoxFunction *newFunction = function->bindThis(instance);
        //call the constructor
        newFunction->call(interpreter, arguments);
        //Once we call the constructor we no longer need the newFunction so delete it before it leaks.
        delete newFunction;
    }

    LoxObject instanceObj(instance);
    return instanceObj;
}

std::optional<LoxObject> LoxClass::findMethod(const std::string &key) {
    if (methods.find(key) != methods.end()){
        return methods[key];
    }

    return std::nullopt;
}

int LoxClass::arity() {
    std::optional<LoxObject> constructor = findMethod("init");
    if (constructor.has_value()){
        return constructor->getCallable()->arity();
    }

    return 0;
}

std::string LoxClass::to_string() {
    return "<class " + name() + ">";
}

std::string LoxClass::name() {
    return className;
}


LoxClassInstance::LoxClassInstance(std::shared_ptr<LoxClass> loxClass) : loxClass(std::move(loxClass)) {}

LoxObject LoxClassInstance::getProperty(const Token &identifier) {
    std::string key = identifier.lexeme;
    if (fields.find(key) != fields.end()){
        return fields[key];
    }

    std::optional<LoxObject> method = loxClass->findMethod(key);
    if (method.has_value()){
        LoxFunction *function = dynamic_cast<LoxFunction*>(method.value().getCallable());
        //Create a new function where the variable "this" is binded to this instance
        SharedCallablePtr newFunction(function->bindThis(shared_from_this()));
        LoxObject newFunctionObject(newFunction);
        return newFunctionObject;
    }

    throw LoxRuntimeError("Undefined property '" + key + "'", identifier.line);
}

void LoxClassInstance::setProperty(const Token &identifier, const LoxObject &value) {
    fields[identifier.lexeme] = value;
}

std::string LoxClassInstance::to_string() {
    std::stringstream ss;
    ss << "<Instance of class " << loxClass->name() << " at " << this << ">";
    return ss.str();
}
