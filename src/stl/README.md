# Standard Template Library & Collections (`src/stl/`)

This directory explores the Standard Template Library (STL) in C++20, spanning value semantics, custom operators, container idioms, algorithmic transformations, C++20 ranges/views, and file system I/O.

## Files & Components

| Component | Focus & Role |
|---|---|
| **[`date.h`](date.h)** · [`cpp`](date.cpp) | Value semantics, spaceship comparisons (`<=>`), and formatting |
| **[`stl_deep_dive.h`](stl_deep_dive.h)** · [`cpp`](stl_deep_dive.cpp) | Containers, algorithms, and lazy ranges/views pipelines |
| **[`file_io.h`](file_io.h)** · [`cpp`](file_io.cpp) | Fast buffer I/O, line streaming, and filesystem path operations |

---

## Realistic Engineering Goals: Value Semantics & Zero-Copy Streams

The Standard Template Library in modern C++ is not just a collection of data structures. It represents a unified philosophy of **contiguous memory layout, value semantics, and composable zero-allocation pipelines**:

| Traditional Container Usage | Modern C++ STL ([src/stl/](.)) | Production Benefit |
|---|---|---|
| Overloading six relational operators (`<`, `<=`, `>`, `>=`, `==`, `!=`) | Spaceship Operator (`operator<=>`) | Synthesizes consistent, bug-free ordering comparisons in a single `constexpr` function. |
| Nested loops creating intermediate vectors | C++20 Ranges & Views (`std::views::filter`) | Lazy evaluation: stream transformations happen on-the-fly without allocating intermediate heap vectors. |
| Manual byte-by-byte file read loops | Stream buffer iterators (`std::istreambuf_iterator`) | Reads entire files into contiguous memory buffers with minimal kernel-to-user space copy overhead. |

---

## Detailed Topic Guides

### 1. Date & Three-Way Comparison (`date.h`)

#### Validated Primitive Wrappers
Avoid "primitive obsession" by scoping domain validations directly into strong parameter types:

```cpp
struct Year  { explicit Year(int year);   /* >= 1 */ };
struct Month { explicit Month(int month); /* 1..12 */ };
struct Day   { explicit Day(int day);     /* 1..31 */ };
```

#### C++20 Spaceship Operator (`<=>`)
Instead of manually overloading all six relational operators (`<`, `<=`, `>`, `>=`, `==`, `!=`), C++20 simplifies this to a single three-way comparison:

```cpp
class Date {
  // Synthesizes <, <=, >, >= comparisons automatically
  friend constexpr auto operator<=>(const Date& lhs, const Date& rhs) {
    if (auto cmp = lhs.get_year() <=> rhs.get_year(); cmp != 0) return cmp;
    if (auto cmp = lhs.get_month() <=> rhs.get_month(); cmp != 0) return cmp;
    return lhs.get_day() <=> rhs.get_day();
  }

  // Synthesizes == and !=
  friend constexpr bool operator==(const Date& lhs, const Date& rhs) = default;
};
```

---

### 2. STL Deep Dive: Containers, Algorithms & Ranges (`stl_deep_dive.h`)

#### Composable C++20 Ranges & Views
C++20 ranges allow lazy transformations chained with Unix-like pipe (`|`) syntax without intermediate container allocations:

```cpp
// Filter even numbers lazily
auto even_view = numbers | std::views::filter([](const int n) constexpr {
  return n % 2 == 0;
});
return {even_view.begin(), even_view.end()};

// Transform elements
auto transformed_view = numbers | std::views::transform([](const int n) {
  return n * 2;
});
```

#### Constrained Algorithms (`std::ranges`)
Modern algorithms accept ranges directly instead of explicit `begin()` / `end()` iterator pairs:

```cpp
std::ranges::sort(numbers);
bool found = std::ranges::find(numbers, target) != numbers.end();

// Finding maximum entry in a map
const auto max_it = std::ranges::max_element(
    word_count, [](const auto& a, const auto& b) constexpr {
      return a.second < b.second;
    });
```

---

### 3. File Input/Output & Filesystem (`file_io.h`)

#### Fast Bulk File Reading
Using stream buffer iterators loads the full file content into a contiguous string buffer with minimal copying:

```cpp
std::string FileIO::read_file_to_string(const std::filesystem::path& file_path) {
  std::ifstream file(file_path, std::ios::in | std::ios::binary);
  if (!file) throw std::runtime_error("Failed to open file: " + file_path.string());
  return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}
```

#### Cross-Platform Filesystem Integration (`std::filesystem`)
Handles path normalization, subfolder creation, and portable file paths:

```cpp
std::filesystem::path FileIO::get_test_data_path(const std::string& filename) {
  const std::filesystem::path base_path = TEST_DATA_DIR;
  if (!std::filesystem::exists(base_path)) {
    std::filesystem::create_directories(base_path);
  }
  return base_path / filename;
}
```

---

## Key Learnings & Systems Insights

- **Views are Lazy**: `std::views::filter` does not compute or allocate memory until iterated over. If you need a persistent collection, materialize the view into a container (e.g., `std::vector`).
- **Binary I/O for Determinism**: When reading and writing raw buffers or structured text across operating systems (macOS, Linux, Windows), use `std::ios::binary` to avoid newline translation issues.
- **Backend Relevance**:
  - Processing streaming server logs with range pipelines reduces memory pressure.
  - Frequency tracking with `std::map` / `std::unordered_map` forms the basis of caching, rate limiting, and metrics aggregation.

---

## Running Associated Tests

Unit tests for this module are located in `test/stl/`:
- [test/stl/date_test.cpp](../../test/stl/date_test.cpp)
- [test/stl/stl_deep_dive_test.cpp](../../test/stl/stl_deep_dive_test.cpp)
- [test/stl/file_io_test.cpp](../../test/stl/file_io_test.cpp)

Run tests via CMake:
```shell
ctest --preset dev -R "DateTest|STLDeepDiveTest|FileIOTest" --output-on-failure
```
