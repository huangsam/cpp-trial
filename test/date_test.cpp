#include "../src/date.h" // Assuming date.h defines Date, Year, Month, Day classes

#include <gtest/gtest.h>
#include <string> // For potential string conversions or debugging if needed

// Namespace for constants specific to Date testing
namespace DateTestConstants {
// Constants for 'one_date'
constexpr int ONE_DATE_YEAR = 2024;
constexpr int ONE_DATE_MONTH = 2;
constexpr int ONE_DATE_DAY = 1;

// Constants for 'newer_date'
// Note: year and month can be reused from ONE_DATE if they are the same
constexpr int NEWER_DATE_YEAR = 2024;
constexpr int NEWER_DATE_MONTH = 2;
constexpr int NEWER_DATE_DAY = 2;

// Constants for 'older_date'
constexpr int OLDER_DATE_YEAR = 2024;
constexpr int OLDER_DATE_MONTH = 1;
constexpr int OLDER_DATE_DAY = 31;
} // namespace DateTestConstants

class DateTest : public testing::Test {
 protected:
  Date one_date;
  Date newer_date;
  Date older_date;

  DateTest()
      // Use named constants for clarity
      : one_date(Year(DateTestConstants::ONE_DATE_YEAR),
                 Month(DateTestConstants::ONE_DATE_MONTH),
                 Day(DateTestConstants::ONE_DATE_DAY)),
        newer_date(Year(DateTestConstants::NEWER_DATE_YEAR),
                   Month(DateTestConstants::NEWER_DATE_MONTH),
                   Day(DateTestConstants::NEWER_DATE_DAY)),
        older_date(Year(DateTestConstants::OLDER_DATE_YEAR),
                   Month(DateTestConstants::OLDER_DATE_MONTH),
                   Day(DateTestConstants::OLDER_DATE_DAY)) {}
};

TEST_F(DateTest, EqualComparisons) {
  // These assertions inherently compare objects and don't involve magic numbers
  ASSERT_EQ(one_date, one_date);
  ASSERT_LE(one_date, one_date);
  ASSERT_GE(one_date, one_date);
}

TEST_F(DateTest, LesserComparisons) {
  // These assertions inherently compare objects and don't involve magic numbers
  ASSERT_LT(one_date, newer_date);
  ASSERT_LE(one_date, newer_date);
}

TEST_F(DateTest, GreaterComparisons) {
  // These assertions inherently compare objects and don't involve magic numbers
  ASSERT_GT(one_date, older_date);
  ASSERT_GE(one_date, older_date);
}

TEST_F(DateTest, UnequalComparisons) {
  // These assertions inherently compare objects and don't involve magic numbers
  ASSERT_NE(one_date, newer_date);
  ASSERT_NE(one_date, older_date);
}
