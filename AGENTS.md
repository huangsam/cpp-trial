---
name: cpp-trial-agents
description: Workspace instructions for C++ learning project covering modern C++ features, CMake build system, and GoogleTest framework
---

# C++ Trial Project Agents

## Project Architecture

This workspace contains a C++ learning project demonstrating modern C++ concepts:

- **Build System**: CMake with Ninja generator, configured via `CMakePresets.json`
- **Testing Framework**: GoogleTest (gtest) for unit testing
- **Source Structure**:
  - `src/`: Implementation files (.cpp/.h) organized into domain modules (`concurrency`, `memory`, etc.)
  - `test/`: Corresponding unit tests mirroring the `src/` module structure
  - `bench/`: Performance benchmarks using Google Benchmark
  - `build/`: Generated build artifacts and dependencies

## Conditional Instructions

IF user wants to add a new C++ topic or learning module, THEN:
- Create implementation files (.cpp/.h pair) in the appropriate domain folder within `src/`
- Add corresponding unit tests in the matching domain folder within the `test/` directory
- Update `CMakeLists.txt` in both the `src/` and `test/` roots to include new files using relative paths
- Follow existing naming conventions in those folders for consistency

IF user wants to add or update performance benchmarks, THEN:
- Add benchmark files (`_bench.cpp`) to the `bench/` directory
- Update `bench/CMakeLists.txt` to include the new benchmark using `add_trial_benchmark`
- Use the standard Google Benchmark library for implementation

IF user encounters memory management or RAII issues, THEN:
- Check for proper resource acquisition and release patterns
- Use valgrind or similar tools for memory leak detection
- Ensure smart pointers are used appropriately (`unique_ptr`, `shared_ptr`, `weak_ptr`)

IF user asks about concurrency or threading problems, THEN:
- Check for race conditions and proper synchronization
- Use thread-safe patterns and avoid global state
- Consider using C++ standard library concurrency features

IF user needs to update documentation or lessons, THEN:
- Update `LESSONS.md` for learning content
- Update `README.md` for project overview
- Ensure code examples match documented concepts
- Test any code snippets in documentation

IF user wants to check code style or run static analysis, THEN:
- Use `clang-format` to automatically format code according to project style guidelines
- Run `clang-tidy` to catch common issues and enforce best practices
- Configuration files `.clang-format` and `.clang-tidy` define project-specific rules
- Consider running these tools before committing changes to maintain code quality
