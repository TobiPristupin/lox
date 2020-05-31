#ifndef JLOX_TOKEN_H
#define JLOX_TOKEN_H

#include <string>
#include <any>
#include <variant>
#include "TokenType.h"

using lox_literal_t = std::variant<int, float, std::string, bool, std::nullptr_t>;
/*NOTE: There is some ambiguity when using std::variant for type safety because tokens that do not have an intrinsic literal value (IF, VAR...)
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

    /*NOTE: It is important here to have a different overloaded constructor for each type of literal instead of simplifying it
     * to one constructor that accepts a lox_literal_t. This is because if we pass a const char* string directly to the
     * lox_literal_t constructor it will be converted it to a bool (if we pass an std::string instead it will remain as a string).
     * This is explained here: https://stackoverflow.com/questions/44086269/why-does-my-variant-convert-a-stdstring-to-a-bool
     * Having a separate constructor for each type allows us to manually cover the case in which the caller passes a const char* and
     * convert it into an std::string.
     * */
    Token(TokenType type, const std::string &lexeme, const std::string &literal, int line);
    Token(TokenType type, const std::string &lexeme, const char* literal, int line);
    Token(TokenType type, const std::string &lexeme, const int &literal, int line);
    Token(TokenType type, const std::string &lexeme, const float &literal, int line);
    Token(TokenType type, const std::string &lexeme, const bool &literal, int line);
    Token(TokenType type, const std::string &lexeme, int line);

    std::string to_string();

};

#endif //JLOX_TOKEN_H
