# C++ Learning Notes

This document tracks the key C++ concepts and learnings from each module in the `src/` directory. Each module demonstrates specific language features, best practices, and backend-relevant skills.

Please refer to README.md for project setup, build instructions, and testing procedures.

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
