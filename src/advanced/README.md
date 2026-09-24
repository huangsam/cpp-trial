# Advanced Metaprogramming & Functional C++ (`src/advanced/`)

This directory covers advanced C++ features, including C++20 concepts and constraints, template metaprogramming, compile-time evaluation, variadic templates, fold expressions, CRTP, and functional idioms with lambdas.

## Files & Components

| File | Purpose | Key Features |
|---|---|---|
| [factorial.h](factorial.h) | Concepts & Compile-Time Checks | Function templates, C++20 `requires std::integral<T>`, `static_assert`, runtime bounds checks |
| [lambda.h](lambda.h) / [lambda.cpp](lambda.cpp) | Functional Programming & Lambdas | Closures, capture semantics, higher-order algorithms (`std::accumulate`), value wrappers |
| [template_meta.h](template_meta.h) / [template_meta.cpp](template_meta.cpp) | Template Metaprogramming | Custom type traits (`std::void_t`), `constexpr` computation, variadic templates, fold expressions, CRTP, tag dispatch |

---

## Realistic Engineering Goals: Compile-Time Computation & Zero-Cost Abstraction

Template metaprogramming is often perceived as "arcane syntax". In modern systems C++, however, metaprogramming is not about clever tricks—it is about **shifting performance costs from runtime to compilation time**:

| Runtime Technique (Other Languages) | Compile-Time C++ Equivalent | Production Benefit |
|---|---|---|
| Runtime reflection & type checking | Concepts (`requires std::integral<T>`) | Incompatible types are rejected at compile time with zero CPU cycles spent on runtime type inspection. |
| Interface dispatch via virtual tables (vtables) | CRTP (Curiously Recurring Template Pattern) | Inlines method calls directly without the pointer indirection or cache misses of dynamic vtable lookups. |
| Dynamic loops for static calculations | `constexpr` & template recursion | Computes constants, lookup tables, and formulas during compilation into raw binary data. |
| Variadic runtime packing / arrays | Variadic templates & fold expressions | Emits tight specialized machine instructions for any parameter pack without allocating temporary arrays. |

---

## Detailed Topic Guides

### 1. Concepts & Function Templates (`factorial.h`)

#### Constrained Templates (`requires std::integral<T>`)
C++20 concepts replace clumsy SFINAE syntax with readable compile-time constraints:

```cpp
namespace Full {
template <typename T>
  requires std::integral<T>
T factorial(T n) {
  static_assert(sizeof(T) <= sizeof(int64_t), "Type too large for factorial computation");
  if (n < 0) {
    throw std::invalid_argument(std::format("Factorial input must be non-negative, got: {}", n));
  }
  T result = 1;
  for (T i = 1; i <= n; ++i) result *= i;
  return result;
}
}
```

---

### 2. Lambda Expressions & Functional Programming (`lambda.h`)

#### Closures with Standard Algorithms
Lambdas encapsulate local computations without needing separate functor structs:

```cpp
int sum_of_squares(std::vector<int> numbers) {
  return std::accumulate(
      numbers.begin(), numbers.end(), 0,
      [](int acc, int x) { return acc + (x * x); });
}
```

---

### 3. Template Metaprogramming & Compile-Time Evaluation (`template_meta.h`)

#### Custom Type Traits with `std::void_t`
Detect whether a type provides specific member types or methods at compile time:

```cpp
template <typename T, typename = void>
struct IsContainer : std::false_type {};

template <typename T>
struct IsContainer<T, std::void_t<typename T::iterator, typename T::value_type>>
    : std::true_type {};

template <typename Container>
  requires IsContainer<Container>::value
void print_container_size(const Container& c) {
  std::cout << "Container size: " << c.size() << "\n";
}
```

#### Variadic Templates & Fold Expressions
Evaluate variable numbers of template parameters with compact C++17 fold expressions:

```cpp
// Fold expression summing arithmetic arguments
template <typename... Args>
  requires(std::is_arithmetic_v<Args> && ...)
constexpr auto sum_all(Args... args) {
  return (args + ...); // Expands to: arg1 + arg2 + ...
}

// Fold expression streaming arguments
template <typename... Args>
void print_all(Args... args) {
  (std::cout << ... << args) << "\n";
}
```

#### Compile-Time Recursion
Compute values purely during compilation using template specialization:

```cpp
template <int N>
struct Fibonacci {
  static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <> struct Fibonacci<0> { static constexpr int value = 0; };
template <> struct Fibonacci<1> { static constexpr int value = 1; };
```

#### Curiously Recurring Template Pattern (CRTP)
Static polymorphism without the runtime overhead or vtable lookups of virtual functions:

```cpp
template <typename Derived>
class Printable {
 public:
  void print() const {
    static_cast<const Derived*>(this)->do_print();
  }
};

class MyClass : public Printable<MyClass> {
 public:
  static void do_print() { std::cout << "Printing MyClass\n"; }
};
```

#### Tag Dispatch & `if constexpr`
Dispatch overloads cleanly without runtime branching costs:

```cpp
template <typename T>
void dispatch_process(T value) {
  if constexpr (std::is_integral_v<T>) {
    process_type(value, IntegralTag{});
  } else if constexpr (std::is_floating_point_v<T>) {
    process_type(value, FloatingTag{});
  } else {
    process_type(value, OtherTag{});
  }
}
```

---

## Key Learnings & Systems Insights

- **Zero-Cost Abstractions**: Metaprogramming shifts runtime overhead (type checks, branching, dispatch) entirely to compile time.
- **Concepts Provide Clear Compiler Errors**: Pre-C++20 templates yielded hundreds of lines of cryptic error cascades; `requires` clauses produce single-line diagnostic failures on constraint mismatches.
- **Backend Relevance**:
  - High-performance serialization/deserialization frameworks (e.g., Protobuf, FlatBuffers) use compile-time introspection to generate fast packing code.
  - Generic logging and metrics pipelines use variadic templates and fold expressions for formatting arbitrary arguments.

---

## Running Associated Tests

Unit tests for this module are located in `test/advanced/`:
- [test/advanced/factorial_test.cpp](../../test/advanced/factorial_test.cpp)
- [test/advanced/lambda_test.cpp](../../test/advanced/lambda_test.cpp)
- [test/advanced/template_meta_test.cpp](../../test/advanced/template_meta_test.cpp)

Run tests via CMake:
```shell
ctest --preset dev -R "FactorialTest|LambdaTest|TemplateMetaTest" --output-on-failure
```
