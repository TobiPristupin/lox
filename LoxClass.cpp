#include <iostream>
#include <utility>
#include <sstream>
#include "LoxClass.h"
#include "LoxObject.h"
#include "LoxError.h"


LoxClassWrapper::LoxClassWrapper(const std::string &name, const std::unordered_map<std::string, LoxObject> &methods)
    : className(name), methods(methods) {}

LoxObject LoxClassWrapper::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    SharedInstancePtr instance = std::make_shared<LoxClassInstance>(shared_from_this());
    LoxObject instanceObj(instance);
    return instanceObj;
}

int LoxClassWrapper::arity() {
    return 0;
}

std::string LoxClassWrapper::to_string() {
    return "<class " + name() + ">";
}

std::string LoxClassWrapper::name() {
    return className;
}


LoxClassInstance::LoxClassInstance(std::shared_ptr<LoxClassWrapper> loxClass) : loxClass(std::move(loxClass)) {}

LoxObject LoxClassInstance::getProperty(const Token &identifier) {
    std::string key = identifier.lexeme;
    if (fields.find(key) != fields.end()){
        return fields[key];
    }

    std::optional<LoxObject> method = findMethod(key);
    if (method.has_value()){
        return method.value();
    }

    throw LoxRuntimeError("Undefined property '" + key + "'", identifier.line);
}

void LoxClassInstance::setProperty(const Token &identifier, const LoxObject &value) {
    fields[identifier.lexeme] = value;
}

std::optional<LoxObject> LoxClassInstance::findMethod(const std::string &key) {
    if (loxClass->methods.find(key) != loxClass->methods.end()){
        return loxClass->methods[key];
    }

    return std::nullopt;
}

std::string LoxClassInstance::to_string() {
    std::stringstream ss;
    ss << "<Instance of class " << loxClass->name() << " at " << this << ">";
    return ss.str();
}
