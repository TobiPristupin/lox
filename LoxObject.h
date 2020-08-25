#ifndef JLOX_LOXOBJECT_H
#define JLOX_LOXOBJECT_H

#include <iosfwd>
#include <memory>
#include <string>

struct Token;

enum class LoxType {
    NIL, BOOL, NUMBER, STRING, CALLABLE, INSTANCE
};

std::string loxTypeToString(LoxType type);

class LoxCallable;
class LoxClassInstance;

/*A shared ptr is used because there may be scenarios where a Callable object such as a function has to be owned
by more than one LoxObject.*/
using SharedCallablePtr = std::shared_ptr<LoxCallable>;
using SharedInstancePtr = std::shared_ptr<LoxClassInstance>;

/* This class is a wrapper to represent bool, nil, numbers, strings, callables, and instances.
 * */
class LoxObject {
public:
    LoxType type = LoxType::NIL;

    explicit LoxObject(const Token &token);
    explicit LoxObject(double number);
    explicit LoxObject(const std::string &string);
    explicit LoxObject(const char* string);
    explicit LoxObject(bool boolean);
    explicit LoxObject(SharedCallablePtr callable);
    explicit LoxObject(LoxCallable* ptr) = delete;
    explicit LoxObject(SharedInstancePtr instance);
    explicit LoxObject(LoxClassInstance* ptr) = delete;
    static LoxObject Nil();
    LoxObject(); //Initializes the object as NIL

    bool isNumber() const;
    bool isBoolean() const;
    bool isString() const;
    bool isNil() const;
    bool isCallable() const;
    bool isClassInstance() const;

    bool truthy() const;

    double getNumber() const;
    bool getBoolean() const ;
    std::string getString() const;
    LoxCallable* getCallable() const;
    LoxClassInstance* getClassInstance() const;


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
    LoxObject operator++();
    LoxObject operator--();
    LoxObject operator-() const;
    LoxObject operator!() const;


private:

    double number = 0.0;
    bool boolean = false;
    std::string str = "";
    SharedCallablePtr callable;
    SharedInstancePtr instance;
};

#endif //JLOX_LOXOBJECT_H
