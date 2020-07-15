#ifndef JLOX_LOXERROR_H
#define JLOX_LOXERROR_H


#include <string>

class LoxError : public std::exception {
protected:
    std::string message;
    int line, pos;
public:
    LoxError(const std::string &message, int line=-1, int pos=-1);
    const char *what() const noexcept override;
};


class LoxScanningError : public LoxError {
    public:
        LoxScanningError(const std::string &message, int line, int pos);
        const char* what() const noexcept override;
};

class LoxParsingError : public LoxError {
public:
    LoxParsingError(const std::string &message, int line);
    const char* what() const noexcept override;
};

class LoxRuntimeError : public LoxError {
public:
    LoxRuntimeError(const std::string &message, int line=-1);
    const char* what() const noexcept override;
};


#endif //JLOX_LOXERROR_H
