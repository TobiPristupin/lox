#include "iostream"

class Base {
public:

    Base(std::string hey){
        std::cout << hey << "\n";
    }

    Base(const char* hey){
        Base(std::string(hey));
    }

    Base(bool hey){
        std::cout << hey << "\n";
    }
};

int main(){
    Base a("hello");
    Base b(true);
}