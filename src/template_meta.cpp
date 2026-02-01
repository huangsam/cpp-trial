#include "template_meta.h"

#include <vector>

void demo_specialization() {
  std::cout << "=== Template Specialization ===\n";
  std::cout << "int is pointer: " << IsPointer<int>::value << "\n";
  std::cout << "int* is pointer: " << IsPointer<int*>::value << "\n";
  std::cout << "const int* is pointer: " << IsPointer<const int*>::value
            << "\n";
}

void demo_sfinae() {
  std::cout << "=== SFINAE ===\n";
  print_if_integral(42);
  print_if_floating(3.14);
}

void demo_type_traits() {
  std::cout << "=== Type Traits ===\n";
  const std::vector vec = {1, 2, 3};
  print_container_size(vec);
}

void demo_constexpr() {
  std::cout << "=== constexpr Programming ===\n";
  constexpr int fact5 = factorial(5);
  std::cout << "5! = " << fact5 << "\n";

  constexpr int pow2_3 = Power<2, 3>::value;
  std::cout << "2^3 = " << pow2_3 << "\n";
}

void demo_variadic() {
  std::cout << "=== Variadic Templates ===\n";
  std::cout << "Sum of 1, 2, 3, 4: " << sum_all(1, 2, 3, 4) << "\n";
  print_all("Hello", ", ", "world", "!", 42);
}

void demo_recursion() {
  std::cout << "=== Template Recursion ===\n";
  std::cout << "Fibonacci(10) = " << Fibonacci<10>::value << "\n";
}

void demo_crtp() {
  std::cout << "=== CRTP ===\n";
  constexpr MyClass obj;
  obj.print();
}

void demo_tag_dispatch() {
  std::cout << "=== Tag Dispatch ===\n";
  dispatch_process(42);
  dispatch_process(3.14);
  dispatch_process("hello");
}

void demonstrate_template_meta() {
  demo_specialization();
  demo_sfinae();
  demo_type_traits();
  demo_constexpr();
  demo_variadic();
  demo_recursion();
  demo_crtp();
  demo_tag_dispatch();
}
