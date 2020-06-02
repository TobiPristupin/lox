#include "iostream"

class Base {
public:

    Base(std::string hey){
        std::cout << hey << "\n";
    }

    virtual std::string to_string();
};

class Derived : public Base {

    Derived(std::string hey) : Base(hey) {}

    std::string to_string(){
        std::cout <<
    }
};

int main(){
    Base a("hello");
    Base b(true);
}