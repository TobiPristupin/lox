#ifndef JLOX_UTILS_H
#define JLOX_UTILS_H

#include "../Token.h"

namespace utils {
    std::string literalToString(const lox_literal_t &literal);
    std::string literalType(const lox_literal_t &literal);
}


#endif //JLOX_UTILS_H
