#ifndef JLOX_LOXCLASSWRAPPER_H
#define JLOX_LOXCLASSWRAPPER_H


#include <string>
#include "LoxObject.h"

class LoxClassWrapper : public LoxObject {
public:
    std::string name;

    LoxClassWrapper(const std::string &name);
};


#endif //JLOX_LOXCLASSWRAPPER_H
