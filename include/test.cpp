#include <iostream>
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

class Test {
    public:
        int t;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Test, t);
};

class Derived {
    public:
        std::vector<Test> v;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Derived, v);
};

int main() {
    Derived d;
    Test t1, t2;
    t1.t = 1;
    t2.t = 3;
    d.v.push_back(t1);
    d.v.push_back(t2);

    json j = d;
    std::cout << j << std::endl;
}
