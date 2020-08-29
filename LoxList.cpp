#include <sstream>
#include "LoxList.h"
#include "LoxObject.h"
#include "Expr.h"
#include "LoxError.h"

LoxList::LoxList(const ListExpr* expr, const std::vector<LoxObject> &items) : listDeclarationExpr(expr), items(items) {}

size_t LoxList::length() {
    return items.size();
}

void LoxList::append(const LoxObject &val) {
    items.push_back(val);
}

LoxObject LoxList::at(int index) {
    assertBounds(index);
    return items[index];
}

LoxObject LoxList::remove(int index) {
    assertBounds(index);
    LoxObject item = items[index];
    items.erase(items.begin() + index);
    return item;
}

void LoxList::assertBounds(int index) {
    if (index < 0 || index >= length()){
        throw LoxRuntimeError("List index out of range", listDeclarationExpr->openingBracket.line);
    }
}

std::string LoxList::to_string() {
    std::stringstream ss;
    ss << "[";
    for (int i = 0; i < length(); i++){
        ss << items[i];
        if (i != length() - 1) ss << ", ";
    }
    ss << "]";

    return ss.str();
}
