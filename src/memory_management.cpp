#include "memory_management.h"

#include <chrono>
#include <iostream>

// ============================================================================
// 1. Custom Allocators Implementation
// ============================================================================

ArenaAllocator::ArenaAllocator(size_t size) : size_(size), offset_(0) {
  buffer_ = new char[size];
  std::cout << "ArenaAllocator created with " << size << " bytes\n";
}

ArenaAllocator::~ArenaAllocator() {
  delete[] buffer_;
  std::cout << "ArenaAllocator destroyed\n";
}

void* ArenaAllocator::allocate(size_t bytes, size_t alignment) {
  const auto current = reinterpret_cast<size_t>(buffer_ + offset_);
  const auto aligned = (current + alignment - 1) & ~(alignment - 1);
  const auto new_offset = aligned - reinterpret_cast<size_t>(buffer_) + bytes;

  if (new_offset > size_) {
    return nullptr;  // Out of memory
  }

  void* result = buffer_ + (aligned - reinterpret_cast<size_t>(buffer_));
  offset_ = new_offset;
  return result;
}

void ArenaAllocator::deallocate(void* /*ptr*/, size_t /*bytes*/) {
  // Arena allocator doesn't deallocate individual blocks
  // Memory is freed when the arena is destroyed
}

void ArenaAllocator::reset() { offset_ = 0; }

size_t ArenaAllocator::remaining_space() const { return size_ - offset_; }

// ============================================================================
// 3. RAII Patterns Implementation
// ============================================================================

FileHandle::FileHandle(const char* filename, const char* mode)
    : file_(fopen(filename, mode)) {
  if (file_) {
    std::cout << "File opened: " << filename << "\n";
  }
}

FileHandle::~FileHandle() {
  if (file_) {
    fclose(file_);
    std::cout << "File closed\n";
  }
}

FileHandle::FileHandle(FileHandle&& other) noexcept : file_(other.file_) {
  other.file_ = nullptr;
}

FileHandle& FileHandle::operator=(FileHandle&& other) noexcept {
  if (this != &other) {
    if (file_) fclose(file_);
    file_ = other.file_;
    other.file_ = nullptr;
  }
  return *this;
}

Timer::Timer(const char* label)
    : start_(std::chrono::high_resolution_clock::now()), label_(label) {
  std::cout << "Timer started: " << label << "\n";
}

Timer::~Timer() {
  const auto end = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start_);
  std::cout << "Timer ended: " << label_ << " - " << duration.count()
            << " microseconds\n";
}

// ============================================================================
// 4. Placement New Implementation
// ============================================================================

MemoryManager::MemoryManager(size_t size) : size_(size), used_(0) {
  buffer_ = new char[size];
  std::cout << "MemoryManager created with " << size << " bytes\n";
}

MemoryManager::~MemoryManager() {
  delete[] buffer_;
  std::cout << "MemoryManager destroyed\n";
}

void* MemoryManager::allocate(size_t bytes, size_t alignment) {
  const auto current = reinterpret_cast<size_t>(buffer_ + used_);
  const auto aligned = (current + alignment - 1) & ~(alignment - 1);
  const auto new_used = aligned - reinterpret_cast<size_t>(buffer_) + bytes;

  if (new_used > size_) {
    return nullptr;
  }

  void* result = buffer_ + (aligned - reinterpret_cast<size_t>(buffer_));
  used_ = new_used;
  return result;
}

// ============================================================================
// 5. Memory Alignment Implementation
// ============================================================================

void* AlignedAllocator::allocate(size_t size, size_t alignment) {
  void* ptr = nullptr;
  if (posix_memalign(&ptr, alignment, size) != 0) {
    throw std::bad_alloc();
  }
  return ptr;
}

void AlignedAllocator::deallocate(void* ptr) { free(ptr); }

// ============================================================================
// Demonstration Functions
// ============================================================================

void demonstrate_custom_allocators() {
  std::cout << "=== Custom Allocators ===\n";

  ArenaAllocator arena(1024);
  const CustomAllocator<int> alloc(&arena);

  std::vector<int, CustomAllocator<int>> vec(alloc);
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  std::cout << "Vector size: " << vec.size() << "\n";
  std::cout << "Arena remaining space: " << arena.remaining_space()
            << " bytes\n";
}

void demonstrate_memory_pools() {
  std::cout << "=== Memory Pools ===\n";

  MemoryPool<int, 1024> pool;

  int* p1 = pool.allocate();
  int* p2 = pool.allocate();
  int* p3 = pool.allocate();

  *p1 = 10;
  *p2 = 20;
  *p3 = 30;

  std::cout << "Allocated values: " << *p1 << ", " << *p2 << ", " << *p3
            << "\n";
}

void demonstrate_raii_patterns() {
  std::cout << "=== RAII Patterns ===\n";

  {
    Timer timer("File operation");
    const FileHandle file("temp.txt", "w");
    if (file) {
      fprintf(file.get(), "Hello, RAII!");
    }
  }  // File automatically closed here

  std::cout << "File operation completed\n";
}

void demonstrate_placement_new() {
  std::cout << "=== Placement New ===\n";

  MemoryManager manager(1024);

  auto* i = manager.construct<int>(42);
  auto* d = manager.construct<double>(3.14);
  auto* s = manager.construct<std::string>("Hello");

  std::cout << "Constructed: " << *i << ", " << *d << ", " << *s << "\n";

  MemoryManager::destroy(s);
  MemoryManager::destroy(d);
  MemoryManager::destroy(i);
}

void demonstrate_memory_alignment() {
  std::cout << "=== Memory Alignment ===\n";

  auto* aligned_ptr = AlignedAllocator::allocate(64, 64);
  std::cout << "Allocated 64-byte aligned memory at: " << aligned_ptr << "\n";

  const auto addr = reinterpret_cast<uintptr_t>(aligned_ptr);
  std::cout << "Address is " << (addr % 64 == 0 ? "" : "not ")
            << "64-byte aligned\n";

  AlignedAllocator::deallocate(aligned_ptr);

  CacheLineAligned cla{};
  std::cout << "CacheLineAligned object at: " << &cla << "\n";
  const auto cla_addr = reinterpret_cast<uintptr_t>(&cla);
  std::cout << "Address is " << (cla_addr % 64 == 0 ? "" : "not ")
            << "cache-line aligned\n";
}

void demonstrate_stack_memory() {
  std::cout << "=== Stack Memory ===\n";

  StackVector<int, 10> stack_vec;

  for (int i = 0; i < 8; ++i) {
    stack_vec.push_back(i * 10);
  }

  std::cout << "Stack vector contents: ";
  for (size_t i = 0; i < stack_vec.size(); ++i) {
    std::cout << stack_vec[i] << " ";
  }
  std::cout << "\nCapacity: " << StackVector<int, 10>::capacity() << "\n";
}
