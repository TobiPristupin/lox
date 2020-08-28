#include "LoxObject.h"
#include <cmath>
#include <stdexcept>
#include <utility>
#include "LoxCallable.h"
#include "LoxClass.h"
#include "Token.h"
#include "TokenType.h"
#include "tools/Utils.h"

LoxObject::LoxObject(double number) : type(LoxType::NUMBER), number(number) {}

LoxObject::LoxObject(const std::string &string) : type(LoxType::STRING), str(string) {}

LoxObject::LoxObject(const char *string) : LoxObject(std::string(string)) {}

LoxObject::LoxObject(bool boolean) : type(LoxType::BOOL), boolean(boolean) {}

LoxObject LoxObject::Nil() {
    return LoxObject();
}

LoxObject::LoxObject(SharedCallablePtr callable) : type(LoxType::CALLABLE), callable(std::move(callable)) {}

LoxObject::LoxObject(SharedInstancePtr instance) : type(LoxType::INSTANCE), instance(std::move(instance)) {}

LoxObject::LoxObject(const Token &token) {
    switch (token.type) {
        case NUMBER:
            type = LoxType::NUMBER;
            number = std::stod(token.lexeme);
            break;
        case TRUE:
            type = LoxType::BOOL;
            boolean = true;
            break;
        case FALSE:
            type = LoxType::BOOL;
            boolean = false;
            break;
        case STRING:
            type = LoxType::STRING;
            str = token.lexeme;
            break;
        case NIL:
            type = LoxType::NIL;
            break;
        default:
            throw std::runtime_error("Invalid token type when constructing LoxObject");
    }
}

LoxObject::LoxObject() : type(LoxType::NIL) {}


bool LoxObject::isNumber() const {
    return type == LoxType::NUMBER;
}

bool LoxObject::isBoolean() const {
    return type == LoxType::BOOL;
}

bool LoxObject::isString() const {
    return type == LoxType::STRING;
}

bool LoxObject::isNil() const {
    return type == LoxType::NIL;
}

bool LoxObject::isCallable() const {
    return type == LoxType::CALLABLE;
}

bool LoxObject::isClassInstance() const {
    return type == LoxType::INSTANCE;
}

double LoxObject::getNumber() const {
    if (!isNumber()){
        throw std::runtime_error("LoxObject does not contain a number");
    }
    return number;
}

bool LoxObject::getBoolean() const {
    if (!isBoolean()){
        throw std::runtime_error("LoxObject does not contain a boolean");
    }
    return boolean;
}

std::string LoxObject::getString() const {
    if (!isString()){
        throw std::runtime_error("LoxObject does not contain a string");
    }
    return str;
}

SharedCallablePtr LoxObject::getCallable() const {
    if (!isCallable()){
        throw std::runtime_error("LoxObject does not contain a callable");
    }
    return callable;
}

SharedInstancePtr LoxObject::getClassInstance() const {
    if (!isClassInstance()){
        throw std::runtime_error("LoxObject does not contain a class instance");
    }
    return instance;
}

bool LoxObject::truthy() const {//In lox every literal is considered true except for nil and false
    if (isBoolean()){
        return getBoolean();
    } else if (isNil()){
        return false;
    }

    return true;
}

LoxObject operator+(const LoxObject &lhs, const LoxObject &rhs) {
    if (lhs.isNumber() && rhs.isNumber()){
        return LoxObject(lhs.getNumber() + rhs.getNumber());
    } else if (lhs.isString() && rhs.isString()){
        return LoxObject(lhs.getString() + rhs.getString());
    }

//    else if (lhs.isString() && rhs.isNumber()){
//        return LoxObject(lhs.getString() + std::to_string(rhs.getNumber()));
//    } else if (lhs.isNumber() && rhs.isString()){
//        return LoxObject(std::to_string(lhs.getNumber()) + rhs.getString());
//    }

    else {
        throw std::runtime_error("Cannot apply operator '+' to operands of type " + loxTypeToString(lhs.type) + " and " + loxTypeToString(rhs.type));
    }
}

LoxObject operator-(const LoxObject &lhs, const LoxObject &rhs) {
    if (lhs.isNumber() && rhs.isNumber()){
        return LoxObject(lhs.getNumber() - rhs.getNumber());
    } else {
        throw std::runtime_error("Cannot apply operator '-' to operands of type " + loxTypeToString(lhs.type) + " and " + loxTypeToString(rhs.type));
    }
}

LoxObject operator*(const LoxObject &lhs, const LoxObject &rhs) {
    if (lhs.isNumber() && rhs.isNumber()){
        return LoxObject(lhs.getNumber() * rhs.getNumber());
    } else {
        throw std::runtime_error("Cannot apply operator '*' to operands of type " + loxTypeToString(lhs.type) + " and " + loxTypeToString(rhs.type));
    }
}

LoxObject operator/(const LoxObject &lhs, const LoxObject &rhs) {
    if (lhs.isNumber() && rhs.isNumber()){
        if (rhs.getNumber() == 0.0){
            throw std::runtime_error("Cannot divide by zero");
        }
        return LoxObject(lhs.getNumber() / rhs.getNumber());
    } else {
        throw std::runtime_error("Cannot apply operator '/' to operands of type " + loxTypeToString(lhs.type) + " and " + loxTypeToString(rhs.type));
    }
}

bool operator==(const LoxObject &lhs, const LoxObject &rhs) {
    if (lhs.type != rhs.type) return false;

    if (lhs.isNumber() && rhs.isNumber()){
        return lhs.getNumber() == rhs.getNumber();
    } else if (lhs.isString() && rhs.isString()){
        return lhs.getString() == rhs.getString();
    } else if (lhs.isBoolean() && rhs.isBoolean()){
        return lhs.getBoolean() == rhs.getBoolean();
    } else if (lhs.isNil() && rhs.isNil()){
        return true;
    } else if (lhs.isCallable() && rhs.isCallable()){
        return lhs.getCallable() == rhs.getCallable();
    } else if (rhs.isClassInstance() && rhs.isClassInstance()){
        return lhs.getClassInstance() == rhs.getClassInstance();
    }

    throw std::runtime_error("This should be unreachable. Missing case");
}

bool operator!=(const LoxObject &lhs, const LoxObject &rhs) {
    return !(lhs == rhs);
}

bool operator>(const LoxObject &lhs, const LoxObject &rhs) {
    if (lhs.isNumber() && rhs.isNumber()){
        return lhs.getNumber() > rhs.getNumber();
    } else if (lhs.isString() && rhs.isString()){
        return lhs.getString() > rhs.getString();
    } else {
        throw std::runtime_error("Cannot apply operator '>' to operands of type " + loxTypeToString(lhs.type) + " and " + loxTypeToString(rhs.type));
    }
}

bool operator>=(const LoxObject &lhs, const LoxObject &rhs) {
    return lhs > rhs || lhs == rhs;
}

bool operator<(const LoxObject &lhs, const LoxObject &rhs) {
    if (lhs.isNumber() && rhs.isNumber()){
        return lhs.getNumber() < rhs.getNumber();
    } else if (lhs.isString() && rhs.isString()){
        return lhs.getString() < rhs.getString();
    } else {
        throw std::runtime_error("Cannot apply operator '<' to operands of type " + loxTypeToString(lhs.type) + " and " + loxTypeToString(rhs.type));
    }
}

bool operator<=(const LoxObject &lhs, const LoxObject &rhs) {
    return lhs < rhs || lhs == rhs;
}

LoxObject LoxObject::operator-() const {
    if (this->isNumber()){
        return LoxObject(-getNumber());
    }

    throw std::runtime_error("Cannot apply unary operator '-' to operand of type " + loxTypeToString(this->type));
}

LoxObject LoxObject::operator!() const {
    if (this->isBoolean()){
        return LoxObject(!truthy());
    }

    throw std::runtime_error("Cannot apply unary operator '!' to operand of type " + loxTypeToString(this->type));
}

LoxObject LoxObject::operator++() {
    if (isNumber()){
        return LoxObject(++number);
    }

    throw std::runtime_error("Cannot apply prefix operator '++' to operand of type " + loxTypeToString(this->type));
}

LoxObject LoxObject::operator--() {
    if (isNumber()){
        return LoxObject(--number);
    }

    throw std::runtime_error("Cannot apply prefix operator '--' to operand of type " + loxTypeToString(this->type));
}

std::ostream &operator<<(std::ostream &os, const LoxObject &object) {
    switch (object.type) {
        case LoxType::NIL:
            os << std::string("nil");
            return os;
        case LoxType::BOOL:
            os << (object.getBoolean() ? std::string("true") : std::string("false"));
            return os;
        case LoxType::NUMBER:
            if (std::abs(floor(object.getNumber())) == std::abs(object.getNumber())){ //If it has no decimal part
                os << std::to_string((long long) object.getNumber());
            } else {
                os << std::to_string(object.getNumber());
            }
            return os;
        case LoxType::STRING:
            {
            std::string s = object.getString();
            utils::replaceAll(s, "\\n", "\n");
            utils::replaceAll(s, "\\t", "\t");
            os << s;
            return os;
            }
        case LoxType::CALLABLE:
            os << object.getCallable()->to_string();
            return os;
        case LoxType::INSTANCE:
            os << object.getClassInstance()->to_string();
            return os;
        default:
            throw std::runtime_error("Object has no string representation");
    }
}


std::string loxTypeToString(LoxType type) {
    switch (type) {
        case LoxType::NIL:
            return "nil";
        case LoxType::BOOL:
            return "bool";
        case LoxType::NUMBER:
            return "number";
        case LoxType::STRING:
            return "string";
        case LoxType::CALLABLE:
            return "callable";
        case LoxType::INSTANCE:
            return "instance";
    }

    throw std::runtime_error("This should be unreachable. Missing case.");
}


