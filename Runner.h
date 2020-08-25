#ifndef JLOX_RUNNER_H
#define JLOX_RUNNER_H
#include <string>

class Interpreter;

class Runner {
public:
    //returns exit code
    static int runScript(const std::string& filename);
    static int runRepl();
    static void displayLoxUsage();

private:
    static int runCode(const std::string& code, bool replMode = false);
    static Interpreter interpreter;
};

#endif
