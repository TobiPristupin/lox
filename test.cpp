#include <iostream>

class Base {};

class Derived : public Base {

    void ye(){
        std::cout << "ye" << std::endl;
    }
};


int main(){
    Base b;
    Derived c;
    b = c;
    b.ye();

}

