#include <fstream>
#include <iostream>
#include "Runner.h"
#include "Scanner.h"
#include "LoxException.h"
#include "Parser.h"
#include "FileReader.h"


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
        runCode(line);
    }
}

void Runner::runCode(const std::string& code) {
    Scanner scanner(code);
    std::vector<Token> tokens = scanner.scanTokens();
    for (Token t : tokens){
        std::cout << t.to_string() << "\n";
    }

//    Parser parser(tokens);
//    Expression* expr = parser.parse();
//    BinaryExpr* binary = dynamic_cast<BinaryExpr*>(expr);
//    std::cout << binary->op->to_string() << std::endl;
//
//
//    bool error = false;
//    if (error){
//        throw LoxException("Program terminated with an error");
//    }
}

void Runner::displayLoxUsage(){
    std::cout << "Usage: jlox [script]\n";
}
