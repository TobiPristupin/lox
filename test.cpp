#include <iostream>

void tes(const char* str){
    std::cout << str << "\n";
}
int main(){
    std::string a = "hello";
    tes(a.c_str());
}

