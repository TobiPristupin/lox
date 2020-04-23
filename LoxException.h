#ifndef JLOX_LOXEXCEPTION_H
#define JLOX_LOXEXCEPTION_H


#include <string>

class LoxException : public std::exception {
protected:
    std::string message;
    int line, pos;
public:
    LoxException(std::string message, int line=-1, int pos=-1);
    const char *what() const noexcept override;
//    const char *what() const override; //override correclty, add position in scanning error messahe, test
};


class ScanningException : public LoxException {
    public:
        ScanningException(std::string message, int line, int pos);
        const char* what() const noexcept override;
};

#endif //JLOX_LOXEXCEPTION_H
