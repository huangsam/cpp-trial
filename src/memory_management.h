#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <algorithm>
#include <chrono>
#include <cstdio>

// ============================================================================
// 1. Custom Allocators for STL Containers
// ============================================================================

// ArenaAllocator manages a contiguous block of memory for efficient allocation.
class ArenaAllocator {
 private:
  char* buffer_;
  size_t size_;
  size_t offset_;

 public:
  explicit ArenaAllocator(size_t size);
  ~ArenaAllocator();

  void* allocate(size_t bytes, size_t alignment = alignof(std::max_align_t));
  static void deallocate(void* ptr, size_t bytes);
  void reset();

  [[nodiscard]] size_t remaining_space() const;
};

// CustomAllocator is an STL-compatible allocator that delegates to an
// ArenaAllocator.
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

// MemoryPool maintains a pool of pre-allocated blocks for fast object
// allocation.
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

  void add_block() {
    Block* new_block = new Block();
    new_block->next = current_block_;
    current_block_ = new_block;
  }

 public:
  MemoryPool()
      : current_block_(nullptr),
        object_size_(sizeof(T)),
        objects_per_block_(BlockSize / sizeof(T)) {
    add_block();
  }

  ~MemoryPool() {
    while (current_block_) {
      Block* next = current_block_->next;
      delete current_block_;
      current_block_ = next;
    }
  }

  T* allocate() {
    if (current_block_->used >= objects_per_block_) {
      add_block();
    }
    T* result = reinterpret_cast<T*>(current_block_->data +
                                     current_block_->used * object_size_);
    ++current_block_->used;
    return result;
  }

  static void deallocate(T* /*ptr*/) {
    // Simple pool doesn't track individual deallocations
    // In a real implementation, you'd maintain a free list
  }
};

// ============================================================================
// 3. RAII Patterns
// ============================================================================

// FileHandle is an RAII wrapper that automatically manages FILE* resources.
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

// Timer is an RAII helper that measures elapsed time and prints the result on
// destruction.
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

// MemoryManager provides custom memory management with placement new for object
// construction.
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
  static void destroy(T* ptr) {
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

// AlignedAllocator provides memory allocation with configurable alignment for
// cache efficiency.
class AlignedAllocator {
 public:
  static void* allocate(size_t size, size_t alignment);
  static void deallocate(void* ptr);
};

// CacheLineAligned is an example of memory alignment for cache-line efficiency.
struct alignas(64) CacheLineAligned {
  int data[16];  // 64 bytes
};

// ============================================================================
// 6. Stack-based Memory Management
// ============================================================================

// StackVector is a fixed-capacity vector using stack allocation for small
// objects.
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
  [[nodiscard]] static size_t capacity() { return Capacity; }
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
