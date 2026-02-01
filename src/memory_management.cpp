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
  size_t current = reinterpret_cast<size_t>(buffer_ + offset_);
  size_t aligned = (current + alignment - 1) & ~(alignment - 1);
  size_t new_offset = aligned - reinterpret_cast<size_t>(buffer_) + bytes;

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
// 2. Memory Pools Implementation
// ============================================================================

template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::MemoryPool()
    : current_block_(nullptr),
      object_size_(sizeof(T)),
      objects_per_block_(BlockSize / sizeof(T)) {
  add_block();
}

template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::~MemoryPool() {
  while (current_block_) {
    Block* next = current_block_->next;
    delete current_block_;
    current_block_ = next;
  }
}

template <typename T, size_t BlockSize>
void MemoryPool<T, BlockSize>::add_block() {
  Block* new_block = new Block();
  new_block->next = current_block_;
  current_block_ = new_block;
}

template <typename T, size_t BlockSize>
T* MemoryPool<T, BlockSize>::allocate() {
  if (current_block_->used >= objects_per_block_) {
    add_block();
  }

  T* result = reinterpret_cast<T*>(current_block_->data +
                                   current_block_->used * object_size_);
  ++current_block_->used;
  return result;
}

template <typename T, size_t BlockSize>
void MemoryPool<T, BlockSize>::deallocate(T* /*ptr*/) {
  // Simple pool doesn't track individual deallocations
  // In a real implementation, you'd maintain a free list
}

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
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
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
  size_t current = reinterpret_cast<size_t>(buffer_ + used_);
  size_t aligned = (current + alignment - 1) & ~(alignment - 1);
  size_t new_used = aligned - reinterpret_cast<size_t>(buffer_) + bytes;

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
  CustomAllocator<int> alloc(&arena);

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
    FileHandle file("temp.txt", "w");
    if (file) {
      fprintf(file.get(), "Hello, RAII!");
    }
  }  // File automatically closed here

  std::cout << "File operation completed\n";
}

void demonstrate_placement_new() {
  std::cout << "=== Placement New ===\n";

  MemoryManager manager(1024);

  int* i = manager.construct<int>(42);
  double* d = manager.construct<double>(3.14);
  std::string* s = manager.construct<std::string>("Hello");

  std::cout << "Constructed: " << *i << ", " << *d << ", " << *s << "\n";

  manager.destroy(s);
  manager.destroy(d);
  manager.destroy(i);
}

void demonstrate_memory_alignment() {
  std::cout << "=== Memory Alignment ===\n";

  void* aligned_ptr = AlignedAllocator::allocate(64, 64);
  std::cout << "Allocated 64-byte aligned memory at: " << aligned_ptr << "\n";

  uintptr_t addr = reinterpret_cast<uintptr_t>(aligned_ptr);
  std::cout << "Address is " << (addr % 64 == 0 ? "" : "not ")
            << "64-byte aligned\n";

  AlignedAllocator::deallocate(aligned_ptr);

  CacheLineAligned cla;
  std::cout << "CacheLineAligned object at: " << &cla << "\n";
  uintptr_t cla_addr = reinterpret_cast<uintptr_t>(&cla);
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
  std::cout << "\nCapacity: " << stack_vec.capacity() << "\n";
}
