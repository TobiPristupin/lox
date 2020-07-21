#ifndef JLOX_LOXFUNCTIONWRAPPER_H
#define JLOX_LOXFUNCTIONWRAPPER_H

#include "LoxCallable.h"

//This class wraps a FunctionDeclStmt into a LoxCallable. Basically it acts as the intermediary between the parser and the interpreter.
class LoxFunctionWrapper : public LoxCallable {
public:
    //LoxFunctionWrapper does not own the stmt, it only uses it. All statements are owned by Runner.cpp by using unique_ptrs
    const FunctionDeclStmt* functionDeclStmt;

    explicit LoxFunctionWrapper(const FunctionDeclStmt* stmt) : functionDeclStmt(stmt){};
    LoxObject call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) override;
    int arity() override;
    std::string to_string() override;
    std::string name() override;

};


#endif //JLOX_LOXFUNCTIONWRAPPER_H
