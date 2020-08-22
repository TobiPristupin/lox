#include "iostream"
#include <utility>
#include <variant>
#include <vector>
#include <memory>
#include <unordered_map>

class Res {
public:

    Res* parent;
    explicit Res(Res* parent = nullptr) : parent(parent) {
        std::cout << "Resource acquired\n";
    }

    ~Res(){
        std::cout << "Resource deleted\n";
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

class Takes {
    std::shared_ptr<Res> ptr;

public:
    Takes(std::shared_ptr<Res> ptr) : ptr(std::move(ptr)) {}
};


int main(){
    std::optional<std::unique_ptr<Res>> res = std::nullopt;
//    std::optional<std::unique_ptr<Res>> res = std::make_unique<Res>();
    std::cout << res.has_value() << "\n";
//    std::cout << res.has_value() << "\n";
}

