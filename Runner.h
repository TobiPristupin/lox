#ifndef JLOX_RUNNER_H
#define JLOX_RUNNER_H
#include <string>
#include "Interpreter.h"

class Runner {
public:
    static void runScript(const std::string& filename);
    static void runRepl();
    static void displayLoxUsage();

private:
    static void runCode(const std::string& code);
    static Interpreter interpreter;
};

#endif
