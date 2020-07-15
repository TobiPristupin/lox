#ifndef JLOX_LOXOBJECT_H
#define JLOX_LOXOBJECT_H

#include "Token.h"

enum class LoxType {
    NIL, BOOL, NUMBER, STRING, CALLABLE
};

std::string loxTypeToString(LoxType type);

class LoxObject {
public:
    LoxType type = LoxType::NIL;

    explicit LoxObject(const Token &token);
    LoxObject(); //Use this constructor when initializing the object as NIL
    explicit LoxObject(double number);
    explicit LoxObject(const std::string &string);
    explicit LoxObject(const char* string);
    explicit LoxObject(bool boolean);

    bool isNumber() const;
    bool isBoolean() const;
    bool isString() const;
    bool isNil() const;

    bool truthy() const;

    double getNumber() const;
    bool getBoolean() const ;
    std::string getString() const;

    friend std::ostream& operator<<(std::ostream& os, const LoxObject& object);
    friend LoxObject operator+(const LoxObject &lhs, const LoxObject &rhs);
    friend LoxObject operator-(const LoxObject &lhs, const LoxObject &rhs);
    friend LoxObject operator*(const LoxObject &lhs, const LoxObject &rhs);
    friend LoxObject operator/(const LoxObject &lhs, const LoxObject &rhs);
    friend bool operator==(const LoxObject &lhs, const LoxObject &rhs);
    friend bool operator!=(const LoxObject &lhs, const LoxObject &rhs);
    friend bool operator>(const LoxObject &lhs, const LoxObject &rhs);
    friend bool operator>=(const LoxObject &lhs, const LoxObject &rhs);
    friend bool operator<(const LoxObject &lhs, const LoxObject &rhs);
    friend bool operator<=(const LoxObject &lhs, const LoxObject &rhs);
    LoxObject operator-() const;
    LoxObject operator!() const;


private:

    double number = 0.0;
    bool boolean = false;
    std::string str = "";
};


#endif //JLOX_LOXOBJECT_H
