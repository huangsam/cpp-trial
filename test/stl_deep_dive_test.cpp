#include "../src/stl_deep_dive.h"

#include <gtest/gtest.h>

#include <map>
#include <set>
#include <string>
#include <vector>

TEST(STLDeepDiveTest, FilterEvenNumbers) {
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
  std::vector<int> evens = STLDeepDive::filter_even(numbers);
  EXPECT_EQ(evens, std::vector<int>({2, 4, 6}));
}

TEST(STLDeepDiveTest, SumVector) {
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  int sum = STLDeepDive::sum_vector(numbers);
  EXPECT_EQ(sum, 15);
}

TEST(STLDeepDiveTest, CountWords) {
  std::vector<std::string> words = {"hello", "world", "hello", "cpp"};
  std::map<std::string, int> word_count = STLDeepDive::count_words(words);
  EXPECT_EQ(word_count["hello"], 2);
  EXPECT_EQ(word_count["world"], 1);
  EXPECT_EQ(word_count["cpp"], 1);
}

TEST(STLDeepDiveTest, MostFrequentWord) {
  std::map<std::string, int> word_count = {{"hello", 2}, {"world", 1}, {"cpp", 3}};
  std::string most_frequent = STLDeepDive::most_frequent_word(word_count);
  EXPECT_EQ(most_frequent, "cpp");
}

TEST(STLDeepDiveTest, UniqueElements) {
  std::vector<int> numbers = {1, 2, 2, 3, 3, 3};
  std::set<int> unique = STLDeepDive::unique_elements(numbers);
  EXPECT_EQ(unique, std::set<int>({1, 2, 3}));
}

TEST(STLDeepDiveTest, SetIntersection) {
  std::set<int> set1 = {1, 2, 3, 4};
  std::set<int> set2 = {3, 4, 5, 6};
  std::set<int> intersection = STLDeepDive::intersection(set1, set2);
  EXPECT_EQ(intersection, std::set<int>({3, 4}));
}

TEST(STLDeepDiveTest, SortVector) {
  std::vector<int> numbers = {3, 1, 4, 1, 5};
  STLDeepDive::sort_vector(numbers);
  EXPECT_EQ(numbers, std::vector<int>({1, 1, 3, 4, 5}));
}

TEST(STLDeepDiveTest, ContainsElement) {
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  EXPECT_TRUE(STLDeepDive::contains_element(numbers, 3));
  EXPECT_FALSE(STLDeepDive::contains_element(numbers, 6));
}

TEST(STLDeepDiveTest, TransformMultiply) {
  std::vector<int> numbers = {1, 2, 3};
  std::vector<int> multiplied = STLDeepDive::transform_multiply(numbers, 2);
  EXPECT_EQ(multiplied, std::vector<int>({2, 4, 6}));
}

TEST(STLDeepDiveTest, FilterLongWords) {
  std::vector<std::string> words = {"hi", "hello", "world", "cpp"};
  std::vector<std::string> long_words = STLDeepDive::filter_long_words(words, 5);
  EXPECT_EQ(long_words, std::vector<std::string>({"hello", "world"}));
}
