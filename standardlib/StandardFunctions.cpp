#include <chrono>
#include <iostream>
#include "StandardFunctions.h"



LoxObject standardFunctions::Clock::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    using namespace std::chrono;
    double ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return LoxObject(ms);
}

int standardFunctions::Clock::arity() {
    return 0;
}

std::string standardFunctions::Clock::to_string() {
    return "<native function " + name() + ">";
}

std::string standardFunctions::Clock::name() {
    return "clock";
}

