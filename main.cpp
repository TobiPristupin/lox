#include <iostream>
#include "Runner.h"
#include "LoxException.h"

int main(int argc, char *argv[]) {
    if (argc > 2){
        Runner::displayLoxUsage();
        return 1;
    } else if (argc == 2){
        try {
            Runner::runScript(argv[1]);
        } catch (const LoxException &exception){
            std::cerr << exception.what() << "\n";
        }
    } else {
        try {
            Runner::runRepl();
        } catch (const LoxException &exception){
            std::cerr << exception.what() << "\n";
        }
    }

    return 0;
}
