#include "../src/memory_management.h"

#include <gtest/gtest.h>

#include <vector>

// Test custom allocators
TEST(MemoryManagementTest, ArenaAllocator) {
  ArenaAllocator arena(1024);

  void* ptr1 = arena.allocate(100);
  ASSERT_NE(ptr1, nullptr);

  void* ptr2 = arena.allocate(200);
  ASSERT_NE(ptr2, nullptr);

  EXPECT_GT(arena.remaining_space(), 0);

  arena.reset();
  EXPECT_EQ(arena.remaining_space(), 1024);
}

TEST(MemoryManagementTest, CustomAllocator) {
  ArenaAllocator arena(1024);
  const CustomAllocator<int> alloc(&arena);

  std::vector<int, CustomAllocator<int>> vec(alloc);
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

// Test memory pools
TEST(MemoryManagementTest, MemoryPool) {
  MemoryPool<int, 1024> pool;

  int* p1 = pool.allocate();
  int* p2 = pool.allocate();
  int* p3 = pool.allocate();

  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  ASSERT_NE(p3, nullptr);

  *p1 = 10;
  *p2 = 20;
  *p3 = 30;

  EXPECT_EQ(*p1, 10);
  EXPECT_EQ(*p2, 20);
  EXPECT_EQ(*p3, 30);
}

// Test RAII patterns
TEST(MemoryManagementTest, FileHandle) {
  // This test assumes we can create temporary files
  // In a real scenario, you'd use a temporary directory
  {
    const FileHandle file("test_raii.txt", "w");
    EXPECT_TRUE(file);
    if (file) {
      fprintf(file.get(), "RAII test");
    }
  }  // File should be automatically closed here
  // We can't easily test file closure without filesystem access
  SUCCEED();
}

TEST(MemoryManagementTest, Timer) {
  // Timer will print timing information
  // We just ensure it doesn't crash
  {
    Timer timer("Test timer");
    // Do some work
    volatile int sum = 0;
    for (int i = 0; i < 1000; ++i) {
      sum += i;
    }
  }  // Timer should print duration here
  SUCCEED();
}

// Test placement new
TEST(MemoryManagementTest, MemoryManager) {
  MemoryManager manager(1024);

  int* i = manager.construct<int>(42);
  ASSERT_NE(i, nullptr);
  EXPECT_EQ(*i, 42);

  auto* d = manager.construct<double>(3.14);
  ASSERT_NE(d, nullptr);
  EXPECT_DOUBLE_EQ(*d, 3.14);

  auto* s = manager.construct<std::string>("Hello");
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(*s, "Hello");

  MemoryManager::destroy(s);
  MemoryManager::destroy(d);
  MemoryManager::destroy(i);
}

// Test memory alignment
TEST(MemoryManagementTest, AlignedAllocator) {
  void* ptr = AlignedAllocator::allocate(64, 64);
  ASSERT_NE(ptr, nullptr);

  const auto addr = reinterpret_cast<uintptr_t>(ptr);
  EXPECT_EQ(addr % 64, 0);  // Should be 64-byte aligned

  AlignedAllocator::deallocate(ptr);
}

TEST(MemoryManagementTest, CacheLineAligned) {
  CacheLineAligned cla{};
  const auto addr = reinterpret_cast<uintptr_t>(&cla);
  EXPECT_EQ(addr % 64, 0);  // Should be cache-line aligned
}

// Test stack memory
TEST(MemoryManagementTest, StackVector) {
  StackVector<int, 10> vec;

  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 10);
  EXPECT_TRUE(vec.empty());

  for (int i = 0; i < 5; ++i) {
    vec.push_back(i * 10);
  }

  EXPECT_EQ(vec.size(), 5);
  EXPECT_FALSE(vec.empty());

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(vec[i], i * 10);
  }

  // Test move semantics
  vec.push_back(50);
  EXPECT_EQ(vec[5], 50);
}

// Test demonstration functions
TEST(MemoryManagementTest, DemonstrateFunctions) {
  // These functions print output, we just ensure they don't crash
  testing::internal::CaptureStdout();
  demonstrate_custom_allocators();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_FALSE(output.empty());

  testing::internal::CaptureStdout();
  demonstrate_memory_pools();
  output = testing::internal::GetCapturedStdout();
  EXPECT_FALSE(output.empty());

  testing::internal::CaptureStdout();
  demonstrate_raii_patterns();
  output = testing::internal::GetCapturedStdout();
  EXPECT_FALSE(output.empty());

  testing::internal::CaptureStdout();
  demonstrate_placement_new();
  output = testing::internal::GetCapturedStdout();
  EXPECT_FALSE(output.empty());

  testing::internal::CaptureStdout();
  demonstrate_memory_alignment();
  output = testing::internal::GetCapturedStdout();
  EXPECT_FALSE(output.empty());

  testing::internal::CaptureStdout();
  demonstrate_stack_memory();
  output = testing::internal::GetCapturedStdout();
  EXPECT_FALSE(output.empty());
}
