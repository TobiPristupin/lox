#include <iostream>

class Base {};

class Derived : public Base {

    void ye(){
        std::cout << "ye" << std::endl;
    }
};


int main(){
    std::string a = " \"ahs\" ";
    std::cout << a << "\n";
}

