#include "StandardFunctions.h"
#include <chrono>
#include <iostream>
#include <thread>


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

//TODO: there should be some type checking here.
LoxObject standardFunctions::Sleep::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    int time = (int) arguments[0].getNumber();
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    return LoxObject();
}

int standardFunctions::Sleep::arity() {
    return 1;
}

std::string standardFunctions::Sleep::to_string() {
    return "<native function " + name() + ">";
}

std::string standardFunctions::Sleep::name() {
    return "sleep";
}

