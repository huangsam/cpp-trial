# Source Directory (`src/`)

Welcome to the core implementation source tree of `cpp-trial`. This directory contains modular, domain-focused C++20 components demonstrating modern idioms, memory management patterns, standard library features, template metaprogramming, and concurrent systems programming.

## Architecture & Build System

All modules in `src/` are compiled into a shared static library target called `cpp_trial_core` via [src/CMakeLists.txt](CMakeLists.txt). This library is linked into:
- The demonstration executable: `main.out` (compiled from [src/main.cpp](main.cpp))
- The unit test suite: `test.out` (located in `test/`)
- Performance benchmarks: `*_bench.out` (located in `bench/`)

### Compiler & Toolchain Configuration
- **Standard**: C++20 (`set(CMAKE_CXX_STANDARD 20)` enabled globally)
- **Compiler Warnings**: Strict baseline flags (`-Wall -Wextra -Wpedantic -Wunused -Werror`)
- **Formatting**: Automated with `clang-format` (`cmake --build build --target format`)
- **Static Analysis**: Verified with `clang-tidy` integration (`-DWITH_CLANG_TIDY=ON`)

---

## Domain Modules

The source tree is divided into six domain directories. Each submodule has its own dedicated `README.md` detailing its design, code highlights, key takeaways, and test references:

| Module | Focus & Features | Deep Dive Guide |
|---|---|---|
| **[`oop/`](oop/)** | Strong types, validation wrappers, encapsulation, class hierarchies, virtual dispatch, runtime polymorphism, C++20 `std::formatter` | [oop/README.md](oop/README.md) |
| **[`types/`](types/)** | Modular namespaces, scoped enums (`enum class`), unions, `std::variant`, `std::optional`, `std::any`, `std::string_view`, structured bindings | [types/README.md](types/README.md) |
| **[`stl/`](stl/)** | C++20 three-way comparison (`<=>`), STL containers (`vector`, `map`, `set`), standard algorithms, C++20 ranges & views, file I/O with `std::filesystem` | [stl/README.md](stl/README.md) |
| **[`memory/`](memory/)** | `unique_ptr` with custom deleters, `shared_ptr`, `weak_ptr`, Rule of Zero/Five, move semantics, perfect forwarding, arena allocators, memory pools, alignment | [memory/README.md](memory/README.md) |
| **[`advanced/`](advanced/)** | Concepts & requires constraints, lambdas & functional composition, type traits (`std::void_t`), `constexpr`, fold expressions, variadics, CRTP, tag dispatch | [advanced/README.md](advanced/README.md) |
| **[`concurrency/`](concurrency/)** | Multithreading with `std::thread`, mutex synchronization, `lock_guard` RAII, atomic status flags, asynchronous tasks with `std::async` and `std::future` | [concurrency/README.md](concurrency/README.md) |

---

## Application Entrypoint (`main.cpp`)

[src/main.cpp](main.cpp) serves as an end-to-end integration harness exercising components across all six modules. It demonstrates:
- Date formatting and three-way comparisons
- Factorial calculation with template constraints
- Lambda comparisons and functional sum-of-squares
- Validated Person entity formatting
- Custom deleters for file I/O using `std::unique_ptr`
- Reference counting and circular reference breaking with `std::shared_ptr` / `std::weak_ptr`
- Memory arena allocation and RAII cleanup
- Move semantics resource consumption
- STL container filtering, counting, and intersection
- Namespace resolution and type-safe config parsing
- Thread-safe counting and async task dispatch

Run the main application:
```shell
cmake --preset dev
cmake --build --preset dev
./build/bin/main.out
```

---

## Coding Conventions Across `src/`

- **Type Safety over Primitives**: Use wrapper types (e.g., `Age`, `Salary`, `Year`, `Month`) with validation logic in constructors instead of passing raw primitives.
- **Resource Management (RAII)**: Own resources via smart pointers or dedicated RAII classes. Explicitly delete copy operations when implementing unique-ownership types.
- **`[[nodiscard]]`**: Apply to non-void getters, pure functions, and factory methods to prevent discarded return values.
- **Const Correctness**: Mark non-mutating member functions `const` and prefer `const auto` for immutable local variables.
- **Modern C++ Idioms**: Prefer C++20 ranges (`| std::views::filter`), `std::format`, `using enum`, concepts, and `std::from_chars` over legacy C-style idioms.

---

## Related Documentation

- [Project README](../README.md): Workspace overview, dependencies, and build instructions.
- [Curriculum Roadmap (LESSONS.md)](../LESSONS.md): Progressive, step-by-step learning syllabus guiding through each module.
