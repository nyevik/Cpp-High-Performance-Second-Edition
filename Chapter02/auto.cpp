
#include <gtest/gtest.h>
#include <vector>

namespace old_syntax {

class Foo {
public:
  int val() const { return m_; }

  const int &cref() const { return m_; }

  int &mref() { return m_; }

private:
  int m_{};
};

} // namespace old_syntax

namespace new_syntax {

class Foo {
public:
  auto val() const -> int { return m_; }

  auto &cref() const { return m_; }
  auto cref_trailing() const -> const int& { return m_; }
  auto &mref() { return m_; }
  auto mref_trailing() -> int& { return m_; }

  void some_func(const std::string& a, const std::string & b) {
    const auto& c = a + b; // c is a const reference to the result of a + b
    //auto& d = a + b; // d is a non-const reference to the result of a + b, which is not valid and will cause a compilation error
  }

private: 
  int m_{};
};

} // namespace new_syntax

TEST(Auto, ConstAndMutableReference) {
  auto foo = new_syntax::Foo{};
  auto &cref = foo.cref(); // cref is a const reference
  auto &cref_trailing = foo.cref_trailing(); // cref_trailing is also a const reference
  auto &mref = foo.mref(); // mref is a mutable reference
  mref =foo.mref_trailing();

  static_assert(std::is_const_v<std::remove_reference_t<decltype(cref)>>, "");
  static_assert(!std::is_const_v<std::remove_reference_t<decltype(mref)>>, "");
}
