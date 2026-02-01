#include "stl_deep_dive.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

std::vector<int> STLDeepDive::filter_even(const std::vector<int>& numbers) {
  auto even_view =
      numbers | std::views::filter([](int n) { return n % 2 == 0; });
  return {even_view.begin(), even_view.end()};
}

int STLDeepDive::sum_vector(const std::vector<int>& numbers) {
  return std::accumulate(numbers.begin(), numbers.end(), 0);
}

std::map<std::string, int> STLDeepDive::count_words(
    const std::vector<std::string>& words) {
  std::map<std::string, int> word_count;
  for (const auto& word : words) {
    ++word_count[word];
  }
  return word_count;
}

std::string STLDeepDive::most_frequent_word(
    const std::map<std::string, int>& word_count) {
  if (word_count.empty()) return "";
  auto max_it = std::ranges::max_element(
      word_count,
      [](const auto& a, const auto& b) { return a.second < b.second; });
  return max_it->first;
}

std::set<int> STLDeepDive::unique_elements(const std::vector<int>& numbers) {
  return std::set<int>(numbers.begin(), numbers.end());
}

std::set<int> STLDeepDive::intersection(const std::set<int>& set1,
                                        const std::set<int>& set2) {
  std::set<int> result;
  std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                        std::inserter(result, result.begin()));
  return result;
}

void STLDeepDive::sort_vector(std::vector<int>& numbers) {
  std::sort(numbers.begin(), numbers.end());
}

bool STLDeepDive::contains_element(const std::vector<int>& numbers,
                                   int target) {
  return std::find(numbers.begin(), numbers.end(), target) != numbers.end();
}

std::vector<int> STLDeepDive::transform_multiply(
    const std::vector<int>& numbers, int factor) {
  auto transformed_view =
      numbers | std::views::transform([factor](int n) { return n * factor; });
  return {transformed_view.begin(), transformed_view.end()};
}

std::vector<std::string> STLDeepDive::filter_long_words(
    const std::vector<std::string>& words, size_t min_length) {
  auto long_words_view =
      words | std::views::filter([min_length](const std::string& word) {
        return word.length() >= min_length;
      });
  return {long_words_view.begin(), long_words_view.end()};
}
