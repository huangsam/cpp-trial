#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <algorithm>
#include <iostream>
#include <vector>

// ============================================================================
// 1. Custom Allocators for STL Containers
// ============================================================================

// Simple arena allocator for demonstration
class ArenaAllocator {
 private:
  char* buffer_;
  size_t size_;
  size_t offset_;

 public:
  explicit ArenaAllocator(size_t size);
  ~ArenaAllocator();

  void* allocate(size_t bytes, size_t alignment = alignof(std::max_align_t));
  void deallocate(void* ptr, size_t bytes);
  void reset();

  [[nodiscard]] size_t remaining_space() const;
};

// Custom allocator for STL containers
template <typename T>
class CustomAllocator {
 private:
  ArenaAllocator* arena_;

 public:
  using value_type = T;

  explicit CustomAllocator(ArenaAllocator* arena) : arena_(arena) {}

  T* allocate(size_t n) {
    return static_cast<T*>(arena_->allocate(n * sizeof(T), alignof(T)));
  }

  void deallocate(T* ptr, size_t n) { arena_->deallocate(ptr, n * sizeof(T)); }

  // Required for allocator compatibility
  template <typename U>
  CustomAllocator(const CustomAllocator<U>& other) : arena_(other.arena_) {}
};

// ============================================================================
// 2. Memory Pools
// ============================================================================

// Fixed-size memory pool for objects of type T
template <typename T, size_t BlockSize = 4096>
class MemoryPool {
 private:
  struct Block {
    char data[BlockSize];
    size_t used = 0;
    Block* next = nullptr;
  };

  Block* current_block_;
  size_t object_size_;
  size_t objects_per_block_;

 public:
  MemoryPool();
  ~MemoryPool();

  T* allocate();
  void deallocate(T* ptr);

 private:
  void add_block();
};

// ============================================================================
// 3. RAII Patterns
// ============================================================================

// RAII wrapper for file handles
class FileHandle {
 private:
  FILE* file_;

 public:
  explicit FileHandle(const char* filename, const char* mode);
  ~FileHandle();

  // Prevent copying
  FileHandle(const FileHandle&) = delete;
  FileHandle& operator=(const FileHandle&) = delete;

  // Allow moving
  FileHandle(FileHandle&& other) noexcept;
  FileHandle& operator=(FileHandle&& other) noexcept;

  [[nodiscard]] FILE* get() const { return file_; }
  explicit operator bool() const { return file_ != nullptr; }
};

// RAII timer for performance measurement
class Timer {
 private:
  std::chrono::high_resolution_clock::time_point start_;
  const char* label_;

 public:
  explicit Timer(const char* label);
  ~Timer();

  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
};

// ============================================================================
// 4. Placement New and Custom Memory Management
// ============================================================================

// Custom memory manager with placement new
class MemoryManager {
 private:
  char* buffer_;
  size_t size_;
  size_t used_;

 public:
  explicit MemoryManager(size_t size);
  ~MemoryManager();

  template <typename T, typename... Args>
  T* construct(Args&&... args) {
    void* mem = allocate(sizeof(T), alignof(T));
    if (!mem) return nullptr;
    return new (mem) T(std::forward<Args>(args)...);
  }

  template <typename T>
  void destroy(T* ptr) {
    if (ptr) {
      ptr->~T();
      // Note: memory is not deallocated in this simple example
    }
  }

 private:
  void* allocate(size_t bytes, size_t alignment);
};

// ============================================================================
// 5. Memory Alignment
// ============================================================================

// Aligned memory allocator
class AlignedAllocator {
 public:
  static void* allocate(size_t size, size_t alignment);
  static void deallocate(void* ptr);
};

// Cache-line aligned type
struct alignas(64) CacheLineAligned {
  int data[16];  // 64 bytes
};

// ============================================================================
// 6. Stack-based Memory Management
// ============================================================================

// Stack-based vector (fixed capacity)
template <typename T, size_t Capacity>
class StackVector {
 private:
  T data_[Capacity];
  size_t size_ = 0;

 public:
  void push_back(const T& value) {
    if (size_ < Capacity) {
      data_[size_++] = value;
    }
  }

  void push_back(T&& value) {
    if (size_ < Capacity) {
      data_[size_++] = std::move(value);
    }
  }

  T& operator[](size_t index) { return data_[index]; }
  const T& operator[](size_t index) const { return data_[index]; }

  [[nodiscard]] size_t size() const { return size_; }
  [[nodiscard]] size_t capacity() const { return Capacity; }
  [[nodiscard]] bool empty() const { return size_ == 0; }
};

// ============================================================================
// Demonstration Functions
// ============================================================================

void demonstrate_custom_allocators();
void demonstrate_memory_pools();
void demonstrate_raii_patterns();
void demonstrate_placement_new();
void demonstrate_memory_alignment();
void demonstrate_stack_memory();

#endif  // MEMORY_MANAGEMENT_H
