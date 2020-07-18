//#define DEBUG

#include <iostream>
#include "Runner.h"

#ifdef DEBUG
#include "gtest/gtest.h"
#endif

int main(int argc, char *argv[]) {
#ifdef DEBUG
    ::testing::InitGoogleTest(&argc, argv);
#endif

    int exitCode;

    if (argc > 2) {
        Runner::displayLoxUsage();
        exitCode = 0;
    } else if (argc == 2) {
        exitCode = Runner::runScript(argv[1]);
    } else {
        exitCode = Runner::runRepl();
    }

#ifdef DEBUG
    return RUN_ALL_TESTS();
#else
    return exitCode;
#endif
}

//TODO: Add support for ++ and -- operator
//TODO: Add int to str conversion
//TODO: Add support for concatenating int and str?
//TODO: Add a console printing library for colors?


