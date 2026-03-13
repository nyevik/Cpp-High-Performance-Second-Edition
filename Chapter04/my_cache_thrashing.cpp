#include <array>
#include <gtest/gtest.h>
#include <iostream>
#include <type_traits>

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

void print_matrix(const MatrixType& matrix) { // Function to print the
                                              // contents of the matrix
  for (const auto& row : matrix) {
    for (const auto& value : row) {
      cout << value << " "; // Print each value in the row followed by a space
    }
    cout << endl; // Print a newline after each row for better readability
  }
}
// test function
auto f(const std::array<int, 1024>& input) {
  // do something with input
  cout << "Processing input array of size: " << input.size()
       << endl;    // Print the size of the input array for demonstration
  return input[0]; // Just return the first element for demonstration
}

int main() {
  // ::testing::InitGoogleTest(&argc, argv); // Initialize Google Test framework
  // return RUN_ALL_TESTS(); // Run all the tests defined in this file

  MatrixType m; // Create a matrix instance on the stack because it's small
                // enough to fit without causing stack overflow
  cout << "Filling matrix in a cache-friendly way:" << endl;
  cache_thrashing_fast(m); // Fill the matrix using the cache-friendly method
  print_matrix(m);         // Print the matrix after filling it
  cout << "\nFilling matrix in a cache-unfriendly way:" << endl;
  cache_thrashing_slow(m); // Fill the matrix using the cache-unfriendly method
  print_matrix(m);         // Print the matrix after filling it

  auto a = std::array<int, 16>{}; // allocated on the stack
  auto b = std::array<int, 16>{};

  // are these two arrays the same type?
  cout << "Are the two arrays the same type? " << std::boolalpha
       << std::is_same_v<decltype(a),
                         decltype(b)> << endl; // Check if the two arrays are of
                                               // the same type and print the
                                               // result
  auto c = array<int, 1024>{};
  cout << "Are the two arrays the same type? " << std::boolalpha
       << std::is_same_v<decltype(a), decltype(c)> << endl;
  // arrays a and c are not the same type because they have different sizes,
  // even though they are both std::array<int, N> types.

  // this should not compile:
  // f(a);// This line is commented out because it will not compile due to a
  // type mismatch.

  int d[16]; // C-style array allocated on the stack
  return 0;  // Exit the program
}