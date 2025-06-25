#include "../src/person.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Define global constants for common test data or thresholds,
// or place them inside test fixtures if they are specific to a fixture.

// --- Constants for PersonTest ---
namespace PersonTestConstants {
constexpr auto TEST_PERSON_NAME = "John";
constexpr int TEST_PERSON_AGE = 28;
constexpr double TEST_PERSON_SALARY = 200000.00;
}  // namespace PersonTestConstants

class PersonTest : public testing::Test {
 protected:
  Person person;

  PersonTest()
      : person(PersonTestConstants::TEST_PERSON_NAME,
               Age(PersonTestConstants::TEST_PERSON_AGE),
               Salary(PersonTestConstants::TEST_PERSON_SALARY)) {}
};

TEST_F(PersonTest, NameGetter) {
  EXPECT_EQ(person.get_name(), PersonTestConstants::TEST_PERSON_NAME);
}

TEST_F(PersonTest, AgeGetter) {
  EXPECT_EQ(person.get_age(), PersonTestConstants::TEST_PERSON_AGE);
}

TEST_F(PersonTest, SalaryGetter) {
  EXPECT_DOUBLE_EQ(person.get_salary(),
                   PersonTestConstants::TEST_PERSON_SALARY);
}

// --- Constants and structures for PersonAnalyzerTest ---
namespace PersonAnalyzerTestConstants {
// For floating point comparisons
constexpr double DEFAULT_EPSILON = 1e-9;

// Staff member data (can be struct or individual constants)
// Using structs or named tuples can be even clearer for complex data sets
struct StaffMemberData {
  const char* name;
  int age;
  double salary;
};

// Define individual constants for staff members, making it clear which person
// is which
constexpr StaffMemberData ALICE_DATA = {
    .name = "Alice", .age = 30, .salary = 50000.0};
constexpr StaffMemberData BOB_DATA = {
    .name = "Bob", .age = 25, .salary = 45000.0};
constexpr StaffMemberData CHARLIE_DATA = {
    .name = "Charlie", .age = 35, .salary = 60000.0};
constexpr StaffMemberData DAVID_DATA = {
    .name = "David", .age = 40, .salary = 75000.0};
constexpr StaffMemberData EVE_DATA = {
    .name = "Eve", .age = 28, .salary = 48000.0};
constexpr StaffMemberData FRANK_DATA = {
    .name = "Frank", .age = 22, .salary = 30000.0};

// Thresholds for filtering
constexpr int AGE_THRESHOLD_STANDARD = 30;
constexpr double SALARY_THRESHOLD_STANDARD = 45000.0;
constexpr int AGE_THRESHOLD_NONE_ELIGIBLE_HIGH = 50;
constexpr double SALARY_THRESHOLD_NONE_ELIGIBLE_HIGH = 100000.0;
constexpr int AGE_THRESHOLD_ALL_ELIGIBLE = 0;  // Means no age filter
constexpr double SALARY_THRESHOLD_ALL_ELIGIBLE =
    30000.0;                           // Bob is excluded by this
constexpr int AGE_THRESHOLD_NONE = 0;  // No age threshold
constexpr double SALARY_THRESHOLD_NONE =
    0.0;  // No salary threshold (or lowest possible)

// Expected averages for various scenarios
constexpr double EXPECTED_AVG_STANDARD_FILTER = 185000.0 / 3.0;
constexpr double EXPECTED_AVG_NO_ELIGIBLE = 0.0;
constexpr double EXPECTED_AVG_ALL_ELIGIBLE = 278000.0 / 5.0;
constexpr double EXPECTED_AVG_MIN_SALARY_EDGE_CASE = 233000.0 / 4.0;

}  // namespace PersonAnalyzerTestConstants

class PersonAnalyzerTest : public testing::Test {
 protected:
  std::vector<Person> staff;

  void SetUp() override {
    staff = {{PersonAnalyzerTestConstants::ALICE_DATA.name,
              Age(PersonAnalyzerTestConstants::ALICE_DATA.age),
              Salary(PersonAnalyzerTestConstants::ALICE_DATA.salary)},
             {PersonAnalyzerTestConstants::BOB_DATA.name,
              Age(PersonAnalyzerTestConstants::BOB_DATA.age),
              Salary(PersonAnalyzerTestConstants::BOB_DATA.salary)},
             {PersonAnalyzerTestConstants::CHARLIE_DATA.name,
              Age(PersonAnalyzerTestConstants::CHARLIE_DATA.age),
              Salary(PersonAnalyzerTestConstants::CHARLIE_DATA.salary)},
             {PersonAnalyzerTestConstants::DAVID_DATA.name,
              Age(PersonAnalyzerTestConstants::DAVID_DATA.age),
              Salary(PersonAnalyzerTestConstants::DAVID_DATA.salary)},
             {PersonAnalyzerTestConstants::EVE_DATA.name,
              Age(PersonAnalyzerTestConstants::EVE_DATA.age),
              Salary(PersonAnalyzerTestConstants::EVE_DATA.salary)},
             {PersonAnalyzerTestConstants::FRANK_DATA.name,
              Age(PersonAnalyzerTestConstants::FRANK_DATA.age),
              Salary(PersonAnalyzerTestConstants::FRANK_DATA.salary)}};
  }

  static void expect_average_salary(const std::vector<Person>& people_data,
                                    const int age_threshold,
                                    const Salary min_salary,
                                    const double expected_average) {
    const double actual_average = calculate_average_eligible_salary_ranges(
        people_data, age_threshold, min_salary.value);
    ASSERT_NEAR(expected_average, actual_average,
                PersonAnalyzerTestConstants::DEFAULT_EPSILON);
  }
};

TEST_F(PersonAnalyzerTest, StandardFilteringCase) {
  // Age >= 30, Salary > 45000
  // Eligible: Alice (50000), Charlie (60000), David (75000)
  // Sum = 50000 + 60000 + 75000 = 185000
  // Count = 3
  // Average = 185000 / 3 = 61666.666...
  expect_average_salary(
      staff, PersonAnalyzerTestConstants::AGE_THRESHOLD_STANDARD,
      Salary(PersonAnalyzerTestConstants::SALARY_THRESHOLD_STANDARD),
      PersonAnalyzerTestConstants::EXPECTED_AVG_STANDARD_FILTER);
}

TEST_F(PersonAnalyzerTest, NoEligiblePeopleAgeTooHigh) {
  expect_average_salary(
      staff, PersonAnalyzerTestConstants::AGE_THRESHOLD_NONE_ELIGIBLE_HIGH,
      Salary(PersonAnalyzerTestConstants::SALARY_THRESHOLD_NONE),
      PersonAnalyzerTestConstants::EXPECTED_AVG_NO_ELIGIBLE);
}

TEST_F(PersonAnalyzerTest, NoEligiblePeopleSalaryTooHigh) {
  expect_average_salary(
      staff, PersonAnalyzerTestConstants::AGE_THRESHOLD_NONE,
      Salary(PersonAnalyzerTestConstants::SALARY_THRESHOLD_NONE_ELIGIBLE_HIGH),
      PersonAnalyzerTestConstants::EXPECTED_AVG_NO_ELIGIBLE);
}

TEST_F(PersonAnalyzerTest, AllEligibleLowThresholds) {
  // All staff members except Frank (salary 30000 <= 30000)
  // Eligible: Alice (50000), Bob (45000), Charlie (60000), David (75000), Eve
  // (48000) Sum = 50000 + 45000 + 60000 + 75000 + 48000 = 278000 Count = 5
  // Average = 278000 / 5 = 55600
  expect_average_salary(
      staff, PersonAnalyzerTestConstants::AGE_THRESHOLD_ALL_ELIGIBLE,
      Salary(PersonAnalyzerTestConstants::SALARY_THRESHOLD_ALL_ELIGIBLE),
      PersonAnalyzerTestConstants::EXPECTED_AVG_ALL_ELIGIBLE);
}

TEST_F(PersonAnalyzerTest, EmptyInputVector) {
  constexpr std::vector<Person> empty_staff = {};
  expect_average_salary(
      empty_staff, PersonAnalyzerTestConstants::AGE_THRESHOLD_NONE,
      Salary(PersonAnalyzerTestConstants::SALARY_THRESHOLD_NONE),
      PersonAnalyzerTestConstants::EXPECTED_AVG_NO_ELIGIBLE);
}

TEST_F(PersonAnalyzerTest, MinSalaryEdgeCaseExclusiveThreshold) {
  // If min_salary is 45000.0, Bob (45000.0) should be excluded because it's >
  // min_salary Eligible: Alice (50000), Charlie (60000), David (75000), Eve
  // (48000) Sum = 50000 + 60000 + 75000 + 48000 = 233000 Count = 4 Average =
  // 233000 / 4 = 58250
  expect_average_salary(
      staff, PersonAnalyzerTestConstants::AGE_THRESHOLD_NONE,
      Salary(PersonAnalyzerTestConstants::
                 SALARY_THRESHOLD_STANDARD),  // Re-using 45000.0 constant
      PersonAnalyzerTestConstants::EXPECTED_AVG_MIN_SALARY_EDGE_CASE);
}
