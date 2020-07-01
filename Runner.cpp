#include <fstream>
#include <iostream>
#include "Runner.h"
#include "Scanner.h"
#include "LoxError.h"
#include "Parser.h"
#include "FileReader.h"
#include "tools/AstPrinter.h"
#include "Interpreter.h"
#include "tools/utils.h"


Interpreter Runner::interpreter = Interpreter();

int Runner::runScript(const std::string& filename) {
    FileReader reader(filename);
    return runCode(reader.readAll());
}

int Runner::runRepl() {
    std::cout << "Interactive Repl mode. Type \"quit()\" or press CTRL-C to exit\n";
    std::string line;
    while (true){
        std::cout << "< ";
        std::getline(std::cin, line);
        if (line == "quit()") return 0;
        try {
            runCode(line);
        } catch (const LoxError &exception){
            std::cout << exception.what() << "\n"; //use cout instead of cerr to avoid the two streams not being synchronized when printing the next '< '
        }
    }
}

int Runner::runCode(const std::string& code) {
    Scanner scanner(code);
    std::vector<Token> tokens;

    try {
        tokens = scanner.scanTokens();
    } catch (const LoxScanningError& exception) {
        std::cerr << exception.what() << "\n";
        return 65;
    }

    /*Because the parser can keep parsing after multiple errors instead of exiting at the first error, it has its own
    exception handling functionality baked into it, and the caller only has to worry about success or not.*/
    Parser parser(tokens);
    bool successFlag = false;
    std::vector<UniqueStmtPtr> statements = parser.parse(successFlag);

    if (!successFlag){
        return 65;
    }

    try {
        interpreter.interpret(statements);
    } catch (const LoxRuntimeError &exception) {
        std::cerr << exception.what() << "\n";
        return 70;
    }

    return 0;
}

void Runner::displayLoxUsage(){
    std::cout << "Usage: jlox [script]\n";
}
