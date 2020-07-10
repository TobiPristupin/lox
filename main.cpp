//#define DEBUG

#include <iostream>
#include "Runner.h"
#include "LoxError.h"

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

//TODO: Change every cerr into cout because the streams are not synchronized
//TODO: Add support for ++ and -- operator
//TODO: Add printing newlines
//TODO: Add string concatenation