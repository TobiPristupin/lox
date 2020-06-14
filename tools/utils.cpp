

#include "utils.h"

std::string literalToString(lox_literal_t &literal) {
    if (std::holds_alternative<std::string>(literal)){
        return std::get<std::string>(literal);
    } else if (std::holds_alternative<double>(literal)){
        return std::to_string(std::get<double>(literal));
    } else if (std::holds_alternative<bool>(literal)){
        return std::to_string(std::get<bool>(literal));
    } else if (std::holds_alternative<nullptr_t>(literal)) {
        return "nil";
    }

    //unreachable
    return "";
}

std::string literalType(lox_literal_t &literal) {
    if (std::holds_alternative<std::string>(literal)){
        return "string";
    } else if (std::holds_alternative<double>(literal)){
        return "number";
    } else if (std::holds_alternative<bool>(literal)){
        return "bool";
    } else if (std::holds_alternative<nullptr_t>(literal)) {
        return "nil";
    }

    //unreachable
    return "";
}
