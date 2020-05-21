#define DEBUG

#include <iostream>
#include "Runner.h"
#include "LoxException.h"

#ifdef DEBUG
#include "gtest/gtest.h"
#endif

int main(int argc, char *argv[]) {
#ifdef DEBUG
    ::testing::InitGoogleTest(&argc, argv);
#endif

    if (argc > 2) {
        Runner::displayLoxUsage();
        return 1;
    } else if (argc == 2) {
        try {
            Runner::runScript(argv[1]);
        } catch (const LoxException &exception) {
            std::cerr << exception.what() << "\n";
        }
    } else {
        try {
            Runner::runRepl();
        } catch (const LoxException &exception) {
            std::cerr << exception.what() << "\n";
        }
    }

#ifdef DEBUG
    return RUN_ALL_TESTS();
#else
    return 0;
#endif
}
