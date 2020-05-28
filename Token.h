#ifndef JLOX_TOKEN_H
#define JLOX_TOKEN_H

#include <string>
#include <any>
#include <variant>
#include "TokenType.h"

using lox_literal_t = std::variant<int, float, std::string, bool, std::nullptr_t>;
/*There is some ambiguity when using std::variant for type safety because tokens that do not have an intrinsic literal value (IF, VAR...)
 * are created with a literal value of nullptr. However, the token NIL does have an intrinsic literal value (null) and is also
 * created with a literal value of nullptr. So a nullptr literal value means that the token has no intrinsic literal value,
 * unless if it is a nullptr. So before operating on the literal value one must check the token type. This could be fixed
 * by creating a new type used only for NIL tokens and adding it to lox_literal_t, while reserving nullptr for tokens without
 * an intrinsic literal value. I might do that some day.
*/
struct Token {

    TokenType type;
    std::string lexeme;
    lox_literal_t literal;
    int line{};

    Token(TokenType type, const std::string &lexeme, const lox_literal_t &literal,
          int line) : type(type), lexeme(lexeme), literal(literal), line(line) {}

    std::string to_string() {
        std::string s = "Token: " + tokenTypeToString(type) + " "  + lexeme;
        if (std::holds_alternative<std::string>(literal)){
            s += " " + std::get<std::string>(literal);
        } else if (std::holds_alternative<int>(literal)){
            s += " " + std::to_string(std::get<int>(literal));
        } else if (std::holds_alternative<float>(literal)){
            s += " " + std::to_string(std::get<float>(literal));
        } else if (std::holds_alternative<bool>(literal)){
            s += " " + std::to_string(std::get<bool>(literal));
        } else if (std::holds_alternative<nullptr_t>(literal)) {
            s += " null";
        }

        s += " " + std::to_string(line);
        return  s;
    }

};


#endif //JLOX_TOKEN_H
