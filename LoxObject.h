#ifndef JLOX_LOXOBJECT_H
#define JLOX_LOXOBJECT_H

#include <memory>
#include "Token.h"

enum class LoxType {
    NIL, BOOL, NUMBER, STRING, CALLABLE
};

std::string loxTypeToString(LoxType type);

class LoxCallable;

using SharedCallablePtr = std::shared_ptr<LoxCallable>;

class LoxObject {
public:
    LoxType type = LoxType::NIL;

    explicit LoxObject(const Token &token);
    LoxObject(); //Use this constructor when initializing the object as NIL
    explicit LoxObject(double number);
    explicit LoxObject(const std::string &string);
    explicit LoxObject(const char* string);
    explicit LoxObject(bool boolean);
    explicit LoxObject(SharedCallablePtr callable);
    explicit LoxObject(LoxCallable* ptr) = delete;

    bool isNumber() const;
    bool isBoolean() const;
    bool isString() const;
    bool isNil() const;
    bool isCallable() const;

    bool truthy() const;

    double getNumber() const;
    bool getBoolean() const ;
    std::string getString() const;
    LoxCallable* getCallable() const;

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
    SharedCallablePtr callable;
};


#endif //JLOX_LOXOBJECT_H
