#include <iostream>
#include <utility>
#include <sstream>
#include "LoxClass.h"
#include "LoxObject.h"


LoxClassWrapper::LoxClassWrapper(const std::string &name) : className(name) {}

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

std::string LoxClassInstance::to_string() {
    std::stringstream ss;
    ss << "<Instance of class " << loxClass->name() << " at " << this << ">";
    return ss.str();
}
