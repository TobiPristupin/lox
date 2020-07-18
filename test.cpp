#include "iostream"
#include <variant>
#include <vector>
#include <memory>

class Res {
public:
    Res(){
        std::cout << "Resource acquired\n";
    }

    ~Res(){
        std::cout << "Resource deleted\n";
    }

    Res operator-() const {
        throw std::runtime_error("hewyre");
    }
};



std::unique_ptr<Res> ret(){
    std::unique_ptr<Res> ptr = std::make_unique<Res>();
    std::cout << ptr.get() << "\n";
    return ptr;
}

std::vector<std::unique_ptr<Res>> create(){
    std::vector<std::unique_ptr<Res>> vec;
    std::unique_ptr<Res> res = std::make_unique<Res>();
    vec.push_back(std::move(res));
    return vec;
}

void f(std::unique_ptr<Res> uniquePtr){
    std::cout << uniquePtr.get() << "\n";
}

std::unique_ptr<Res> func(std::unique_ptr<Res> res){
    return res;
}

#include <chrono>
int main(){
    using namespace std::chrono;
    std::cout << duration_cast<seconds>(system_clock::now().time_since_epoch()).count() << "\n";
}

