#include "../src/move_semantics.h"

#include <gtest/gtest.h>

#include <string>

// Test fixture for ResourceManager
class ResourceManagerTest : public testing::Test {
 protected:
  ResourceManager rm_;
  const size_t test_size_ = 10;

  void SetUp() override { rm_ = ResourceManager(test_size_); }
};

TEST_F(ResourceManagerTest, DefaultConstruction) {
  const ResourceManager rm;
  EXPECT_EQ(rm.size(), 0);
}

TEST_F(ResourceManagerTest, SizedConstruction) {
  EXPECT_EQ(rm_.size(), test_size_);
}

TEST_F(ResourceManagerTest, CopyConstruction) {
  const ResourceManager copy = rm_;
  EXPECT_EQ(copy.size(), rm_.size());
  EXPECT_EQ(copy.data(), rm_.data());
}

TEST_F(ResourceManagerTest, CopyAssignment) {
  ResourceManager copy;
  copy = rm_;
  EXPECT_EQ(copy.size(), rm_.size());
  EXPECT_EQ(copy.data(), rm_.data());
}

TEST_F(ResourceManagerTest, MoveConstruction) {
  const ResourceManager moved = std::move(rm_);
  EXPECT_EQ(moved.size(), test_size_);
  EXPECT_GE(rm_.size(), 0);
}

TEST_F(ResourceManagerTest, MoveAssignment) {
  const ResourceManager moved = std::move(rm_);
  EXPECT_EQ(moved.size(), test_size_);
  EXPECT_GE(rm_.size(), 0);
}

TEST_F(ResourceManagerTest, ConsumeRvalue) {
  std::vector vec = {1, 2, 3, 4, 5};
  rm_.consume_rvalue(std::move(vec));
  EXPECT_EQ(rm_.size(), 5);
  EXPECT_TRUE(vec.empty());
}

TEST_F(ResourceManagerTest, CreateLargeResource) {
  const ResourceManager large = ResourceManager::create_large_resource(100);
  EXPECT_EQ(large.size(), 100);
}

TEST_F(ResourceManagerTest, DemonstrateMove) {
  ResourceManager::demonstrate_move(rm_);
  EXPECT_GE(rm_.size(), 0);
}

// Test perfect forwarding template
TEST(MoveSemanticsTest, PerfectForwarding) {
  ResourceManager rm(5);

  testing::internal::CaptureStdout();
  process_resource(rm);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Processed resource with 5 elements"),
            std::string::npos);

  testing::internal::CaptureStdout();
  process_resource(std::move(rm));
  output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Processed resource with"), std::string::npos);
}

// Test MoveOnlyType
TEST(MoveOnlyTypeTest, DefaultConstruction) {
  const MoveOnlyType mot;
  EXPECT_EQ(mot.get_data(), "default");
}

TEST(MoveOnlyTypeTest, ValueConstruction) {
  const MoveOnlyType mot("test data");
  EXPECT_EQ(mot.get_data(), "test data");
}

TEST(MoveOnlyTypeTest, MoveConstruction) {
  MoveOnlyType original("original");
  const MoveOnlyType moved = std::move(original);
  EXPECT_EQ(moved.get_data(), "original");
}

TEST(MoveOnlyTypeTest, MoveAssignment) {
  MoveOnlyType mot1("first");
  MoveOnlyType mot2("second");
  mot2 = std::move(mot1);
  EXPECT_EQ(mot2.get_data(), "first");
}

// Test performance demonstration
TEST(MoveSemanticsTest, PerformanceDemonstration) {
  testing::internal::CaptureStdout();
  demonstrate_move_vs_copy();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find("Move vs Copy Demonstration"), std::string::npos);
  EXPECT_NE(output.find("Move is approximately"), std::string::npos);
  EXPECT_NE(output.find("Use move when"), std::string::npos);
}
