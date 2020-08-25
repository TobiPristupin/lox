#include "Runner.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include "FileReader.h"
#include "Interpreter.h"
#include "LoxError.h"
#include "Parser.h"
#include "Resolver.h"
#include "Scanner.h"
#include "Token.h"
#include "typedefs.h"

class Expr;


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
            runCode(line, true);
        } catch (const LoxError &exception){
            std::cout << exception.what() << "\n"; //use cout instead of cerr to avoid the two streams not being synchronized when printing the next '< '
        }
    }
}

int Runner::runCode(const std::string& code, bool replMode) {
    Scanner scanner(code);
    std::vector<Token> tokens;

    try {
        tokens = scanner.scanTokens();
    } catch (const LoxScanningError& exception) {
        std::cout << exception.what() << "\n";
        return 65;
    }


    Parser parser(tokens);
    /*Because the parser can keep parsing after multiple errors instead of exiting at the first error, it has its own
    exception handling functionality baked into it, and the caller only has to worry about success or not.*/
    bool parsingSuccess = true;
    std::vector<UniqueStmtPtr> statements = parser.parse(parsingSuccess);
    if (!parsingSuccess){
        return 65;
    }

    Resolver resolver;
    std::unordered_map<const Expr*, int> distances;
    /*Because the resolver can keep going after multiple errors instead of exiting at the first error, it has its own
    exception handling functionality baked into it, and the caller only has to worry about success or not.*/
    bool resolvingSuccess = false;
    distances = resolver.resolve(statements, resolvingSuccess);
    if (!resolvingSuccess){
        return 65;
    }



    try {
        interpreter.interpret(statements, distances, replMode);
    } catch (const LoxRuntimeError &exception) {
        std::cout << exception.what() << "\n";
        return 70;
    }

    return 0;
}

void Runner::displayLoxUsage(){
    std::cout << "Usage: jlox [script]\n";
}
