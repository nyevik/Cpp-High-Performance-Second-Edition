#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

void printVector(const std::vector<int>& v) {
  for (const auto& elem : v) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> v{-1, 5, 2, -3, 4, -5, 5};
  printVector(v); // Print the original vector
  std::erase(v, 5);
  printVector(v); // Print the vector after erasing all occurrences of 5
  std::erase_if(v, [](int x) { return x < 0; }); // Erase all negative numbers
  printVector(v); // Print the vector after erasing all negative numbers

  /*std::sort(v.begin(), v.end()); // Sort the vector in ascending order
  printVector(v);     // Print the sorted vector
  std::reverse(v.begin(), v.end()); // Reverse the sorted vector to get
  descending order printVector(v);     // Print the reversed vector std::cout <<
  "The maximum element is " << v.front() << std::endl; std::cout << "The minimum
  element is " << v.back() << std::endl; std::cout << "The sum of all elements
  is " << std::accumulate(v.begin(), v.end(), 0) << std::endl; std::cout << "The
  average of all elements is " << std::accumulate(v.begin(), v.end(), 0) /
  v.size() << std::endl; std::cout << "The number of elements is " << v.size()
  << std::endl; std::cout << "The number of elements is " << v.size() <<
  std::endl; std::cout << "The number of elements is " << v.size() <<
  std::endl;*/
  return 0;
}
