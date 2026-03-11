#include <array>
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

constexpr auto kSize = 3u;
using MatrixType =
    std::array<std::array<int, kSize>,
               kSize>; // Define a matrix type using std::array for a 3x3 matrix

auto cache_thrashing_fast(
    MatrixType& matrix) { // Function to fill the matrix in a cache-friendly way
  auto counter = 0;
  for (auto i = 0u; i < kSize; ++i) {
    for (auto j = 0u; j < kSize; ++j) {
      matrix[i][j] =
          ++counter; // Fill the matrix row by row, which is cache-friendly
      cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j]
           << " "; // Print the value just assigned to the matrix for
                   // demonstration
    }
    cout << endl; // Print a newline after each row for better readability
  }
}
auto cache_thrashing_slow(MatrixType& matrix) { // Function to fill the matrix
                                                // in a cache-unfriendly way
  auto counter = 0;
  for (auto i = 0u; i < kSize; ++i) {
    for (auto j = 0u; j < kSize; ++j) {
      matrix[j][i] = ++counter; // Fill the matrix column by column, which can
                                // cause cache thrashing

      cout << "matrix[" << j << "][" << i << "] = " << matrix[j][i]
           << " "; // Print the value just assigned to the matrix for
                   // demonstration
    }
    cout << endl; // Print a newline after each column for better readability
  }
}

int main() {
  // ::testing::InitGoogleTest(&argc, argv); // Initialize Google Test framework
  // return RUN_ALL_TESTS(); // Run all the tests defined in this file

  MatrixType m; // Create a matrix instance on the stack because it's small
                // enough to fit without causing stack overflow
  cout << "Filling matrix in a cache-friendly way:" << endl;
  cache_thrashing_fast(m); // Fill the matrix using the cache-friendly method
  cout << "\nFilling matrix in a cache-unfriendly way:" << endl;
  cache_thrashing_slow(m); // Fill the matrix using the cache-unfriendly method
  return 0;                // Exit the program
}