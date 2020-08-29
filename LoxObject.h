#ifndef JLOX_LOXOBJECT_H
#define JLOX_LOXOBJECT_H

#include <iosfwd>
#include <memory>
#include <string>

struct Token;

enum class LoxType {
    NIL, BOOL, NUMBER, STRING, CALLABLE, INSTANCE, LIST
};

std::string loxTypeToString(LoxType type);

class LoxCallable;
class LoxClassInstance;
class LoxList;

/* A shared ptr is used because resources such as functions, classes, and instances are created and stored in memory only once but can
 * be shared with multiple users. For example, two variables can refer to the same function.
 * */
using SharedCallablePtr = std::shared_ptr<LoxCallable>;
using SharedInstancePtr = std::shared_ptr<LoxClassInstance>;
using SharedListPtr = std::shared_ptr<LoxList>;

/*The book uses Java's Object class to represent variables, instances, functions, etc, essentially surrendering type safety
 * and having to depend on instanceof checks. When porting it to C++ I attempted to maintain some type safety while still
 * staying close to the book. LoxObject is my attempt to do that. LoxObject is a wrapper that can hold literals, callables
 * such as functions and classes, and instances.
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
    explicit LoxObject(SharedListPtr list);
    explicit LoxObject(LoxList* ptr) = delete;
    static LoxObject Nil();
    LoxObject(); //Initializes the object as NIL

    bool isNumber() const;
    bool isBoolean() const;
    bool isString() const;
    bool isNil() const;
    bool isCallable() const;
    bool isClassInstance() const;
    bool isList() const;

    bool truthy() const;

    double getNumber() const;
    bool getBoolean() const ;
    std::string getString() const;
    SharedCallablePtr getCallable() const;
    SharedInstancePtr getClassInstance() const;
    SharedListPtr getList() const;


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
    SharedListPtr list;
};

#endif //JLOX_LOXOBJECT_H
