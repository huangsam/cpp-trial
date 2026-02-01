#ifndef MOVE_SEMANTICS_H
#define MOVE_SEMANTICS_H

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Example class demonstrating move semantics and the Rule of Five
class ResourceManager {
 private:
  std::vector<int> data_;

 public:
  ResourceManager();
  explicit ResourceManager(size_t size);
  ResourceManager(const ResourceManager& other);
  ResourceManager& operator=(const ResourceManager& other);
  ResourceManager(ResourceManager&& other) noexcept;
  ResourceManager& operator=(ResourceManager&& other) noexcept;
  ~ResourceManager();

  [[nodiscard]] size_t size() const { return data_.size(); }
  [[nodiscard]] const std::vector<int>& data() const { return data_; }
  void set_data(size_t index, int value);

  void consume_rvalue(std::vector<int>&& vec);
  ResourceManager create_large_resource(size_t size);
  static void demonstrate_move(ResourceManager& rm);
};

// Template function demonstrating perfect forwarding
template <typename T>
void process_resource(T&& resource) {
  auto processed = std::forward<T>(resource);
  std::cout << "Processed resource with " << processed.size() << " elements\n";
}

// Move-only type example (using Rule of Zero with smart pointers)
class MoveOnlyType {
 private:
  std::unique_ptr<std::string> data_;

 public:
  MoveOnlyType() : data_(std::make_unique<std::string>("default")) {}
  explicit MoveOnlyType(const std::string& str)
      : data_(std::make_unique<std::string>(str)) {}

  MoveOnlyType(MoveOnlyType&&) noexcept = default;
  MoveOnlyType& operator=(MoveOnlyType&&) noexcept = default;

  MoveOnlyType(const MoveOnlyType&) = delete;
  MoveOnlyType& operator=(const MoveOnlyType&) = delete;

  ~MoveOnlyType() = default;

  [[nodiscard]] const std::string& get_data() const { return *data_; }
};

// Utility functions for performance demonstration
std::chrono::nanoseconds measure_copy_time(size_t size);
std::chrono::nanoseconds measure_move_time(size_t size);
void demonstrate_move_vs_copy();

#endif  // MOVE_SEMANTICS_H
