#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

namespace {

bool read_stream_into_string(std::istream& in, std::string& content,
                             std::ostream& err) {
  const auto size_pos = in.tellg();
  if (size_pos == std::streampos(-1)) {
    err << "Failed to determine file size" << std::endl;
    return false;
  }

  const auto size = static_cast<std::size_t>(size_pos);
  content.assign(size, '\0');

  in.seekg(0);
  if (size > 0) {
    in.read(content.data(), static_cast<std::streamsize>(size));
  }

  return true;
}

int print_file_contents(const std::string& path, std::ostream& out,
                        std::ostream& err) {
  auto in = std::ifstream(path, std::ios::in | std::ios::ate);
  if (in.fail()) {
    err << "Failed to open input file" << std::endl;
    return 1;
  }

  auto content = std::string{};
  if (!read_stream_into_string(in, content, err)) {
    return 1;
  }

  out << content << std::endl;
  return EXIT_SUCCESS;
}

class MyFileBasicString : public testing::Test {
protected:
  std::string create_file(const std::string& filename,
                          const std::string& content = {}) {
    files_to_remove_.push_back(filename);

    auto out = std::ofstream{filename};
    if (!out) {
      ADD_FAILURE() << "Failed to create test file: " << filename;
      return filename;
    }

    out << content;
    return filename;
  }

  void TearDown() override {
    for (const auto& filename : files_to_remove_) {
      std::remove(filename.c_str());
    }
  }

private:
  std::vector<std::string> files_to_remove_{};
};

TEST_F(MyFileBasicString, PrintsNonEmptyFileContents) {
  const auto filename =
      create_file("my_file_basic_string_multiline.txt", "Hello\nGoogle Test!");

  auto out = std::ostringstream{};
  auto err = std::ostringstream{};

  const auto rc = print_file_contents(filename, out, err);

  ASSERT_EQ(EXIT_SUCCESS, rc);
  ASSERT_EQ("Hello\nGoogle Test!\n", out.str());
  ASSERT_TRUE(err.str().empty());
}

TEST_F(MyFileBasicString, ReportsMissingInputFile) {
  constexpr auto kMissingFile = "my_file_basic_string_missing.txt";
  std::remove(kMissingFile);

  auto out = std::ostringstream{};
  auto err = std::ostringstream{};

  const auto rc = print_file_contents(kMissingFile, out, err);

  ASSERT_EQ(1, rc);
  ASSERT_TRUE(out.str().empty());
  ASSERT_EQ("Failed to open input file\n", err.str());
}

TEST_F(MyFileBasicString, PrintsNewlineForEmptyFile) {
  const auto filename = create_file("my_file_basic_string_empty.txt");

  auto out = std::ostringstream{};
  auto err = std::ostringstream{};

  const auto rc = print_file_contents(filename, out, err);

  ASSERT_EQ(EXIT_SUCCESS, rc);
  ASSERT_EQ("\n", out.str());
  ASSERT_TRUE(err.str().empty());
}

TEST(MyFileBasicStringHelpers, ReportsFailureWhenTellgCannotDetermineSize) {
  auto in = std::stringstream{"content"};
  in.setstate(std::ios::failbit);

  auto content = std::string{};
  auto err = std::ostringstream{};

  const auto success = read_stream_into_string(in, content, err);

  ASSERT_FALSE(success);
  ASSERT_TRUE(content.empty());
  ASSERT_EQ("Failed to determine file size\n", err.str());
}

} // namespace
