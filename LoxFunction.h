#ifndef JLOX_LOXFUNCTION_H
#define JLOX_LOXFUNCTION_H

#include <string>
#include <vector>
#include "Environment.h"
#include "LoxCallable.h"
#include "LoxObject.h"

class FunctionDeclStmt;
class Interpreter;
class LambdaExpr;

//This class wraps a FunctionDeclStmt into a LoxCallable. Basically it acts as the intermediary between the parser and the interpreter.
class LoxFunction : public LoxCallable {
public:
    //LoxFunction does not own the stmt, it only uses it. All statements are owned by Runner.cpp by using unique_ptrs
    const FunctionDeclStmt* functionDeclStmt;
    Environment::SharedPtr closure;
    bool isConstructor;

    LoxFunction(const FunctionDeclStmt* functionDeclStmt, Environment::SharedPtr closure, bool isConstructor = false);
    LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
    //Creates a NEW LoxFunction that is a copy of the current LoxFunction but with a different closure where "this" is binded to an instance;
    LoxFunction* bindThis(SharedInstancePtr instance);
    int arity() override;
    std::string to_string() override;
    std::string name() override;

};

//This class wraps a LambdaExpr into a LoxCallable. Basically it acts as the intermediary between the parser and the interpreter.
class LoxLambdaWrapper : public LoxCallable {
public:

    const LambdaExpr* lambdaExpr;
    Environment::SharedPtr closure;

    LoxLambdaWrapper(const LambdaExpr* lambdaExpr, Environment::SharedPtr closure);
    LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
    int arity() override;
    std::string to_string() override;
    std::string name() override;

};


#endif //JLOX_LOXFUNCTION_H
