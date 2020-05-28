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

    /*NOTE: Here we have an overloaded constructor for each literal type, instead of having one constructor that accepts
     * a literal parameter of type lox_literal_t. This is because in the special case in which a string is passed as the literal,
     * we need to make sure that we are passing an std::string to the lox_literal_t constructor instead of a char* .
     * If we pass a char* accidentally, char* will decay into a bool and literal will hold a bool instead of a string.
     * This is explained much more clearly here: https://stackoverflow.com/questions/44086269/why-does-my-variant-convert-a-stdstring-to-a-bool
     * Having a separate constructor for std::string allows us to make sure that we are always working with an std::string.
     *
     * Don't ask me how I found this bug. Just crazy C++ shit.
     * */
    Token(TokenType type, const std::string &lexeme, const std::string &literal, int line);
    Token(TokenType type, const std::string &lexeme, const int &literal, int line);
    Token(TokenType type, const std::string &lexeme, const float &literal, int line);
    Token(TokenType type, const std::string &lexeme, const bool &literal, int line);
    Token(TokenType type, const std::string &lexeme, int line);

    std::string to_string();

};

#endif //JLOX_TOKEN_H
