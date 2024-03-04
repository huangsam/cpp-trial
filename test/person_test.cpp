#include "../src/person.h"

#include <gtest/gtest.h>

class PersonTest : public testing::Test {
 protected:
  void SetUp() override {
    person = new Person("John", 28);
  }
  void TearDown() override {
    delete person;
  }
  Person *person;
};

TEST_F(PersonTest, NameGetter) {
  EXPECT_EQ(person->getName(), "John");
}

TEST_F(PersonTest, AgeGetter) {
  EXPECT_EQ(person->getAge(), 28);
}
