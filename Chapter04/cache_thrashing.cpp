#include <array>
#include <gtest/gtest.h>

//
// This example demonstrates cache thrashing.
// Changing the way we access elements in
// a matrix has a huge effect on the
// performance.
//

// The L1 Data cache size, replace this number with the
// L1 Data cache size on your machine
constexpr auto kL1CacheCapacity = 32768u;
constexpr auto kSize = kL1CacheCapacity / sizeof(int);
using MatrixType = std::array<std::array<int, kSize>, kSize>;

auto cache_thrashing_fast(MatrixType& matrix) {
  auto counter = 0;
  for (auto i = 0u; i < kSize; ++i) {
    for (auto j = 0u; j < kSize; ++j) {
      matrix[i][j] = counter++;
    }
  }
}

auto cache_thrashing_slow(MatrixType& matrix) {
  auto counter = 0;
  for (auto i = 0u; i < kSize; ++i) {
    for (auto j = 0u; j < kSize; ++j) {
      matrix[j][i] = counter++; // Slow due to cache thrashing
    }
  }
}

// Use static storage duration so the matrix is placed in
// static memory instead of on the thread stack.
// For this example, the matrix is large enough that a stack
// allocation could easily overflow a typical stack.
// As a global object, it is created once and reused by both tests.
MatrixType m;

TEST(CacheThrashing, Fast) { cache_thrashing_fast(m); }

TEST(CacheThrashing, Slow) { cache_thrashing_slow(m); }
