#ifndef FILE_IO_H
#define FILE_IO_H

#include <filesystem>
#include <string>
#include <vector>

// Class for file I/O operations
class FileIO {
 public:
  // Read entire file to string
  static std::string read_file_to_string(
      const std::filesystem::path& file_path);

  // Write string to file (overwrites)
  static void write_string_to_file(const std::filesystem::path& file_path,
                                   std::string_view content);

  // Read file line by line
  static std::vector<std::string> read_file_lines(
      const std::filesystem::path& file_path);

  // Write vector of strings to file
  static void write_lines_to_file(const std::filesystem::path& file_path,
                                  const std::vector<std::string>& lines);
};

#endif  // FILE_IO_H
