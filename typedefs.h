#include <memory>

#ifndef JLOX_TYPEDEFS_H
#define JLOX_TYPEDEFS_H
//Had to create this file to get rid of a circular dependency between Expr.h and Stmt.h

class Stmt;
class Expr;

using UniqueExprPtr = std::unique_ptr<Expr>;
using UniqueStmtPtr = std::unique_ptr<Stmt>;


#endif //JLOX_TYPEDEFS_H
