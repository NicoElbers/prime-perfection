#include "prime_generators.h"
#include <chrono>
#include <fancyfunc/fancy_func.h>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

using GeneratorSig = std::function<std::vector<int>(int)>;
using ns = std::chrono::nanoseconds;

void measurementFunc(GeneratorSig func, int max_ns, int itr) {

  auto max_time = ns(max_ns * 1000000);
  auto start_time = std::chrono::high_resolution_clock::now();
  auto end_time = std::chrono::high_resolution_clock::now();

  double tot_time_ns{0};

  int i = 1;
  unsigned long long num_to_call_with = 0;
  while (end_time - start_time < max_time && i < 64) {
    num_to_call_with = fancy_func(i);

    tot_time_ns = 0;
    for (int i = 0; i < itr; ++i) {

      start_time = std::chrono::high_resolution_clock::now();
      func(num_to_call_with);
      end_time = std::chrono::high_resolution_clock::now();

      tot_time_ns +=
          std::chrono::duration_cast<ns>(end_time - start_time).count();
    }

    std::cout << "Took on average " << std::fixed << std::setprecision(2)
              << (tot_time_ns / itr) / 1000000 << "ms for input value "
              << num_to_call_with << " for " << itr << " iterations."
              << std::endl;
    i++;
  }

  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  // int max_ms{};
  // int itr{};

  // if (argc < 2) {
  //   max_ms = 50;
  // } else {
  //   max_ms = atoi(argv[1]);
  // }

  // if (argc < 3) {
  //   itr = 100;
  // } else {
  //   itr = atoi(argv[2]);
  // }

  // std::cout << "Testing all functions until time takes more than " << max_ms
  //           << " ms per iteration" << std::endl;
  // std::cout << "Warning: may take up to 2 * ms * itr longer than expected"
  //           << std::endl;
  // std::cout << "Testing for " << itr << " iterations" << std::endl;
  // std::cout << std::endl;

  // std::cout << "Testing gen::naive:" << std::endl;
  // measurementFunc(gen::naive, max_ms, itr);
  // std::cout << "Testing gen::smart:" << std::endl;
  // measurementFunc(gen::smart, max_ms, itr);
  // std::cout << "Testing gen::multi_op:" << std::endl;
  // measurementFunc(gen::multi_op, max_ms, itr);
  // std::cout << "Testing gen::multi_thread:" << std::endl;
  // measurementFunc(gen::multi_thread, max_ms, itr);

  // auto start = std::chrono::high_resolution_clock::now();
  auto cache = gen::multi_thread(1'000'000'000);
  // auto end = std::chrono::high_resolution_clock::now();

  // auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end -
  // start)
  //                .count();

  // std::cout << "Took " << dur << "ms" << std::endl;

  return 0;
}
