#include <format>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "advanced/factorial.h"
#include "advanced/lambda.h"
#include "advanced/template_meta.h"
#include "concurrency/async_simple.h"
#include "concurrency/safe_counter.h"
#include "concurrency/thread_simple.h"
#include "memory/memory_management.h"
#include "memory/move_semantics.h"
#include "memory/smart_pointers.h"
#include "oop/inheritance.h"
#include "oop/person.h"
#include "stl/date.h"
#include "stl/file_io.h"
#include "stl/stl_deep_dive.h"
#include "types/enums_unions.h"
#include "types/namespaces.h"
#include "types/type_safety.h"

void demo_oop() {
  std::cout << "## [oop] Object-Oriented Programming\n\n";

  std::cout << "### person.h\n";
  const auto person = Person("David", Age(21), Salary(65000.00));
  std::cout << std::format("{}\n", person);

  std::cout << "\n### inheritance.h\n";
  Dog dog("Buddy");
  Cat cat("Whiskers");
  std::cout << make_animal_speak(dog) << "\n";
  std::cout << make_animal_speak(cat) << "\n";
}

void demo_types() {
  std::cout << "## [types] Types & Type Safety\n\n";

  std::cout << "### type_safety.h\n";
  std::map<std::string, int> data = {{"key1", 42}, {"key2", 100}};
  if (auto result = find_value(data, "key1")) {
    std::cout << "Found value: " << *result << "\n";
  }
  ConfigValue config = 42;  // Can hold int, string, or bool
  std::cout << "Config: " << config_to_string(config) << "\n";
  TypeSafeContainer container;
  container.add(42);
  container.add(std::string("hello"));
  container.add(true);
  auto int_val = container.get_as<int>(0);
  auto str_val = container.get_as<std::string>(1);
  auto bool_val = container.get_as<bool>(2);
  if (int_val && str_val && bool_val) {
    std::cout << "Retrieved: int=" << *int_val << ", string=" << *str_val
              << ", bool=" << *bool_val << "\n";
  }
  std::string original = "Hello World";
  process_string(original);

  std::cout << "\n### enums_unions.h\n";
  Color color = Red;
  auto status = Status::Running;
  std::cout << "Color: " << color << ", Status: " << static_cast<int>(status)
            << "\n";
  TaggedData tagged(42.5);
  std::cout << "Tagged data: " << tagged.to_string() << "\n";
  VariantData variant = 'h';
  std::cout << "Variant data: " << variant_to_string(variant) << "\n";

  std::cout << "\n### namespaces.h\n";
  std::cout << "Math result: " << utils::math::add(5, 3) << "\n";
  std::cout << "Calculator multiply: "
            << utils::math::Calculator::multiply(4, 7) << "\n";
  std::cout << "Upper case: " << utils::to_upper("hello world") << "\n";
  std::cout << "Processed: " << data::Processor::process("input data") << "\n";
}

void demo_stl() {
  std::cout << "## [stl] Standard Template Library\n\n";

  std::cout << "### date.h\n";
  const auto date1 = Date(Year(2024), Month(1), Day(1));
  std::cout << std::format("{}\n", date1);
  const auto date2 = Date(Year(2024), Month(2), Day(2));
  std::cout << std::format("{}\n", date2);
  if (date1 < date2) {
    std::cout << std::format("First date is older than second date\n");
  }

  std::cout << "\n### stl_deep_dive.h\n";
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto evens = STLDeepDive::filter_even(numbers);
  std::cout << "Even numbers: ";
  for (int num : evens) std::cout << num << " ";
  std::cout << "\n";
  std::vector<std::string> words = {"hello", "world", "cpp", "programming",
                                    "cpp"};
  auto word_count = STLDeepDive::count_words(words);
  std::cout << "Most frequent word: "
            << STLDeepDive::most_frequent_word(word_count) << "\n";
  std::set<int> set1 = {1, 2, 3, 4, 5};
  std::set<int> set2 = {3, 4, 5, 6, 7};
  auto intersection_result = STLDeepDive::intersection(set1, set2);
  std::cout << "Set intersection: ";
  for (int num : intersection_result) std::cout << num << " ";
  std::cout << "\n";

  std::cout << "\n### file_io.h\n";
  try {
    const auto output_path = FileIO::get_test_data_path("demo_output.txt");
    FileIO::write_string_to_file(output_path,
                                 "Hello from FileIO!\nThis is a test file.");
    auto content = FileIO::read_file_to_string(output_path);
    std::cout << "File content: " << content << "\n";

    const auto lines_path = FileIO::get_test_data_path("demo_lines.txt");
    std::vector<std::string> lines = {"Line 1", "Line 2", "Line 3"};
    FileIO::write_lines_to_file(lines_path, lines);
    auto read_lines = FileIO::read_file_lines(lines_path);
    std::cout << "Read " << read_lines.size() << " lines from file\n";
  } catch (const std::exception& e) {
    std::cout << "File I/O error: " << e.what() << "\n";
  }
}

void demo_memory() {
  std::cout << "## [memory] Memory Management & RAII\n\n";

  std::cout << "### smart_pointers.h\n";
  try {
    auto file_handler =
        createFileHandler(FileIO::get_test_data_path("demo.txt"));
    file_handler->writeData("Hello from unique_ptr!");
    std::cout << "File written successfully\n";
  } catch (const std::exception& e) {
    std::cout << "File operation failed: " << e.what() << "\n";
  }
  {
    auto resource1 = createSharedResource("Resource A");
    {
      std::cout << "Shared resource use count: " << resource1.use_count()
                << "\n";
    }
    std::cout << "After inner scope, use count: " << resource1.use_count()
              << "\n";
  }
  {
    auto parent = createParent("John");
    auto child = createChild("Jane");
    createFamily(parent, child);
    parent->showFamily();
  }

  std::cout << "\n### memory_management.h\n";
  {
    ArenaAllocator arena(1024);
    std::cout << "Custom allocator created with 1024 bytes\n";
    std::cout << "Remaining space: " << arena.remaining_space() << " bytes\n";
  }
  std::cout << "RAII: File and timer automatically cleaned up\n";

  std::cout << "\n### move_semantics.h\n";
  {
    ResourceManager rm;
    std::vector<int> data = {1, 2, 3, 4, 5};
    rm.consume_rvalue(std::move(data));
    std::cout << "Move semantics: consumed " << rm.size() << " elements\n";
  }
}

void demo_advanced() {
  std::cout << "## [advanced] Advanced C++ & Metaprogramming\n\n";

  std::cout << "### factorial.h\n";
  std::cout << std::format("Full::factorial(5): {}\n", Full::factorial(5));
  std::cout << std::format("Full::factorial(10): {}\n", Full::factorial(10));

  std::cout << "\n### lambda.h\n";
  std::cout << std::format("less_than(3,4): {}\n",
                           less_than(ValueOne(3), ValueTwo(4)));
  std::cout << std::format("sum_of_squares(vector{{1,2,3}}): {}\n",
                           sum_of_squares(std::vector{1, 2, 3}));

  std::cout << "\n### template_meta.h\n";
  std::cout << std::format("Minimal::factorial(7): {}\n",
                           Minimal::factorial(7));
  std::cout << "Template metaprogramming: Fibonacci<10> = "
            << Fibonacci<10>::value << "\n";
}

void demo_concurrency() {
  std::cout << "## [concurrency] Concurrency & Multithreading\n\n";

  std::cout << "### thread_simple.h\n";
  {
    ThreadSimpleClass thread_demo;
    thread_demo.start_worker_thread();
    thread_demo.join_worker_thread();
    std::cout << "Worker message: " << thread_demo.get_worker_message() << "\n";
  }

  std::cout << "\n### safe_counter.h\n";
  {
    SafeCounter counter;
    counter.start_worker_threads(4, 100);
    counter.join_worker_threads();
    std::cout << "Safe counter final value: " << counter.get_count() << "\n";
  }

  std::cout << "\n### async_simple.h\n";
  std::cout << greet() << "\n";
}

int main() {
  auto print_divider = [] { std::cout << "\n---\n\n"; };

  demo_oop();
  print_divider();
  demo_types();
  print_divider();
  demo_stl();
  print_divider();
  demo_memory();
  print_divider();
  demo_advanced();
  print_divider();
  demo_concurrency();

  return 0;
}
