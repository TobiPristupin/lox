#include "utils.h"
#include <cmath>

namespace utils {

    std::string literalToString(lox_literal_t &literal) {
        if (std::holds_alternative<std::string>(literal)){
            return std::get<std::string>(literal);
        } else if (std::holds_alternative<double>(literal)){
            double val = std::get<double>(literal);
            if (std::abs(floor(val)) == std::abs(val)){ //If it has no decimal part
                return std::to_string((int) val);
            }

            return std::to_string(val);
        } else if (std::holds_alternative<bool>(literal)){
            return std::get<bool>(literal) ? "true" : "false";
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
}

