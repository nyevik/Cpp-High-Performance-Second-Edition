#include <gtest/gtest.h>
#include <vector>

int main() {
  std::vector<int> v{-1, 5, 2, -3, 4, -5, 5};
  for (const auto& elem : v) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
  return 0;
}