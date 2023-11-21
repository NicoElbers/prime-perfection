#include "../src/prime_generators.h"
#include <iostream>
#include <type_traits>
#include <vector>

using GeneratorFuncSig = std::unique_ptr<std::vector<int>>;

template <typename T>
concept Invocable = std::is_invocable_r<GeneratorFuncSig, T, int>::value;

class GeneratorTesting {
public:
  template <Invocable T> void test(T func) {
    std::vector<int> cache = *func(1000000);
    std::cout << cache.size() << std::endl;
    return;
  }
};

int main(int argc, char *argv[]) {
  GeneratorTesting test;

  test.test(gen::smart);

  return 0;
}
