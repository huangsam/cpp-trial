#ifndef TEMPLATE_META_H
#define TEMPLATE_META_H

#include <iostream>
#include <type_traits>

// Template specialization and partial specialization
template <typename T>
struct IsPointer {
  static constexpr bool value = false;
};

template <typename T>
struct IsPointer<T*> {
  static constexpr bool value = true;
};

template <typename T>
struct IsPointer<const T*> {
  static constexpr bool value = true;
};

// Constraints with requires
template <typename T>
  requires std::integral<T>
void print_if_integral(T val) {
  std::cout << val << " is an integral type\n";
}

template <typename T>
  requires std::floating_point<T>
void print_if_floating(T val) {
  std::cout << val << " is a floating-point type\n";
}

// Type traits
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

// constexpr programming
constexpr int factorial(int n) { return (n <= 1) ? 1 : n * factorial(n - 1); }

template <int Base, int Exp>
struct Power {
  static constexpr int value = Base * Power<Base, Exp - 1>::value;
};

template <int Base>
struct Power<Base, 0> {
  static constexpr int value = 1;
};

// Variadic templates
template <typename... Args>
  requires(std::is_arithmetic_v<Args> && ...)
constexpr auto sum_all(Args... args) {
  return (args + ...);
}

template <typename... Args>
void print_all(Args... args) {
  (std::cout << ... << args) << "\n";
}

// Template recursion
template <int N>
struct Fibonacci {
  static constexpr int value =
      Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<0> {
  static constexpr int value = 0;
};

template <>
struct Fibonacci<1> {
  static constexpr int value = 1;
};

// CRTP
template <typename Derived>
class Printable {
 public:
  void print() const { static_cast<const Derived*>(this)->do_print(); }
};

class MyClass : public Printable<MyClass> {
 public:
  static void do_print() { std::cout << "Printing MyClass\n"; }
};

// Tag dispatch
struct IntegralTag {};
struct FloatingTag {};
struct OtherTag {};

template <typename T>
void process_type(T value, IntegralTag) {
  std::cout << value << " is processed as integral\n";
}

template <typename T>
void process_type(T value, FloatingTag) {
  std::cout << value << " is processed as floating-point\n";
}

template <typename T>
void process_type(T value, OtherTag) {
  std::cout << value << " is processed as other type\n";
}

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

// Demonstration function
void demonstrate_template_meta();

#endif  // TEMPLATE_META_H
