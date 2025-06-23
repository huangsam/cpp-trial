#include "../src/person.hpp"

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
