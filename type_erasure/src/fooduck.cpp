#include <iostream>
#include "fooduck.h"
class Duck {
    public:
    char quack() {
        return m_complicatedData;
    }

    private:
    char m_complicatedData = 'q';
};

FooDuck::FooDuck() { m_duck = std::make_unique<Duck>(); }
FooDuck::~FooDuck() = default;

void FooDuck::quack() {
    std::cout << m_duck->quack();
}