#include <fstream>
#include <iostream>
#include "Runner.h"
#include "ErrorLogger.h"

void Runner::runScript(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()){
        ErrorLogger::error("File " + filename + " not found");
        return;
    }

    std::string data((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    file.close();

    runCode(data);
}

void Runner::runRepl() {
    std::cout << "Interactive Repl mode. Type \"quit()\" or press CTRL-C to exit\n";
    std::string line;
    while (true){
        std::cout << "< ";
        std::getline(std::cin, line);
        if (line == "quit()") return;
        runCode(line);
    }
}

void Runner::runCode(const std::string& code) {
    std::cout << "Running code :\n" << code << "\n";

    bool error = false;
    if (error){
        ErrorLogger::error("Program terminated with an error");
    }
}

void Runner::displayLoxUsage(){
    std::cout << "Usage: jlox [script]\n";
}
