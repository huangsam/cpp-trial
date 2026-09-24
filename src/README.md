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

## Architectural Goals & The Modern C++ Mindset

Modern C++ is often perceived as verbose or intimidating when compared to high-level scripting languages. However, in C++, **verbosity is not boilerplate—it represents explicit engineering control**:

1. **Deterministic Lifetime over Garbage Collection**:
   - There are no background GC pauses or mark-and-sweep cycles.
   - Resource cleanup is tied strictly to scope exit via **RAII** (Resource Acquisition Is Initialization). Smart pointers (`std::unique_ptr`, `std::shared_ptr`) automate memory reclamation without runtime overhead.

2. **Compile-Time Safety over Runtime Exception Recovery**:
   - Instead of passing raw primitive types (`int`, `double`) and hoping runtime callers provide valid values, we use strong wrapper types (`Age`, `Salary`, `Year`, `Month`) with explicit constructors.
   - Modifiers like `explicit`, `[[nodiscard]]`, `const`, and `noexcept` turn common human oversights (like swapped parameters or ignored return values) into immediate compiler errors.

3. **Zero-Cost Abstractions over Layered Indirection**:
   - High-level constructs like C++20 range pipelines (`| std::views::filter`) and compile-time templates compile down to the exact same assembly as handwritten pointer loops.
   - You get declarative, readable code without paying runtime performance penalties.

---

## Domain Modules

The source tree is divided into six domain directories. Each submodule has its own dedicated `README.md` detailing its design, code highlights, key takeaways, and test references:

| Module & Guide | Core Domain Focus |
|---|---|
| **[`oop/`](oop/README.md)** | Encapsulation, strong parameter validation, class hierarchies, and runtime polymorphism |
| **[`types/`](types/README.md)** | Namespace scoping, scoped enumerations, type-safe variants, and modern vocabulary types |
| **[`stl/`](stl/README.md)** | Synthesized comparisons, standard containers, constrained algorithms, and lazy range views |
| **[`memory/`](memory/README.md)** | Smart pointer ownership, zero-copy move semantics, arena allocators, and memory pools |
| **[`advanced/`](advanced/README.md)** | Concepts and constraints, functional closures, compile-time introspection, and static polymorphism |
| **[`concurrency/`](concurrency/README.md)** | Native thread lifecycle, critical section synchronization, lock-free atomics, and async futures |

---

## Application Entrypoint (`main.cpp`)

[src/main.cpp](main.cpp) serves as an end-to-end integration harness exercising components across all six modules. It organizes demonstrations into three cohesive system areas:

- **Domain Models & Type Safety**: Validated `Person` formatting via `std::format`, C++20 `Date` spaceship comparisons (`<=>`), and type-safe `ConfigValue` variants with `std::visit`.
- **Memory Architecture & Lifetimes**: Custom `unique_ptr` file deleters, cycle-breaking `shared_ptr`/`weak_ptr` relationships, scoped `ArenaAllocator` regions, and `ResourceManager` move semantics.
- **Algorithms & Concurrent Tasks**: C++20 range filtering and transforms, `sum_of_squares` lambda closures, `SafeCounter` thread synchronization with mutexes, and `std::async` worker offloading.

Run the main application:
```shell
cmake --preset dev
cmake --build --preset dev
./build/bin/main.out
```

---

## Coding Conventions Across `src/`

| Convention | Modern C++ Idiom | Engineering Rationale |
|---|---|---|
| **Strong Typing** | Dedicated structs (`Age`, `Salary`, `Year`) | Prevents primitive obsession and catches swapped or invalid arguments at construction. |
| **Deterministic RAII** | `std::unique_ptr`, `std::shared_ptr`, custom deleters | Guarantees resource release upon scope exit without manual cleanup calls. |
| **Compiler Attributes** | `[[nodiscard]]`, `const`, `explicit`, `noexcept` | Enforces compiler-level diagnostics against accidental copies, drops, or mutations. |
| **Zero-Cost Abstractions** | C++20 ranges (`\|`), `std::format`, concepts, `std::from_chars` | Expressive, declarative syntax that optimizes down to tight machine assembly. |

---

## Related Documentation

- [Project README](../README.md): Workspace overview, dependencies, and build instructions.
- [Curriculum Roadmap (LESSONS.md)](../LESSONS.md): Progressive, step-by-step learning syllabus guiding through each module.
