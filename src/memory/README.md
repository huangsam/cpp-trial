# Modern Memory Management (`src/memory/`)

This directory covers modern C++ memory management, ranging from safe RAII ownership with smart pointers to high-performance zero-copy move semantics and custom memory allocators.

## Files & Components

| File | Purpose | Key Features |
|---|---|---|
| [smart_pointers.h](smart_pointers.h) / [smart_pointers.cpp](smart_pointers.cpp) | Safe Ownership & Lifetime | `std::unique_ptr` with custom deleters, `std::shared_ptr`, `std::weak_ptr` cycle breaking, Rule of Zero, factory functions |
| [move_semantics.h](move_semantics.h) / [move_semantics.cpp](move_semantics.cpp) | Value Semantics & Resource Stealing | Rule of Five (`ResourceManager`), rvalue references (`&&`), `std::move`, perfect forwarding (`std::forward`), move-only types |
| [memory_management.h](memory_management.h) / [memory_management.cpp](memory_management.cpp) | High-Performance Allocators | `ArenaAllocator`, STL `CustomAllocator<T>`, `MemoryPool<T>`, placement `new`, cache alignment (`alignas(64)`), `StackVector` |

---

## Realistic Engineering Goals: Deterministic Ownership Without a GC

In garbage-collected environments (Java, Python, Go), developers don't track object ownership—a runtime background collector sweeps memory periodically. In legacy C, developers manually paired `malloc()` and `free()`, resulting in notorious leaks, double-frees, and use-after-free vulnerabilities.

Modern C++ rejects both approaches. Instead, it achieves **deterministic ownership** with zero runtime GC pauses through three tiers of memory control demonstrated in this module:

| Memory Tier | Mechanism | Production Purpose |
|---|---|---|
| **Tier 1: Smart Pointers** | `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr` | Explicit ownership semantics; memory is freed deterministically at scope exit without leaks. |
| **Tier 2: Move Semantics** | Rvalue references (`&&`), `std::move` | Steals buffer pointers instead of duplicating expensive heap allocations during data transfer. |
| **Tier 3: Custom Allocators** | `ArenaAllocator`, `MemoryPool<T>`, `alignas(64)` | Bypasses general-purpose OS heap locks for low-latency, high-frequency allocation loops. |

---

## Detailed Topic Guides

### 1. Smart Pointers & Custom Deleters (`smart_pointers.h`)

#### Custom Deleters with `std::unique_ptr`
Encapsulate C APIs (like `FILE*` or OS sockets) in RAII wrappers without manual cleanup code:

```cpp
struct FileDeleter {
  void operator()(FILE* file) const {
    if (file) fclose(file);
  }
};

class FileHandler {
  std::unique_ptr<FILE, FileDeleter> file_;
 public:
  explicit FileHandler(const std::filesystem::path& filename)
      : file_(fopen(filename.string().c_str(), "w+"), FileDeleter{}) {}
};
```

#### Breaking Cycles with `std::weak_ptr`
Cyclic dependencies between `std::shared_ptr` instances create memory leaks because reference counts never reach zero. `std::weak_ptr` provides a non-owning reference:

```cpp
class Parent {
  std::weak_ptr<Child> child_; // Does not increment reference count
};

class Child {
  std::weak_ptr<Parent> parent_;
};
```

#### The Rule of Zero
Classes managing resources through smart pointers do not need custom destructors, copy, or move operations:

```cpp
class SmartContainer {
  std::vector<std::unique_ptr<std::string>> resources_;
 public:
  SmartContainer() = default;
  ~SmartContainer() = default;
  // Compiler synthesizes correct move and delete copy automatically
};
```

---

### 2. Move Semantics & Perfect Forwarding (`move_semantics.h`)

#### The Rule of Five (`ResourceManager`)
When managing a resource manually, define all five special member functions:

```cpp
class ResourceManager {
  std::vector<int> data_;
 public:
  ResourceManager(const ResourceManager& other);                // Copy Constructor
  ResourceManager& operator=(const ResourceManager& other);     // Copy Assignment
  ResourceManager(ResourceManager&& other) noexcept;            // Move Constructor
  ResourceManager& operator=(ResourceManager&& other) noexcept; // Move Assignment
  ~ResourceManager();                                           // Destructor
};
```

#### Perfect Forwarding
`std::forward` preserves the value category (lvalue or rvalue) of arguments in generic code:

```cpp
template <typename T>
void process_resource(T&& resource) {
  auto processed = std::forward<T>(resource);
  // Calls move or copy constructor depending on whether 'resource' was an rvalue or lvalue
}
```

---

### 3. Custom Memory Management & Allocation Patterns (`memory_management.h`)

#### Contiguous Arena Allocators
Bumps a memory pointer for rapid allocation and clears entire arenas in $O(1)$:

```cpp
void* ArenaAllocator::allocate(size_t bytes, size_t alignment) {
  size_t current_address = reinterpret_cast<size_t>(buffer_ + offset_);
  size_t padding = (alignment - (current_address % alignment)) % alignment;
  if (offset_ + padding + bytes > size_) return nullptr;
  offset_ += padding;
  void* ptr = buffer_ + offset_;
  offset_ += bytes;
  return ptr;
}
```

#### Chunk-Based Memory Pools (`MemoryPool<T>`)
Pre-allocates chunks of memory for fixed-size objects, eliminating heap fragmentation in high-frequency allocation loops.

#### Cache-Line Alignment (`alignas(64)`)
Prevents false sharing across CPU cores by aligning critical buffers to 64-byte hardware cache line boundaries:

```cpp
struct alignas(64) CacheLineAligned {
  int data[16]; // Fits squarely within a single 64-byte L1 cache line
};
```

#### Stack Allocation (`StackVector<T, Capacity>`)
Keeps small collections on the stack, bypassing heap allocation entirely:

```cpp
template <typename T, size_t Capacity>
class StackVector {
  T data_[Capacity];
  size_t size_ = 0;
};
```

---

## Key Learnings & Systems Insights

- **`noexcept` on Move Operations**: Always declare move constructors and move assignment operators `noexcept`. Standard library containers (e.g., `std::vector::reserve`) fall back to copying if the move constructor might throw.
- **Moved-from State**: An object after being moved is in a valid but unspecified state. Reset or reassign before reusing it.
- **Backend Relevance**:
  - Connection pools and request lifecycles leverage arena allocators to deallocate all per-request objects at once.
  - Move semantics prevent expensive deep copies of large JSON bodies or network buffers during message dispatch.

---

## Running Associated Tests & Benchmarks

Unit tests:
- [test/memory/smart_pointers_test.cpp](../../test/memory/smart_pointers_test.cpp)
- [test/memory/move_semantics_test.cpp](../../test/memory/move_semantics_test.cpp)
- [test/memory/memory_management_test.cpp](../../test/memory/memory_management_test.cpp)

```shell
ctest --preset dev -R "SmartPointersTest|ResourceManagerTest|MoveOnlyTypeTest|MemoryManagementTest" --output-on-failure
```

Performance benchmarks:
- [bench/memory_management_bench.cpp](../../bench/memory_management_bench.cpp)
- [bench/move_semantics_bench.cpp](../../bench/move_semantics_bench.cpp)

```shell
cmake --preset release && cmake --build --preset release
./build/bin/bench/memory_management_bench.out
./build/bin/bench/move_semantics_bench.out
```
