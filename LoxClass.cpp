#include "LoxClass.h"
#include <iostream>     // for operator<<, basic_ostream, stringstream, basi...
#include <utility>      // for move
#include <sstream>      // for move
#include "LoxError.h"   // for LoxRuntimeError
#include "LoxObject.h"  // for LoxObject, SharedInstancePtr
#include "Token.h"      // for Token
#include "LoxFunctionWrapper.h"


class Interpreter;


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
        //Trying to stay close to the book's Java implementation while porting it to C++ and maintaining type safety
        // (as explained in a comment in LoxObject.h) has lead to some pretty contrived code here.

        //To implement usage of the "this" keyword, every time a method is accessed with the "." operator we retrieve the method,
        //create a new environment whose parent is the method's closure and bind "this" to this current instance. Then we create
        //a new method that is a copy of the one we retrieved but uses this new environment. We have to create a new method each
        //time because the same method may be called from two different instances.

        //Cast the LoxObject into its LoxFunction representation
        LoxFunctionWrapper *function = dynamic_cast<LoxFunctionWrapper*>(method.value().getCallable());

        //Create a new environment that has the function's closure as its parent
        Environment::SharedPtr newEnv = std::make_shared<Environment>(function->closure);

        //Create a LoxObject that contains this instance
        LoxObject instanceObject(shared_from_this());
        //In the new env we created, bind "this" to this instance
        newEnv->define("this", instanceObject);

        //Create a new function that is a copy of "function" but with the new env.
        SharedCallablePtr newFunction = std::make_shared<LoxFunctionWrapper>(function->functionDeclStmt, newEnv);
        LoxObject newFunctionObject(newFunction);
        return newFunctionObject;
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
