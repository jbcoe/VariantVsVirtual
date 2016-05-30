#include "timer.h"
#include <algorithm>
#include <eggs/variant.hpp>
#include <iostream>
#include <random>
#include <vector>

struct odd {
  int value() const { return 1; }
};

struct even {
  int value() const { return 0; }
};

using number = eggs::variant<odd, even>;

int main(int argc, const char *argv[]) {
  int count = std::atoi(argv[1]);

  std::uniform_int_distribution<int> distribution(0, 1);
  std::random_device r;
  std::mt19937 engine(r());
  auto generator = std::bind(distribution, engine);

  int odd_count = 0;

  std::vector<number> numbers;
  numbers.reserve(count);
  std::generate_n(std::back_inserter(numbers), count, [&]() -> number {
    if (generator())
      return odd();
    return even();
  });

  {
    auto t = make_timer("count variants");
    auto odds =
        std::count_if(numbers.begin(), numbers.end(), [](const auto &n) {
          return eggs::variants::apply([](const auto &n) { return n.value(); },
                                       n);
        });

    std::cout << odds << std::endl;
  }
}
