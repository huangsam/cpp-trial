#include <format>
#include <iostream>
#include <vector>

#include "async_simple.h"
#include "date.h"
#include "enums_unions.h"
#include "file_io.h"
#include "inheritance.h"
#include "lambda.h"
#include "memory_management.h"
#include "move_semantics.h"
#include "namespaces.h"
#include "person.h"
#include "smart_pointers.h"
#include "stl_deep_dive.h"
#include "template_meta.h"
#include "thread_simple.h"
#include "type_safety.h"

int main() {
  // date.h demo
  const auto date1 = Date(Year(2024), Month(1), Day(1));
  std::cout << std::format("{}\n", date1);
  const auto date2 = Date(Year(2024), Month(2), Day(2));
  std::cout << std::format("{}\n", date2);
  if (date1 < date2) {
    std::cout << std::format("First date is older than second date\n");
  }

  // factorial.h demo
  std::cout << std::format("factorial(4): {}\n", factorial(4));

  // lambda.h demo
  std::cout << std::format("less_than(3,4): {}\n",
                           less_than(ValueOne(3), ValueTwo(4)));
  std::cout << std::format("sum_of_squares(vector{{1,2,3}}): {}\n",
                           sum_of_squares(std::vector{1, 2, 3}));

  // person.h demo
  const auto person = Person("David", Age(21), Salary(65000.00));
  std::cout << std::format("{}\n", person);

  // smart_pointers.h demo
  try {
    auto file_handler = createFileHandler("demo.txt");
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

  // memory_management.h demo
  {
    ArenaAllocator arena(1024);
    std::cout << "Custom allocator created with 1024 bytes\n";
    std::cout << "Remaining space: " << arena.remaining_space() << " bytes\n";
  }
  std::cout << "RAII: File and timer automatically cleaned up\n";

  // move_semantics.h demo
  {
    ResourceManager rm;
    std::vector<int> data = {1, 2, 3, 4, 5};
    rm.consume_rvalue(std::move(data));
    std::cout << "Move semantics: consumed " << rm.size() << " elements\n";
  }

  // stl_deep_dive.h demo
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

  // type_safety.h demo
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

  // enums_unions.h demo
  Color color = Red;
  auto status = Status::Running;
  std::cout << "Color: " << color << ", Status: " << static_cast<int>(status)
            << "\n";
  TaggedData tagged(42.5);
  std::cout << "Tagged data: " << tagged.to_string() << "\n";
  VariantData variant = 'h';
  std::cout << "Variant data: " << variant_to_string(variant) << "\n";

  // inheritance.h demo
  Dog dog("Buddy");
  Cat cat("Whiskers");
  std::cout << make_animal_speak(dog) << "\n";
  std::cout << make_animal_speak(cat) << "\n";

  // namespaces.h demo
  std::cout << "Math result: " << utils::math::add(5, 3) << "\n";
  std::cout << "Calculator multiply: "
            << utils::math::Calculator::multiply(4, 7) << "\n";
  std::cout << "Upper case: " << to_upper("hello world") << "\n";
  std::cout << "Processed: " << data::Processor::process("input data") << "\n";

  // file_io.h demo
  try {
    FileIO::write_string_to_file("demo_output.txt",
                                 "Hello from FileIO!\nThis is a test file.");
    auto content = FileIO::read_file_to_string("demo_output.txt");
    std::cout << "File content: " << content << "\n";

    std::vector<std::string> lines = {"Line 1", "Line 2", "Line 3"};
    FileIO::write_lines_to_file("demo_lines.txt", lines);
    auto read_lines = FileIO::read_file_lines("demo_lines.txt");
    std::cout << "Read " << read_lines.size() << " lines from file\n";
  } catch (const std::exception& e) {
    std::cout << "File I/O error: " << e.what() << "\n";
  }

  // template_meta.h demo
  std::cout << "Template metaprogramming: Fibonacci<10> = " << Fibonacci<10>::value << "\n";

  // thread_simple.h demo
  {
    ThreadSimpleClass thread_demo;
    thread_demo.start_worker_thread();
    thread_demo.join_worker_thread();
    std::cout << "Worker message: " << thread_demo.get_worker_message() << "\n";
  }

  // async_simple.h demo
  std::cout << greet() << "\n";

  return 0;
}
