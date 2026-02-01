# C++ Learning Notes

This document tracks the key C++ concepts and learnings from each module in the `src/` directory. Each module demonstrates specific language features, best practices, and backend-relevant skills.

Please refer to README.md for project setup, build instructions, and testing procedures.

## Table of Contents

1. [person](#person) - Class design and encapsulation
2. [date](#date) - Operator overloading and RAII
3. [factorial](#factorial) - Function templates and generic programming
4. [lambda](#lambda) - Lambda expressions and functional programming
5. [stl_deep_dive](#stl_deep_dive) - STL containers and algorithms
6. [enums_unions](#enums_unions) - Enums, unions, and type safety
7. [namespaces](#namespaces) - Code organization and modularization
8. [inheritance](#inheritance) - Inheritance and polymorphism
9. [file_io](#file_io) - File input/output operations
10. [thread_simple](#thread_simple) - Basic threading concepts
11. [safe_counter](#safe_counter) - Thread safety and synchronization
12. [async_simple](#async_simple) - Asynchronous programming
13. [Overall Project Learnings](#overall-project-learnings)

## person

**Key Concepts:**
- Class design with multiple constructors
- Access specifiers and encapsulation
- Method chaining and fluent interfaces
- Data validation in setters

**Learnings:**
- Designing classes with proper abstraction
- Implementing getter/setter patterns
- Using `const` member functions
- Object initialization patterns

**Backend Relevance:**
- Data models for user entities
- Business object design

## date

**Key Concepts:**
- Class design and encapsulation
- Operator overloading (comparison operators)
- RAII (Resource Acquisition Is Initialization)
- Custom types and value semantics

**Learnings:**
- Implementing comparison operators for custom classes
- Using `const` correctness in member functions
- Basic date arithmetic and validation
- Object-oriented design principles

**Backend Relevance:**
- Custom data types for business logic
- Date handling in APIs and data processing

## factorial

**Key Concepts:**
- Function templates and generic programming
- Exception handling with custom exceptions
- Input validation and error propagation
- Template specialization

**Learnings:**
- Writing generic functions that work with different types
- Throwing and catching exceptions appropriately
- Using `static_assert` for compile-time checks
- Mathematical computations with overflow considerations

**Backend Relevance:**
- Generic utility functions for data processing
- Error handling in computational services

## lambda

**Key Concepts:**
- Lambda expressions and closures
- Higher-order functions
- Algorithm library usage (`std::transform`, `std::accumulate`)
- Functional programming in C++

**Learnings:**
- Capturing variables in lambdas (by value, reference, or move)
- Using lambdas with standard algorithms
- Functional composition and data transformation
- Performance implications of lambda captures

**Backend Relevance:**
- Data processing pipelines
- Callback mechanisms in event-driven systems

## stl_deep_dive

**Key Concepts:**
- STL containers (vector, map, set, unordered_map)
- STL algorithms (sort, find, transform, accumulate, copy_if)
- Iterator usage and range-based loops
- Lambda expressions with algorithms
- Container operations and performance considerations

**Learnings:**
- Using vector for dynamic arrays with push_back, size, and indexing
- Map for key-value pairs with operator[] and find
- Set for unique elements with insert and count
- Unordered_map for fast lookups
- Algorithms like sort, find_if, transform, accumulate
- Lambda captures and usage in algorithms
- Iterator-based operations

**Backend Relevance:**
- Data structures for caching and configuration
- Algorithm implementations for data processing
- Efficient container usage in high-performance applications
- Functional programming patterns in C++

## enums_unions

**Key Concepts:**
- Enums (scoped vs. unscoped) and their usage
- Unions for memory-efficient storage
- Tagged unions and modern alternatives like `std::variant`
- Type safety and memory management

**Learnings:**
- Scoped enums (`enum class`) prevent implicit conversions
- Unions share memory between different types
- Using tags with unions to avoid unsafe access
- `std::variant` as a type-safe alternative to unions

**Backend Relevance:**
- Efficient data structures for configuration or protocol parsing
- Type-safe handling of multiple data types in APIs

## namespaces

**Key Concepts:**
- Organizing code with namespaces
- Nested namespaces and namespace aliases
- Using declarations and directives
- Avoiding name conflicts in large codebases

**Learnings:**
- Defining and using namespaces for code organization
- Namespace aliases for shorter names
- Using declarations to bring specific names into scope
- Best practices for namespace usage in C++

**Backend Relevance:**
- Modular code organization in large applications
- Preventing naming collisions in libraries and APIs
- Clean interfaces for backend services

## inheritance

**Key Concepts:**
- Inheritance with base and derived classes
- Polymorphism using virtual functions and pure virtual destructors
- Runtime polymorphism via base class references

**Learnings:**
- Defining base classes with virtual methods
- Overriding virtual functions in derived classes
- Using `override` keyword for safety
- Demonstrating polymorphism with base references

**Backend Relevance:**
- Object hierarchies in data models
- Extensible interfaces for plugins or handlers

## file_io

**Key Concepts:**
- File input/output with `std::fstream`
- Exception handling for file operations
- Using `std::filesystem` for paths
- Reading/writing text files

**Learnings:**
- Opening files with different modes (`std::ios::in`, `std::ios::out`)
- Reading entire files vs. line-by-line
- Error handling with `std::runtime_error`
- Using `std::filesystem::path` for cross-platform paths

**Backend Relevance:**
- Configuration file reading/writing
- Logging to files
- Data persistence in applications

## thread_simple

**Key Concepts:**
- Basic thread creation with `std::thread`
- Thread synchronization with `std::mutex` and `std::unique_lock`
- Condition variables for thread communication
- Thread lifecycle management

**Learnings:**
- Creating and joining threads
- Avoiding data races with proper synchronization
- Using condition variables for producer-consumer patterns
- Thread safety best practices

**Backend Relevance:**
- Handling concurrent requests in server applications
- Background task processing

## safe_counter

**Key Concepts:**
- Thread safety with mutexes
- RAII for resource management (`std::lock_guard`)
- Atomic operations and memory barriers
- Race condition prevention

**Learnings:**
- Protecting shared data in multi-threaded environments
- Using RAII for automatic lock management
- Understanding thread synchronization primitives
- Performance trade-offs of synchronization

**Backend Relevance:**
- Thread-safe data structures for concurrent access
- Critical for multi-user server applications

## async_simple

**Key Concepts:**
- Asynchronous programming with `std::async` and `std::future`
- Non-blocking execution for concurrent tasks
- Error handling in async contexts
- C++11/14 concurrency features

**Learnings:**
- How to launch tasks asynchronously without blocking the main thread
- Using `std::future::get()` to retrieve results
- Basic thread pool concepts (though not implemented here)
- Importance of async for backend services handling multiple requests

**Backend Relevance:**
- Simulates handling concurrent user requests in a web server
- Foundation for building scalable, non-blocking services

## Overall Project Learnings

**Build System:**
- CMake configuration and presets
- Cross-platform compilation
- Testing integration with Google Test
- CI/CD with GitHub Actions

**Code Quality Tools:**
- Clang-Format: Configured for Google style to ensure consistent code formatting across the project
- Clang-Tidy: Static analysis checks for bug detection, performance, readability, and modern C++ best practices (currently disabled in build but available for manual use or IDE integration)

**C++ Standards:**
- C++20 features and modern idioms
- Smart pointers and RAII
- Exception safety
- Template metaprogramming basics

**Backend Development Insights:**
- Performance considerations
- Concurrency patterns
- Error handling strategies
- Code organization for maintainability

**Future Extensions:**
- Networking (HTTP servers)
- Database integration
- Serialization (JSON)
- Configuration management
