#include "../src/prime_generators.h"
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <vector>

using GeneratorFuncSig = std::vector<int>;

template <typename T>
  requires std::is_invocable_r_v<GeneratorFuncSig, T, size_t>
void test(T func) {
  std::vector<int> cache = func(1000000);
  std::cout << cache.size() << std::endl;
  return;
}

int main(int argc, char *argv[]) {

  test(gen::smart);

  return 0;
}
