#include "../src/smart_pointers.h"

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Test fixture for smart pointers tests
class SmartPointersTest : public testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(SmartPointersTest, UniquePtrWithCustomDeleter) {
  // Test unique_ptr with custom deleter
  auto fileHandler = createFileHandler("test_file.txt");
  ASSERT_TRUE(fileHandler);

  fileHandler->writeData("Hello, World!");
  EXPECT_EQ(fileHandler->readData(), "Hello, World!");

  // File should be automatically closed by custom deleter
}

TEST_F(SmartPointersTest, SharedPtrReferenceCounting) {
  // Test shared_ptr reference counting behavior
  auto resource1 = createSharedResource("Resource1");
  ASSERT_TRUE(resource1);
  EXPECT_EQ(resource1->getName(), "Resource1");

  {
    const auto& resource2 = resource1;  // Copy shared_ptr
    EXPECT_EQ(resource1->getName(), "Resource1");
    EXPECT_EQ(resource2->getName(), "Resource1");
    // Both pointers should point to the same object
    EXPECT_EQ(resource1.get(), resource2.get());
  }  // resource2 goes out of scope

  // resource1 should still be valid
  EXPECT_EQ(resource1->getName(), "Resource1");
}

TEST_F(SmartPointersTest, WeakPtrBreaksCircularReferences) {
  // Test weak_ptr breaking circular references
  auto parent = createParent("Dad");
  auto child = createChild("Son");

  createFamily(parent, child);

  parent->showFamily();
  child->showFamily();

  // Check that weak_ptr can lock to shared_ptr
  EXPECT_TRUE(parent->getChild().lock());
  EXPECT_TRUE(child->getParent().lock());

  // Reset one shared_ptr - circular reference is broken
  parent.reset();
  EXPECT_FALSE(child->getParent().lock());  // Parent is gone
  EXPECT_TRUE(child);                       // Child still exists
}

TEST_F(SmartPointersTest, MakeUniqueAndMakeShared) {
  // Test make_unique and make_shared best practices
  auto uniquePtr = std::make_unique<std::string>("unique");
  auto sharedPtr = std::make_shared<std::string>("shared");

  EXPECT_EQ(*uniquePtr, "unique");
  EXPECT_EQ(*sharedPtr, "shared");

  // make_unique prevents exceptions during construction
  // make_shared is more efficient than separate allocation
}

TEST_F(SmartPointersTest, RuleOfZeroWithSmartPointers) {
  // Test Rule of Zero - no need to define copy/move operations
  SmartContainer container;

  container.addResource(std::make_unique<std::string>("Resource1"));
  container.addResource(std::make_unique<std::string>("Resource2"));

  EXPECT_EQ(container.getResourceCount(), 2);

  // Container destruction automatically cleans up resources
  // No manual copy/move operations needed
}

TEST_F(SmartPointersTest, ExceptionSafetyWithSmartPointers) {
  ExceptionSafeManager manager;

  // Normal operation
  EXPECT_NO_THROW(manager.addResourceWithExceptionSafety("safe"));
  EXPECT_EQ(manager.getResourceCount(), 1);

  // Exception safety test
  EXPECT_THROW(manager.addResourceWithExceptionSafety("throw"),
               std::runtime_error);
  // Resource should not be added due to exception
  EXPECT_EQ(manager.getResourceCount(), 1);
}

TEST_F(SmartPointersTest, UniquePtrOwnershipTransfer) {
  SmartContainer container;

  auto resource = std::make_unique<std::string>("transfer");
  container.addResource(std::move(resource));

  // resource is now null
  EXPECT_FALSE(resource);

  EXPECT_EQ(container.getResourceCount(), 1);
}

// Helper methods for weak_ptr test (assuming we add these to classes)
TEST_F(SmartPointersTest, WeakPtrLocking) {
  auto parent = createParent("Parent");
  auto child = createChild("Child");

  // Initially no weak references
  EXPECT_FALSE(parent->getChild().lock());
  EXPECT_FALSE(child->getParent().lock());

  createFamily(parent, child);

  // Now weak references work
  auto childFromParent = parent->getChild().lock();
  auto parentFromChild = child->getParent().lock();

  ASSERT_TRUE(childFromParent);
  ASSERT_TRUE(parentFromChild);

  EXPECT_EQ(childFromParent->getName(), "Child");
  EXPECT_EQ(parentFromChild->getName(), "Parent");
}
