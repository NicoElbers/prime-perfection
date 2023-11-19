#include "multi_primes.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

using namespace std;

unique_ptr<vector<int>> prime_bucket_thread(int start, int end) {
  cout << "Started thread" << endl;

  this_thread::sleep_for(chrono::seconds(5));

  vector<int> test_vec;

  for (int i = 0; i < 100; ++i)
    test_vec.emplace_back(i);

  return make_unique<vector<int>>(test_vec);
}
