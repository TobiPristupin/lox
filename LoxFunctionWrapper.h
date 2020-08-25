#ifndef JLOX_LOXFUNCTIONWRAPPER_H
#define JLOX_LOXFUNCTIONWRAPPER_H

#include <string>
#include <vector>
#include "Environment.h"
#include "LoxCallable.h"
#include "LoxObject.h"

class FunctionDeclStmt;
class Interpreter;
class LambdaExpr;

//This class wraps a FunctionDeclStmt into a LoxCallable. Basically it acts as the intermediary between the parser and the interpreter.
class LoxFunctionWrapper : public LoxCallable {
public:
    //LoxFunctionWrapper does not own the stmt, it only uses it. All statements are owned by Runner.cpp by using unique_ptrs
    const FunctionDeclStmt* functionDeclStmt;
    Environment::SharedPtr closure;

    LoxFunctionWrapper(const FunctionDeclStmt* functionDeclStmt, Environment::SharedPtr closure);
    LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
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


#endif //JLOX_LOXFUNCTIONWRAPPER_H
