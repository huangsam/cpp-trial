#include "thread_simple.h"

#include <gtest/gtest.h>

class ThreadSimpleTest : public ::testing::Test {
 protected:
  ExampleThreadClass obj;
};

TEST_F(ThreadSimpleTest, WorkerThreadCompletesTask) {
  ASSERT_FALSE(obj.is_worker_finished());   // Initially not finished
  ASSERT_EQ("", obj.get_worker_message());  // Message should be empty initially

  obj.start_worker_thread();
  obj.join_worker_thread();  // Wait for the thread to finish

  ASSERT_TRUE(obj.is_worker_finished());  // Should be finished after joining
  ASSERT_EQ("Hello from the worker thread!",
            obj.get_worker_message());  // Check the message
}

TEST_F(ThreadSimpleTest, StateBeforeThreadStarts) {
  // Ensure initial state is as expected before the thread is even started
  ASSERT_FALSE(obj.is_worker_finished());
  ASSERT_EQ("", obj.get_worker_message());
}
