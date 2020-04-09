#ifndef JLOX_ERRORLOGGER_H
#define JLOX_ERRORLOGGER_H


#include <string>

class ErrorLogger {
public:
    static void error(const std::string &message);
    static void error(int line, const std::string &message);
};


#endif
