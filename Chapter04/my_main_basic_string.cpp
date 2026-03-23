#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

int main() {
  auto in = std::ifstream(
      "input.txt",
      std::ios::in | std::ios::ate // Open the file in input mode and move the
                                   // file pointer to the end of the file
  );
  if (in.fail()) {
    std::cerr << "Failed to open input file" << std::endl;
    return 1;
  }

  else {
    auto size_pos =
        in.tellg(); // Get the size of the file using tellg() which
                    // returns the current position of the file pointer
    if (size_pos ==
        std::streampos(
            -1)) { // Check if tellg() failed to determine the file size
      std::cerr << "Failed to determine file size" << std::endl;
      in.close();
      return 1;
    }
    auto size = static_cast<std::size_t>(size_pos);
    auto content =
        std::string(size, '\0'); // Create a string with the size of the file
                                 // and initialize it with null characters
    in.seekg(0); // Move the file pointer back to the beginning of the file
    in.read(
        &content[0],
        static_cast<std::streamsize>(
            size)); // Read the content of the file into the string using read()
    std::cout << content << std::endl; // Print the content of the file
    in.close();                        // Close the file
  } // end else
  return EXIT_SUCCESS;
} // end main()
