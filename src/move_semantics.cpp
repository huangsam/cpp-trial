#include "move_semantics.h"

// ResourceManager implementations
ResourceManager::ResourceManager() : data_() {
  std::cout << "ResourceManager default constructed\n";
}

ResourceManager::ResourceManager(size_t size) : data_(size, 0) {
  std::cout << "ResourceManager constructed with size " << size << "\n";
}

ResourceManager::ResourceManager(const ResourceManager& other)
    : data_(other.data_) {
  std::cout << "ResourceManager copy constructed (expensive deep copy)\n";
}

ResourceManager& ResourceManager::operator=(const ResourceManager& other) {
  if (this != &other) {
    data_ = other.data_;
    std::cout << "ResourceManager copy assigned (expensive deep copy)\n";
  }
  return *this;
}

ResourceManager::ResourceManager(ResourceManager&& other) noexcept
    : data_(std::move(other.data_)) {
  std::cout << "ResourceManager move constructed (cheap transfer)\n";
}

ResourceManager& ResourceManager::operator=(ResourceManager&& other) noexcept {
  if (this != &other) {
    data_ = std::move(other.data_);
    std::cout << "ResourceManager move assigned (cheap transfer)\n";
  }
  return *this;
}

ResourceManager::~ResourceManager() {
  std::cout << "ResourceManager destroyed\n";
}

void ResourceManager::set_data(size_t index, int value) {
  if (index < data_.size()) {
    data_[index] = value;
  }
}

void ResourceManager::consume_rvalue(std::vector<int>&& vec) {
  data_ = std::move(vec);
  std::cout << "Consumed rvalue vector with " << data_.size() << " elements\n";
}

ResourceManager ResourceManager::create_large_resource(size_t size) {
  ResourceManager rm(size);
  for (size_t i = 0; i < size; ++i) {
    rm.set_data(i, static_cast<int>(i));
  }
  return rm;
}

void ResourceManager::demonstrate_move(ResourceManager& rm) {
  ResourceManager new_rm = std::move(rm);
  std::cout << "Moved resource with " << new_rm.size() << " elements\n";
}

// Performance measurement functions
std::chrono::nanoseconds measure_copy_time(size_t size) {
  ResourceManager source(size);
  auto start = std::chrono::high_resolution_clock::now();
  ResourceManager copy = source;
  auto end = std::chrono::high_resolution_clock::now();
  return end - start;
}

std::chrono::nanoseconds measure_move_time(size_t size) {
  ResourceManager source(size);
  auto start = std::chrono::high_resolution_clock::now();
  ResourceManager moved = std::move(source);
  auto end = std::chrono::high_resolution_clock::now();
  return end - start;
}

void demonstrate_move_vs_copy() {
  std::cout << "\n=== Move vs Copy Demonstration ===\n";

  constexpr size_t test_size = 100000;

  auto copy_time = measure_copy_time(test_size);
  std::cout << "Copy time for " << test_size
            << " elements: " << copy_time.count() << " nanoseconds\n";

  auto move_time = measure_move_time(test_size);
  std::cout << "Move time for " << test_size
            << " elements: " << move_time.count() << " nanoseconds\n";

  std::cout << "Move is approximately "
            << static_cast<double>(copy_time.count()) / move_time.count()
            << "x faster\n";

  std::cout << "\nWhen to use move vs copy:\n";
  std::cout << "- Use move when the source object will not be used again\n";
  std::cout << "- Use copy when you need to preserve the original object\n";
  std::cout
      << "- Move is especially beneficial for large objects or containers\n";
}
