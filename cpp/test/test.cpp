#include "../src/prime_generators.h"
#include <bits/chrono.h>
#include <gtest/gtest.h>
#include <vector>

const std::vector<int> PRIMES_UNDER_HUNDERD = {
    2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

const int NUM_PRIMES_UNDER_1_000 = 168;
const int NUM_PRIMES_UNDER_10_000 = 1'229;
const int NUM_PRIMES_UNDER_100_000 = 9'592;
const int NUM_PRIMES_UNDER_1_000_000 = 78'498;
const int NUM_PRIMES_UNDER_10_000_000 = 664'579;

TEST(GeneratorsTest, Naive) {
  std::vector<int> primes_to_check = gen::naive(100);

  EXPECT_EQ(25, primes_to_check.size());

  for (int i = 0; i < 25; ++i) {
    EXPECT_EQ(PRIMES_UNDER_HUNDERD[i], primes_to_check[i]);
  }
  primes_to_check = gen::naive(1'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_1_000, primes_to_check.size());
  primes_to_check = gen::naive(10'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_10_000, primes_to_check.size());
  primes_to_check = gen::naive(100'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_100_000, primes_to_check.size());
  // primes_to_check = gen::naive(1'000'000);
  // EXPECT_EQ(NUM_PRIMES_UNDER_1_000_000, primes_to_check.size());
  // primes_to_check = gen::naive(10'000'000);
  // EXPECT_EQ(NUM_PRIMES_UNDER_10_000_000, primes_to_check.size());
}

TEST(GeneratorsTest, Smart) {
  std::vector<int> primes_to_check = gen::smart(100);

  EXPECT_EQ(25, primes_to_check.size());

  for (int i = 0; i < 25; ++i) {
    EXPECT_EQ(PRIMES_UNDER_HUNDERD[i], primes_to_check[i]);
  }
  primes_to_check = gen::smart(1'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_1_000, primes_to_check.size());
  primes_to_check = gen::smart(10'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_10_000, primes_to_check.size());
  primes_to_check = gen::smart(100'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_100_000, primes_to_check.size());
  primes_to_check = gen::smart(1'000'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_1_000_000, primes_to_check.size());
  primes_to_check = gen::smart(10'000'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_10_000_000, primes_to_check.size());
}

TEST(GeneratorsTest, Multi_op) {
  std::vector<int> primes_to_check = gen::multi_op(100);

  EXPECT_EQ(25, primes_to_check.size());

  for (int i = 0; i < 25; ++i) {
    EXPECT_EQ(PRIMES_UNDER_HUNDERD[i], primes_to_check[i]);
  }
  primes_to_check = gen::multi_op(1'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_1_000, primes_to_check.size());
  primes_to_check = gen::multi_op(10'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_10_000, primes_to_check.size());
  primes_to_check = gen::multi_op(100'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_100_000, primes_to_check.size());
  primes_to_check = gen::multi_op(1'000'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_1_000_000, primes_to_check.size());
  primes_to_check = gen::multi_op(10'000'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_10_000_000, primes_to_check.size());
}

TEST(GeneratorsTest, Multi_thread) {
  std::vector<int> primes_to_check = gen::multi_thread(100);
  for (int i = 0; i < 100; ++i) {
    primes_to_check = gen::multi_thread(100);
    EXPECT_EQ(25, primes_to_check.size());

    for (int i = 0; i < 25; ++i) {
      EXPECT_EQ(PRIMES_UNDER_HUNDERD[i], primes_to_check[i]);
    }
  }
  primes_to_check = gen::multi_thread(1'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_1_000, primes_to_check.size());
  primes_to_check = gen::multi_thread(10'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_10_000, primes_to_check.size());
  primes_to_check = gen::multi_thread(100'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_100_000, primes_to_check.size());
  primes_to_check = gen::multi_thread(1'000'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_1_000_000, primes_to_check.size());
  primes_to_check = gen::multi_thread(10'000'000);
  EXPECT_EQ(NUM_PRIMES_UNDER_10_000_000, primes_to_check.size());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
