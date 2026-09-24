# Object-Oriented Programming (`src/oop/`)

This directory illustrates fundamental and modern object-oriented programming patterns in C++20, including class design, value encapsulation, custom type formatting, and dynamic polymorphism.

## Files & Components

| Component | Focus & Role |
|---|---|
| **[`person.h`](person.h)** · [`cpp`](person.cpp) | Encapsulation, strong parameter types, custom formatting, and range pipelines |
| **[`inheritance.h`](inheritance.h)** · [`cpp`](inheritance.cpp) | Abstract base classes, virtual destructors, and dynamic runtime dispatch |

---

## Mindset Shift: Why `Person` Is Structured This Way

If you come from Python, Java, or TypeScript, the implementation in [person.h](person.h) might initially feel like "over-engineering" for a simple entity class. Here is the realistic engineering rationale behind this structure:

| Naive / Introductory OOP | Production Modern C++ ([person.h](person.h)) | Engineering Rationale |
|---|---|---|
| `Person(string name, int age, double salary)` | `Person(string name, Age age, Salary salary)` | **Prevents Primitive Obsession**: In a naive constructor, accidentally calling `Person("Alice", 75000, 30)` compiles silently. Strong wrapper types catch parameter transposition at compile time and guarantee validation on instantiation. |
| Public fields (`p.salary = -100`) | Private fields + `[[nodiscard]]` getters | **Guaranteed Invariants**: An object cannot be mutated into an invalid state after construction. |
| Custom `.toString()` returning `std::string` | `std::formatter<Person>` specialization | **Zero Heap Allocations**: Custom `.toString()` methods allocate a new heap string on every invocation. `std::formatter` streams formatted characters directly into output buffers without allocations. |
| Imperative `for` loop with intermediate arrays | C++20 Range Pipeline (`std::views::filter`) | **Zero Temporary Allocations & Laziness**: Declarative stream processing without allocating temporary vectors for intermediate results. |

---

## Detailed Topic Guides

### 1. Person & Value Encapsulation (`person.h`)

#### Strong Types and Domain Validation
Instead of passing raw `int` or `double` values into constructors, strong types ensure that invalid states cannot be constructed:

```cpp
struct Age {
  static constexpr int MIN_AGE = 1;
  explicit Age(const int age) : value(age) {
    if (value < MIN_AGE) {
      throw std::invalid_argument(
          std::format("Age must be at least {}, got: {}", MIN_AGE, age));
    }
  }
  int value;
};
```

#### Custom Type Formatting (`std::formatter`)
Provides idiomatic string formatting via `std::format` without having to define custom `.to_string()` methods:

```cpp
template <>
struct std::formatter<Person> : std::formatter<std::string> {
  static auto format(const Person& person, std::format_context& ctx) {
    return std::format_to(
        ctx.out(), "{} is {} years old with ${:.2f} as a salary",
        person.get_name(), person.get_age(), person.get_salary());
  }
};
```

#### Modern C++20 Range Pipelines
In [person.cpp](person.cpp), `calculate_average_eligible_salary_ranges` processes collections using composable, lazy-evaluated range views:

```cpp
auto eligible_salaries_view =
    people |
    std::views::filter([age_threshold, min_salary](const Person& person) {
      return person.get_age() >= age_threshold &&
             person.get_salary() > min_salary;
    }) |
    std::views::transform([](const Person& person) {
      return person.get_salary();
    });

const double total = std::accumulate(eligible_salaries_view.begin(), eligible_salaries_view.end(), 0.0);
const int64_t count = std::ranges::distance(eligible_salaries_view);
```

---

### 2. Inheritance & Runtime Polymorphism (`inheritance.h`)

#### Abstract Base Classes & Virtual Destructors
Polymorphic base classes require a virtual destructor (`virtual ~Animal() = default;`) so that deleting a derived object through a base pointer invokes the correct destructor sequence:

```cpp
class Animal {
 public:
  explicit Animal(std::string name) : name_(std::move(name)) {}
  virtual ~Animal() = default;  // Crucial for safe polymorphic deletion
  
  Animal(const Animal&) = delete;
  Animal& operator=(const Animal&) = delete;
  Animal(Animal&&) = default;
  Animal& operator=(Animal&&) = default;

  [[nodiscard]] virtual std::string speak() const = 0; // Pure virtual
  [[nodiscard]] std::string get_name() const { return name_; }

 private:
  std::string name_;
};
```

#### Derived Class Overrides
Derived classes use the `override` specifier to catch signature mismatches at compile time:

```cpp
class Dog : public Animal {
 public:
  explicit Dog(std::string name) : Animal(std::move(name)) {}
  [[nodiscard]] std::string speak() const override { return "Woof!"; }
};
```

#### Dynamic Polymorphic Dispatch
Passing by const reference (`const Animal&`) avoids object slicing while dynamically invoking the overridden `speak()` method at runtime:

```cpp
std::string make_animal_speak(const Animal& animal) {
  return animal.get_name() + " says: " + animal.speak();
}
```

---

## Key Learnings & Systems Insights

- **Prevent Object Slicing**: Always accept polymorphic types by reference (`const Base&`) or pointer/smart pointer (`std::unique_ptr<Base>`), never by value.
- **Rule of Zero/Five with Inheritance**: If a base class declares a virtual destructor, explicitly define or delete copy and move operations to prevent unintentional copying of polymorphic hierarchies.
- **Backend Relevance**:
  - Domain models (users, accounts, permissions) benefit from validated wrapper types to guarantee invariants.
  - Polymorphic interfaces decouple business services from pluggable handlers (e.g., protocol decoders, storage engines).

---

## Running Associated Tests

Unit tests for this module are located in `test/oop/`:
- [test/oop/person_test.cpp](../../test/oop/person_test.cpp)
- [test/oop/inheritance_test.cpp](../../test/oop/inheritance_test.cpp)

Run tests via CMake:
```shell
ctest --preset dev -R "PersonTest|PersonAnalyzerTest|InheritanceTest" --output-on-failure
```
