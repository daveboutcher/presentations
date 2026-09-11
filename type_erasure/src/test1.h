#include <iostream>
#include <ostream>

class Duck {
    public:
    Duck() = default;
    ~Duck() = default;
    void quack() const { std::cout << "quack" << std::endl;}
};