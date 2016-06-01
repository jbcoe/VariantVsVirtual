#include "timer.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

struct number {
  virtual ~number() = default;
  virtual int value() const = 0;
};

struct odd : number {
  int value() const override { return 1; }
};

struct even : number {
  int value() const override { return 0; }
};

int main(int argc, const char *argv[]) {
  int count = std::atoi(argv[1]);

  std::uniform_int_distribution<int> distribution(0, 1);
  std::random_device r;
  std::mt19937 engine(r());
  auto generator = std::bind(distribution, engine);

  int odd_count = 0;

  auto t = make_timer("dispose virtuals");
  std::vector<std::unique_ptr<number>> numbers;
  numbers.reserve(count);
  {
    auto t = make_timer("build virtuals");
    std::generate_n(std::back_inserter(numbers), count,
                    [&]() -> std::unique_ptr<number> {
                      if (generator())
                        return std::make_unique<odd>();
                      return std::make_unique<even>();
                    });
  }
  {
    auto t = make_timer("count virtuals");
    auto odds = std::count_if(numbers.begin(), numbers.end(),
                              [](const auto &n) { return n->value(); });

    std::cout << odds << std::endl;
  }
}
