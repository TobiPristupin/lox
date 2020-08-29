#ifndef JLOX_LOXLIST_H
#define JLOX_LOXLIST_H

#include <vector>

class ListExpr;
class LoxObject;

class LoxList {
public:

    LoxList(const ListExpr* expr, const std::vector<LoxObject> &items);

    size_t length();
    void append(const LoxObject &val);
    LoxObject at(int index);
    LoxObject remove(int index);
    std::string to_string();


private:
    //non owning. All AST nodes are owned by runner.cpp
    const ListExpr* listDeclarationExpr;
    std::vector<LoxObject> items;

    void assertBounds(int index);
};


#endif //JLOX_LOXLIST_H
