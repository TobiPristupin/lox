#include "StandardFunctions.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <sstream>
#include "../LoxError.h"

class Interpreter;

standardFunctions::Clock::Clock() : LoxCallable(CallableType::FUNCTION) {}

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

standardFunctions::Sleep::Sleep() : LoxCallable(CallableType::FUNCTION) {}

LoxObject standardFunctions::Sleep::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    int time;
    try {
        time = (int) arguments[0].getNumber();
    } catch (const std::runtime_error &error) {
        throw LoxRuntimeError("Function 'sleep' expected an integer as its argument");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    return LoxObject::Nil();
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


standardFunctions::Str::Str() : LoxCallable(CallableType::FUNCTION) {}

LoxObject standardFunctions::Str::call(Interpreter &interpreter, const std::vector<LoxObject> &arguments) {
    std::stringstream ss; //Use stringstream because LoxObject overrides operator '<<' for printing
    ss << arguments[0];
    return LoxObject(ss.str());
}

int standardFunctions::Str::arity() {
    return 1;
}

std::string standardFunctions::Str::to_string() {
    return "<native function " + name() + ">";
}

std::string standardFunctions::Str::name() {
    return "str";
}
