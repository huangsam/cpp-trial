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
  - `build/`: Generated build artifacts and dependencies
- **Topics Covered**: RAII, smart pointers, templates, inheritance, concurrency, STL, file I/O, type safety

## Conditional Instructions

IF user wants to add a new C++ topic or learning module, THEN:
- Create implementation files (.cpp/.h pair) in the appropriate domain folder within `src/`
- Add corresponding unit tests in the matching domain folder within the `test/` directory
- Update `CMakeLists.txt` in both the `src/` and `test/` roots to include new files using relative paths
- Follow existing naming conventions in those folders for consistency

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
