# Type System & Safety (`src/types/`)

This directory explores type organization, safety, and modern vocabulary types in C++17 and C++20, contrasting legacy C-style idioms with modern alternatives that eliminate undefined behavior and runtime type crashes.

## Files & Components

| Component | Focus & Role |
|---|---|
| **[`namespaces.h`](namespaces.h)** · [`cpp`](namespaces.cpp) | Nested namespaces, aliases, and symbol pollution prevention |
| **[`enums_unions.h`](enums_unions.h)** · [`cpp`](enums_unions.cpp) | Scoped enums, union memory sharing, and type-safe variants |
| **[`type_safety.h`](type_safety.h)** · [`cpp`](type_safety.cpp) | Modern vocabulary types, string views, and structured bindings |

---

## Realistic Engineering Goals: Why Modern C++ Replaces C-Style Idioms

In legacy C and pre-C++17 codebases, types were often treated casually—raw pointers represented "optional" values, integers doubled as error codes, and untyped unions shared memory blindly. Modern C++ provides explicit vocabulary types that eliminate these classic sources of production crashes:

| Legacy / C-Style Idiom | Modern C++ Replacement | Problem Solved |
|---|---|---|
| Null pointers (`nullptr`) for missing data | `std::optional<T>` | Eliminates null pointer dereference crashes; forces explicit handling of the absent case at compile time. |
| Raw C-unions (`union Data`) | `std::variant<...>` | Prevents undefined behavior from reading the wrong union member; manages constructors and destructors safely. |
| Integer error codes (`-1`, `errno`) | `Result` (`std::variant<T, Error>`) | Unambiguous error signaling without throwing exceptions or risking unchecked error codes. |
| Passing `const std::string&` | `std::string_view` | Avoids heap allocation when inspecting string literals or substrings. |

---

## Detailed Topic Guides

### 1. Namespaces & Scoping (`namespaces.h`)

#### Nested Namespaces & Aliasing
Namespaces partition symbol tables to prevent collisions across libraries:

```cpp
namespace utils {
namespace math {
  constexpr int add(int a, int b) { return a + b; }
}
}

// In client code:
namespace um = utils::math; // Namespace alias
int sum = um::add(5, 10);
```

#### Header Best Practices
Never place `using namespace ...` or global `using` declarations in header files. Doing so injects symbols into every translation unit that includes the header (flagged by Clang-Tidy's `google-global-names-in-headers`).

---

### 2. Enums, Unions, and `std::variant` (`enums_unions.h`)

#### Scoped vs Unscoped Enums
- **Unscoped Enums (`enum Color`)**: Implicitly convert to integers and pollute the enclosing namespace.
- **Scoped Enums (`enum class Status`)**: Strongly typed; conversions require `static_cast`, and values are accessed via their scope (`Status::Idle`).

#### Tagged Unions vs `std::variant`
Raw C-unions share memory across members without tracking which type is currently active. Tagged unions manually pair an enum discriminant with the union:

```cpp
struct TaggedData {
  enum class Type { Int, Double, Char } type;
  Data data{};

  std::string to_string() const {
    switch (type) {
      using enum Type; // C++20 using enum avoids repeating 'Type::'
      case Int:    return std::format("Int: {}", data.int_value);
      case Double: return std::format("Double: {}", data.double_value);
      case Char:   return std::format("Char: {}", data.char_value);
    }
  }
};
```

**Modern Alternative (`std::variant`)**: `std::variant` provides a type-safe union with compile-time safety and automatic destructor management:

```cpp
using VariantData = std::variant<int, double, char>;

std::string variant_to_string(const VariantData& var) {
  return std::visit(
      []<typename T>(T&& arg) -> std::string {
        using DecayedT = std::decay_t<T>;
        if constexpr (std::is_same_v<DecayedT, int>) {
          return std::format("Int: {}", arg);
        } else if constexpr (std::is_same_v<DecayedT, double>) {
          return std::format("Double: {}", arg);
        } else if constexpr (std::is_same_v<DecayedT, char>) {
          return std::format("Char: {}", arg);
        }
        return "Unknown type";
      },
      var);
}
```

---

### 3. Modern Type Safety Features (`type_safety.h`)

#### Optional Values (`std::optional<T>`)
Expresses nullable returns without sentinel values (`-1`, `nullptr`):

```cpp
std::optional<int> find_value(const std::map<std::string, int>& data, std::string_view key) {
  if (const auto it = data.find(std::string(key)); it != data.end()) {
    return it->second;
  }
  return std::nullopt;
}
```

#### Non-Allocating Strings (`std::string_view`)
Passes lightweight references (pointer + size) to string buffers without heap allocations:

```cpp
void process_string(std::string_view sv); // Zero copies when passed std::string or "literal"
```

#### Structured Bindings & Fast Numeric Parsing (`std::from_chars`)
Decompose structures and parse numbers without locale overhead or exception throws:

```cpp
std::optional<Point> parse_point(std::string_view input) {
  const size_t comma = input.find(',');
  if (comma == std::string_view::npos) return std::nullopt;

  int x, y;
  if (auto [ptr, ec] = std::from_chars(input.data(), input.data() + comma, x); ec != std::errc{})
    return std::nullopt;

  if (auto [ptr, ec] = std::from_chars(input.data() + comma + 1, input.data() + input.size(), y); ec != std::errc{})
    return std::nullopt;

  return Point{.x = x, .y = y};
}
```

#### Functional Error Handling (`Result` Pattern)
Eliminates overhead and control flow disruption of exceptions in expected failure cases:

```cpp
enum class Error { InvalidInput, DivisionByZero, NotFound };
using Result = std::variant<std::string, Error>;

Result safe_divide(int a, int b) {
  if (b == 0) return Error::DivisionByZero;
  return std::format("Result: {}", a / b);
}
```

---

## Key Learnings & Systems Insights

- **Prefer `std::variant` over Raw Unions**: Unions cannot safely hold non-trivial types (like `std::string`) without complex placement new and explicit destructor mechanics. `std::variant` handles this automatically.
- **Lifetime Risks with `std::string_view`**: Never return a `string_view` referencing a temporary string; it does not extend the lifetime of the underlying buffer.
- **Backend Relevance**:
  - Configuration loaders parsing heterogeneous types (`int`, `string`, `bool`) benefit from `std::variant`.
  - High-throughput parsers (JSON, HTTP headers, telemetry) leverage `std::string_view` and `std::from_chars` for zero-allocation parsing.

---

## Running Associated Tests

Unit tests for this module are located in `test/types/`:
- [test/types/namespaces_test.cpp](../../test/types/namespaces_test.cpp)
- [test/types/enums_unions_test.cpp](../../test/types/enums_unions_test.cpp)
- [test/types/type_safety_test.cpp](../../test/types/type_safety_test.cpp)

Run tests via CMake:
```shell
ctest --preset dev -R "NamespacesTest|EnumsUnionsTest|TypeSafetyTest" --output-on-failure
```
