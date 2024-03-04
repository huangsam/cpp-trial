#include "../src/person.h"

#include <gtest/gtest.h>

class PersonTest : public testing::Test {
 protected:
  Person person = Person("John", 28);
};

TEST_F(PersonTest, NameGetter) { EXPECT_EQ(person.getName(), "John"); }

TEST_F(PersonTest, AgeGetter) { EXPECT_EQ(person.getAge(), 28); }
