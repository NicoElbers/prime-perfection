#include "../src/prime_generators.h"
#include <bits/chrono.h>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <vector>

using GeneratorFuncSig = std::vector<int>;

// TODO git gud
template <typename T>
  requires std::is_invocable_r_v<GeneratorFuncSig, T, size_t>
void test(T func) {
  std::vector<int> cache = func(1000000);
  std::cout << cache.size() << std::endl;
  return;
}

int main(int argc, char *argv[]) {
  const int val_to_check = 1000000;

  std::vector<int> thread_vec = gen::multi_thread(val_to_check);
  // std::vector<int> smart_vec = gen::smart(val_to_check);

  // if (thread_vec.size() != smart_vec.size()) {
  //   std::cout << "Size is not the same, thread_vec is "
  //             << thread_vec.size() - smart_vec.size() << " bigger" <<
  //             std::endl;
  //   for (int i = 0; i < thread_vec.size(); ++i) {
  //     if (i >= smart_vec.size())
  //       break;
  //
  //     if (thread_vec[i] != smart_vec[i])
  //       std::cout << i << ": thread=" << thread_vec[i]
  //                 << " : smart=" << smart_vec[i] << std::endl;
  //   }
  // } else {
  //   std::cout << "EQUAL SIZE!!!" << std::endl;
  // }

  // TODO implement gtest to automate more

  return 0;
}
