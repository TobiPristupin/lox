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


void Runner::runScript(const std::string& filename) {
    FileReader reader(filename);
    runCode(reader.readAll());
}

void Runner::runRepl() {
    std::cout << "Interactive Repl mode. Type \"quit()\" or press CTRL-C to exit\n";
    std::string line;
    while (true){
        std::cout << "< ";
        std::getline(std::cin, line);
        if (line == "quit()") return;
        try {
            runCode(line);
        } catch (const LoxError &exception){
            std::cerr << exception.what() << "\n";
        }
    }
}

void Runner::runCode(const std::string& code) {
    Scanner scanner(code);
    std::vector<Token> tokens = scanner.scanTokens();
    Parser parser(tokens);
    Expr *expr = parser.parse();
    Interpreter interpreter;
    lox_literal_t result = interpreter.interpret(expr);
    std::cout << literalToString(result) << "\n";


    //    for (Token t : tokens){
    //        std::cout << t.to_string() << "\n";
    //    }

    bool error = false;
    if (error) {
        throw LoxError("Program terminated with an error");
    }

}

void Runner::displayLoxUsage(){
    std::cout << "Usage: jlox [script]\n";
}
