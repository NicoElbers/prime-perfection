#include "prime_generators.h"
#include <iostream>

int main(int argc, char *argv[]) {
  gen::multi_thread(1000000);

  std::cout << std::endl;
  return 0;
}
