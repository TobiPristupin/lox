#ifndef JLOX_RUNNER_H
#define JLOX_RUNNER_H
#include <string>

class Runner {
public:
    static void runScript(const std::string& filename);
    static void runRepl();
    static void displayLoxUsage();

private:
    static void runCode(const std::string& code);
};

#endif
