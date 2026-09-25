---
name: cpp-trial-agents
description: Workspace guidance for C++ learning project covering modern C++, CMake, GoogleTest
---

# C++ Trial Agents

## Verification Commands

Run these preset commands to verify changes across development, analysis, and sanitizers:

```shell
# Fast build & unit test suite (standard verification)
cmake --preset dev && cmake --build --preset dev && ctest --test-dir build --output-on-failure

# Auto-format all source and header files
cmake --build build --target format

# Static analysis with Clang-Tidy (warnings treated as errors)
cmake --preset tidy && cmake --build --preset tidy

# Memory leak & undefined behavior detection (ASan + UBSan)
cmake --preset asan && cmake --build --preset asan && ctest --test-dir build --output-on-failure

# Data race detection (ThreadSanitizer)
cmake --preset tsan && cmake --build --preset tsan && ctest --test-dir build --output-on-failure
```

## Conditional Instructions

IF user wants to add a new C++ topic or learning module, THEN:
- Create implementation files (.cpp/.h pair) in the appropriate domain folder within `src/`
- Add corresponding unit tests in the matching domain folder within the `test/` directory
- Update `CMakeLists.txt` in both the `src/` and `test/` roots to include new files using relative paths
- Follow existing naming conventions in those folders for consistency
- Mark all single-argument constructors and converting member templates as `explicit`

IF user wants to add or update performance benchmarks, THEN:
- Add benchmark files (`_bench.cpp`) to the `bench/` directory
- Update `bench/CMakeLists.txt` to include the new benchmark using `add_trial_benchmark`
- Use the standard Google Benchmark library for implementation

IF user encounters memory management or RAII issues, THEN:
- Check for proper resource acquisition and release patterns
- Run AddressSanitizer (`cmake --preset asan`) for memory leak and UB detection
- Ensure smart pointers are used appropriately (`unique_ptr`, `shared_ptr`, `weak_ptr`)

IF user asks about concurrency or threading problems, THEN:
- Check for race conditions and proper synchronization
- Run ThreadSanitizer (`cmake --preset tsan`) to detect runtime data races
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
