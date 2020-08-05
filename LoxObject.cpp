#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "LoxObject.h"
#include "tools/Utils.h"
#include "LoxCallable.h"

LoxObject::LoxObject(double number) : type(LoxType::NUMBER), number(number) {}

LoxObject::LoxObject(const std::string &string) : type(LoxType::STRING), str(string) {}

LoxObject::LoxObject(const char *string) : LoxObject(std::string(string)) {}

LoxObject::LoxObject(bool boolean) : type(LoxType::BOOL), boolean(boolean) {}

LoxObject LoxObject::Nil() {
    return LoxObject();
}

LoxObject::LoxObject(SharedCallablePtr callable) : type(LoxType::CALLABLE), callable(std::move(callable)) {}

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

LoxCallable *LoxObject::getCallable() const {
    if (!isCallable()){
        throw std::runtime_error("LoxObject does not contain a callable");
    }
    return callable.get();
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
    }  else {
        throw std::runtime_error("Cannot apply operator '+' to operands of type " + loxTypeToString(lhs.type) + " and " + loxTypeToString(rhs.type));
    }
    //TODO: Should we allow implicitly converting a number into str to concatenate them?
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
    if (lhs.isNumber() && rhs.isNumber()){
        return lhs.getNumber() == rhs.getNumber();
    } else if (lhs.isString() && rhs.isString()){
        return lhs.getString() == rhs.getString();
    } else if (lhs.isBoolean() && rhs.isBoolean()){
        return lhs.getBoolean() == rhs.getBoolean();
    } else if (lhs.isNil() && rhs.isNil()){
        return true;
    }

    return false; //Comparing between two different types will always be false
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
    if (object.isString()){
        std::string s = object.getString();
        utils::replaceAll(s, "\\n", "\n");
        utils::replaceAll(s, "\\t", "\t");
        os << s;
    } else if (object.isBoolean()){
        os << (object.getBoolean() ? std::string("true") : std::string("false"));
    } else if (object.isNumber()){
        if (std::abs(floor(object.getNumber())) == std::abs(object.getNumber())){ //If it has no decimal part
            os << std::to_string((long long) object.getNumber());
        } else {
            os << std::to_string(object.getNumber());
        }
    } else if (object.isNil()){
        os << std::string("nil");
    } else if (object.isCallable()) {
        os << object.getCallable()->to_string();
    } else {
        throw std::runtime_error("Object has no string representation");
    }
    return os;
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
    }

    return "unreachable";
}


