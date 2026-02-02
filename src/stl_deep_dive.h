#ifndef STL_DEEP_DIVE_H
#define STL_DEEP_DIVE_H

#include <map>
#include <set>
#include <string>
#include <vector>

// STLDeepDive demonstrates STL containers and algorithms.
// Includes examples with vectors, maps, sets, and functional programming.
class STLDeepDive {
 public:
  // Vector operations
  static std::vector<int> filter_even(const std::vector<int>& numbers);
  static int sum_vector(const std::vector<int>& numbers);

  // Map operations
  static std::map<std::string, int> count_words(
      const std::vector<std::string>& words);
  static std::string most_frequent_word(
      const std::map<std::string, int>& word_count);

  // Set operations
  static std::set<int> unique_elements(const std::vector<int>& numbers);
  static std::set<int> intersection(const std::set<int>& set1,
                                    const std::set<int>& set2);

  // Algorithm demonstrations
  static void sort_vector(std::vector<int>& numbers);
  static bool contains_element(const std::vector<int>& numbers, int target);
  static std::vector<int> transform_multiply(const std::vector<int>& numbers,
                                             int factor);

  // Advanced: using algorithms with lambdas
  static std::vector<std::string> filter_long_words(
      const std::vector<std::string>& words, size_t min_length);
};

#endif  // STL_DEEP_DIVE_H
