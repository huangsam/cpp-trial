#include "safe_counter.h"

#include <cstdint>
#include <gtest/gtest.h>

class SafeCounterTest : public ::testing::Test {
 protected:
  SafeCounter counter_obj;

  void TearDown() override {
    // Ensure threads are joined even if a test fails
    counter_obj.join_worker_threads();
  }
};

TEST_F(SafeCounterTest, MultipleThreadsIncrementSafely) {
  constexpr int num_threads = 5;
  constexpr int increments_per_thread = 10000;
  constexpr int64_t expected_total_count =
      static_cast<int64_t>(num_threads) * increments_per_thread;

  ASSERT_EQ(0, counter_obj.get_count());
  ASSERT_FALSE(counter_obj.are_workers_finished());

  counter_obj.start_worker_threads(num_threads, increments_per_thread);
  counter_obj.join_worker_threads();  // Wait for all threads to finish

  ASSERT_TRUE(counter_obj.are_workers_finished());
  // Crucially, with the mutex, this assertion should consistently pass
  ASSERT_EQ(expected_total_count, counter_obj.get_count());
}

TEST_F(SafeCounterTest, SingleThreadIncrement) {
  constexpr int num_threads = 1;
  constexpr int increments_per_thread = 500;
  constexpr int64_t expected_total_count =
      static_cast<int64_t>(num_threads) * increments_per_thread;

  counter_obj.start_worker_threads(num_threads, increments_per_thread);
  counter_obj.join_worker_threads();

  ASSERT_EQ(expected_total_count, counter_obj.get_count());
}
