#include <memory>
class Duck;

class FooDuck {
  public:
    FooDuck();
    ~FooDuck();
    void quack();
  private:
    std::unique_ptr<Duck> m_duck;
};