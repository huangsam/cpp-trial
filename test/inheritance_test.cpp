#include "../src/inheritance.h"

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Test fixture for inheritance and polymorphism tests
class InheritanceTest : public testing::Test {
 protected:
  std::unique_ptr<Dog> dog_;
  std::unique_ptr<Cat> cat_;

  void SetUp() override {
    dog_ = std::make_unique<Dog>("Buddy");
    cat_ = std::make_unique<Cat>("Whiskers");
  }
};

TEST_F(InheritanceTest, DogSpeaksCorrectly) {
  EXPECT_EQ(dog_->speak(), "Woof!");
  EXPECT_EQ(dog_->get_name(), "Buddy");
}

TEST_F(InheritanceTest, CatSpeaksCorrectly) {
  EXPECT_EQ(cat_->speak(), "Meow!");
  EXPECT_EQ(cat_->get_name(), "Whiskers");
}

TEST_F(InheritanceTest, PolymorphismWithDog) {
  // Demonstrate polymorphism: treat Dog as Animal
  const Animal& animal = *dog_;
  EXPECT_EQ(make_animal_speak(animal), "Buddy says: Woof!");
}

TEST_F(InheritanceTest, PolymorphismWithCat) {
  // Demonstrate polymorphism: treat Cat as Animal
  const Animal& animal = *cat_;
  EXPECT_EQ(make_animal_speak(animal), "Whiskers says: Meow!");
}
