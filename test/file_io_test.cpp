#include "../src/file_io.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

class FileIOTest : public testing::Test {
 protected:
  std::filesystem::path temp_file_;

  void SetUp() override {
    temp_file_ = std::filesystem::temp_directory_path() / "test_file_io.txt";
  }

  void TearDown() override { std::filesystem::remove(temp_file_); }
};

TEST_F(FileIOTest, WriteAndReadString) {
  const std::string content = "Hello, World!\nThis is a test.";
  FileIO::write_string_to_file(temp_file_, content);
  const std::string read_content = FileIO::read_file_to_string(temp_file_);
  EXPECT_EQ(content, read_content);
}

TEST_F(FileIOTest, WriteAndReadLines) {
  const std::vector<std::string> lines = {"Line 1", "Line 2", "Line 3"};
  FileIO::write_lines_to_file(temp_file_, lines);
  const std::vector<std::string> read_lines =
      FileIO::read_file_lines(temp_file_);
  EXPECT_EQ(lines, read_lines);
}

TEST_F(FileIOTest, ReadNonExistentFileThrows) {
  const std::filesystem::path non_existent = "non_existent_file.txt";
  EXPECT_THROW(FileIO::read_file_to_string(non_existent), std::runtime_error);
}

TEST_F(FileIOTest, WriteToInvalidPathThrows) {
  const std::filesystem::path invalid_path = "/invalid/path/file.txt";
  EXPECT_THROW(FileIO::write_string_to_file(invalid_path, "test"),
               std::runtime_error);
}
