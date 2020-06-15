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

    int exitCode = 0;

    if (argc > 2) {
        Runner::displayLoxUsage();
        return 1;
    } else if (argc == 2) {
        try {
            Runner::runScript(argv[1]);
        } catch (const LoxScanningError &exception) {
            std::cerr << exception.what() << "\n";
            exitCode = 65;
        } catch (const LoxParsingError &exception) {
            std::cerr << exception.what() << "\n";
            exitCode = 65;
        } catch (const LoxRuntimeError &exception) {
            std::cerr << exception.what() << "\n";
            exitCode = 70;
        }
    } else {
        Runner::runRepl();
    }

#ifdef DEBUG
    return RUN_ALL_TESTS();
#else
    return exitCode;
#endif
}
