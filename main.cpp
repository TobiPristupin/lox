#include "Runner.h"

int main(int argc, char *argv[]) {
    if (argc > 2){
        Runner::displayLoxUsage();
        return 1;
    } else if (argc == 2){
        Runner::runScript(argv[1]);
    } else {
        Runner::runRepl();
    }

    return 0;
}
