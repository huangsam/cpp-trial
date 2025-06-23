#include "../src/person.h"

#include <gtest/gtest.h>

class PersonTest : public testing::Test {
 protected:
  Person person;

  PersonTest() : person("John", 28, 200000.00) {}
};

TEST_F(PersonTest, NameGetter) { EXPECT_EQ(person.get_name(), "John"); }

TEST_F(PersonTest, AgeGetter) { EXPECT_EQ(person.get_age(), 28); }

TEST_F(PersonTest, SalaryGetter) {
  EXPECT_DOUBLE_EQ(person.get_salary(), 200000.00);
}

class PersonAnalyzerTest : public testing::Test {
 protected:
  std::vector<Person> staff;

  // SetUp is called before each test in this fixture
  void SetUp() override {
    staff = {
        {"Alice", 30, 50000.0},
        {"Bob", 25,
         45000.0},  // Excluded by min_salary threshold (<= 45000.0 for > check)
        {"Charlie", 35, 60000.0},
        {"David", 40, 75000.0},
        {"Eve", 28, 48000.0},   // Excluded by age threshold (< 30)
        {"Frank", 22, 30000.0}  // Excluded by both age and salary
    };
  }

  // Helper function to encapsulate common calculation and assertion logic
  static void expect_average_salary(const std::vector<Person>& people_data,
                                    const int age_threshold,
                                    const double min_salary,
                                    const double expected_average) {
    const double actual_average = calculate_average_eligible_salary_ranges(
        people_data, age_threshold, min_salary);
    ASSERT_NEAR(expected_average, actual_average, 1e-9);
  }
};

TEST_F(PersonAnalyzerTest, StandardFilteringCase) {
  // Age >= 30, Salary > 45000
  // Eligible: Alice (50000), Charlie (60000), David (75000)
  // Sum = 50000 + 60000 + 75000 = 185000
  // Count = 3
  // Average = 185000 / 3 = 61666.666...
  constexpr double expected_avg = 185000.0 / 3.0;
  expect_average_salary(staff, 30, 45000.0, expected_avg);
}

TEST_F(PersonAnalyzerTest, NoEligiblePeople_AgeTooHigh) {
  expect_average_salary(staff, 50, 0.0, 0.0);
}

TEST_F(PersonAnalyzerTest, NoEligiblePeople_SalaryTooHigh) {
  expect_average_salary(staff, 0, 100000.0, 0.0);
}

TEST_F(PersonAnalyzerTest, AllEligible_LowThresholds) {
  // All staff members except Frank (salary 30000 <= 30000)
  // Eligible: Alice (50000), Bob (45000), Charlie (60000), David (75000), Eve
  // (48000) Sum = 50000 + 45000 + 60000 + 75000 + 48000 = 278000 Count = 5
  // Average = 278000 / 5 = 55600
  constexpr double expected_avg = 278000.0 / 5.0;
  expect_average_salary(staff, 0, 30000.0, expected_avg);
}

TEST_F(PersonAnalyzerTest, EmptyInputVector) {
  constexpr std::vector<Person> empty_staff = {};
  expect_average_salary(empty_staff, 0, 0.0, 0.0);
}

TEST_F(PersonAnalyzerTest, MinSalaryEdgeCase_ExclusiveThreshold) {
  // If min_salary is 45000.0, Bob (45000.0) should be excluded because it's >
  // min_salary Eligible: Alice (50000), Charlie (60000), David (75000), Eve
  // (48000) Sum = 50000 + 60000 + 75000 + 48000 = 233000 Count = 4 Average =
  // 233000 / 4 = 58250
  constexpr double expected_avg = 233000.0 / 4.0;
  expect_average_salary(staff, 0, 45000.0, expected_avg);
}
