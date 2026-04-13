# C++ Trial

[![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/huangsam/cpp-trial/ci.yml)](https://github.com/huangsam/cpp-trial/actions)

Exploring modern C++ concepts (C++11 to C++20) with [CMake](https://cmake.org/) and [GoogleTest](https://google.github.io/googletest/) as development tools.

<img src="images/cplusplus.webp" alt="C++" width="250px">

## Project goals

This repository serves as a comprehensive learning resource for modern C++ development, focusing on language mastery through C++11 to C++20 features, tool proficiency with CMake and GoogleTest, backend development patterns for systems programming, code quality with clean and testable C++ code, and progressive learning from basic concepts to advanced template metaprogramming.

## Project structure

The codebase is organized into domain-specific modules:
- `advanced/`: Metaprogramming, lambdas, and factorial templates.
- `concurrency/`: Threading, async programming, and synchronization structures.
- `memory/`: Smart pointers, move semantics, and custom memory management.
- `oop/`: Inheritance, polymorphism, and core class design.
- `stl/`: Standard Template Library containers, algorithms, and file I/O.
- `types/`: Primitive type safety, namespaces, and enums/unions.

For a guided learning path of C++ concepts in this project, refer to [LESSONS.md](LESSONS.md).

## Getting started

For everyone:

```shell
# Build with development mode
cmake --preset dev
cmake --build --preset dev

# Run application and tests
./build/bin/main.out
./build/bin/test.out
```

For performance engineers:

```shell
# Build with release mode
cmake --preset release
cmake --build --preset release

# Run benchmarks
./build/bin/bench/memory_bench.out
./build/bin/bench/concurrency_bench.out
./build/bin/bench/move_bench.out
```

For contributors:

```shell
# Ensure all files are formatted before PR
cmake --build build --target format
```

## Useful resources

- <https://cplusplus.com/>
- <https://en.cppreference.com/w/>
- <https://google.github.io/styleguide/cppguide.html>
- <https://google.github.io/googletest/reference/assertions.html>
- <https://cmake.org/cmake/help/git-master/manual/cmake-commands.7.html>
- <https://clang.llvm.org/docs/ClangFormatStyleOptions.html>
- <https://clang.llvm.org/extra/clang-tidy/checks/list.html>
- <https://github.com/fffaraz/awesome-cpp>
