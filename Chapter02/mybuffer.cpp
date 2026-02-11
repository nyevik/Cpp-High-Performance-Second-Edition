// resource acquisition and the rule of 5:
// If a class manages a resource (e.g., dynamic memory, file handles, network
// connections), it should define all five of the following special member
// functions to ensure proper resource management and avoid issues like memory
// leaks or double deletions:
// 1. Copy constructor: A constructor that creates a new object as a copy of an
// existing object.
// 2. Copy assignment operator: An operator that assigns the contents of one
// object to another existing object.
// 3. Destructor: A function that is called when an object goes out of scope or
// is explicitly deleted, responsible for releasing any resources held by the
// object.
// 4. Move constructor: A constructor that creates a new object by taking
// ownership of the resources of an existing object, leaving the existing object
// in a valid but unspecified state.
// 5. Move assignment operator: An operator that assigns the resources of one
// object to another existing object, first deallocating any existing resources
// and then taking ownership of the resources of the other object, leaving the
// other object in a valid but unspecified state.

#include <algorithm>
#include <iostream>
#if __has_include(<source_location>)
#include <source_location>
#endif

#define DEBUG 1
#define PRINT_BUFFER(x)                                                        \
  (x).printBuffer(#x) // macro to print the contents of a buffer along with its
                      // name for debugging

class Buffer {

public:
  // Constructor
  Buffer(const std::initializer_list<float>&
             values) // using initializer list to initialize the buffer with a
                     // list of float values
      : size_(values.size()),
        ptr_(new float[values.size()]) // raw pointer to a dynamically allocated
                                       // array of floats, initialized with the
                                       // size of the initializer list, need to
                                       // manage the memory manually.
  {
    std::copy(values.begin(), values.end(), ptr_);
  } // end of constructor
  // 1. Copy constructor
  Buffer(const Buffer& other); // copy constructor, creates a new buffer by
                               // copying the contents of another buffer
  // 2. Copy assignment operator
  Buffer& operator=(
      const Buffer&
          other); // copy assignment operator, assigns the contents of one
                  // buffer to another buffer, first deallocating any existing
                  // memory and then copying the contents of the other buffer
  // 3. Destructor
  ~Buffer(); // destructor, deallocates the memory used by the buffer when it
             // goes out of scope or is explicitly deleted
  // 4. Move constructor
  Buffer(Buffer&& other) noexcept; // move constructor, creates a new buffer by
                                   // taking ownership of the resources of
                                   // another buffer, leaving the other buffer
                                   // in a valid but unspecified state
  // 5. Move assignment operator
  Buffer& operator=(
      Buffer&&
          other) noexcept; // move assignment operator, assigns the resources of
                           // one buffer to another buffer, first deallocating
                           // any existing memory and then taking ownership of
                           // the resources of the other buffer, leaving the
                           // other buffer in a valid but unspecified state
  // Swap function for implementing the copy-and-swap idiom for exception-safe
  // copy assignment
  void
  swap(Buffer& other) noexcept { // swap function, swaps the contents of two
                                 // buffers, used to implement the copy-and-swap
                                 // idiom for exception-safe copy assignment
    std::swap(size_, other.size_); // swaps the size of the two buffers
    std::swap(ptr_,
              other.ptr_); // swaps the pointers to the data of the two buffers
  }

  void printBuffer(const char* name = "<unnamed>")
      const { // printBuffer function, prints the contents of the buffer along
              // with its name and memory address for debugging purposes.
    std::cout << "Buffer " << this << " (" << name << ") contents: "
              << std::endl; // prints a header for the buffer contents
    std::cout << "Size: " << size_
              << std::endl; // prints the size of the
                            // buffer to show how many elements it contains
    std::cout << "Address of float array is: " << static_cast<const void*>(ptr_)
              << std::endl; // prints the address of the float array to show
                            // where the data is stored in memory

    for (size_t i = 0; i < size_; ++i) {
      std::cout << ptr_[i] << " "; // prints each element of the buffer followed
                                   // by a space
    }
    std::cout << std::endl; // prints a newline after printing all elements of
                            // the buffer
  }

  void printLocation(
#if defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L
      const std::source_location& loc = std::source_location::current()
#else
      const char* file = __FILE__, int line = __LINE__,
      const char* function = __func__
#endif
  ) const { // printLocation function, prints the source location of the call
            // for debugging purposes
#if defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L
    std::cout << "Called from " << loc.file_name() << ":" << loc.line()
              << " in function " << loc.function_name()
              << std::endl; // prints the file name, line number, and function
                            // name of the call site
#else
    std::cout << "Called from " << file << ":" << line << " in function "
              << function << std::endl;
#endif
  }

private:
  size_t size_{0};
  float* ptr_{nullptr};
}; // end of class Buffer

Buffer::Buffer(const Buffer& other)
    : size_(other.size_) { // copy constructor, creates a new buffer by copying
                           // the contents of another buffer
  ptr_ = new float[size_]; // allocates new memory for the buffer
  std::copy(other.ptr_, other.ptr_ + size_,
            ptr_); // copies the contents of the other buffer into the newly
                   // allocated memory
}

Buffer& Buffer::operator=(
    const Buffer&
        other) { // copy assignment operator, assigns the contents of one buffer
                 // to another buffer, first deallocating any existing memory
                 // and then copying the contents of the other buffer
  delete[] ptr_; // deallocates any existing memory used by the buffer
  ptr_ = new float[other.size_]; // allocates new memory for the buffer
  size_ = other.size_;           // copies the size of the other buffer
  std::copy(other.ptr_, other.ptr_ + size_,
            ptr_); // copies the contents of the other buffer into the newly
                   // allocated memory
  return *this;    // returns a reference to the current object
}

Buffer::~Buffer() { // destructor, deallocates the memory used by the buffer
#ifdef DEBUG
  std::cout << "Destroying buffer " << this
            << std::endl; // when it goes out of scope or is explicitly deleted
#endif
  delete[] ptr_;  // deallocates the memory used by the buffer
  ptr_ = nullptr; // sets the pointer to nullptr to avoid dangling pointer
                  // issues
}

Buffer::Buffer(Buffer&& other) noexcept
    : size_(other.size_),
      ptr_(
          other.ptr_) { // move constructor, creates a new buffer by taking
                        // ownership of the resources of another buffer, leaving
                        // the other buffer in a valid but unspecified state
  other.ptr_ = nullptr; // sets the pointer of the other buffer to nullptr to
                        // indicate that it no longer owns the resources
  other.size_ = 0; // sets the size of the other buffer to 0 to indicate that it
                   // no longer has any resources
}
Buffer& Buffer::operator=(
    Buffer&&
        other) noexcept { // move assignment operator, assigns the resources of
                          // one buffer to another buffer, first deallocating
                          // any existing memory and then taking ownership of
                          // the resources of the other buffer, leaving the
                          // other buffer in a valid but unspecified state
  ptr_ = other.ptr_; // takes ownership of the resources of the other buffer by
                     // assigning its pointer to the current buffer's pointer
  size_ = other.size_;  // copies the size of the other buffer
  other.ptr_ = nullptr; // sets the pointer of the other buffer to nullptr to
                        // indicate that it no longer owns the resources
  other.size_ = 0; // sets the size of the other buffer to 0 to indicate that it
                   // no longer has any resources
  return *this;    // returns a reference to the current object
}

int main() {

  Buffer b1{1.0f, 2.0f, 3.0f}; // create a buffer with three float values
  PRINT_BUFFER(b1);            // print the contents of the buffer
  b1.printBuffer();            // print the contents of the buffer
  b1.printLocation(); // print the source location of the call for debugging
                      // purposes
  Buffer b2 = b1;   // copy constructor is called to create a new buffer b2 that
                    // is a copy of b1
  b2.printBuffer(); // print the contents of the copied buffer
  b1.printBuffer(); // print the contents of the original buffer to show that it
                    // is unchanged after the copy
  return 0;
}