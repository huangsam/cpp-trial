#include "file_io.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

std::string FileIO::read_file_to_string(const std::filesystem::path& file_path) {
  std::ifstream file(file_path, std::ios::in | std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to open file for reading: " + file_path.string());
  }
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return content;
}

void FileIO::write_string_to_file(const std::filesystem::path& file_path, const std::string& content) {
  std::ofstream file(file_path, std::ios::out | std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to open file for writing: " + file_path.string());
  }
  file << content;
}

std::vector<std::string> FileIO::read_file_lines(const std::filesystem::path& file_path) {
  std::ifstream file(file_path);
  if (!file) {
    throw std::runtime_error("Failed to open file for reading: " + file_path.string());
  }
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
}

void FileIO::write_lines_to_file(const std::filesystem::path& file_path, const std::vector<std::string>& lines) {
  std::ofstream file(file_path);
  if (!file) {
    throw std::runtime_error("Failed to open file for writing: " + file_path.string());
  }
  for (const auto& line : lines) {
    file << line << '\n';
  }
}