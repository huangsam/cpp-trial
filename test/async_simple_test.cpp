#include "../src/async_simple.h"

#include <gtest/gtest.h>

#include <future>

TEST(AsyncSimpleTest, Hello) {
  std::future<std::string> future_result =
      std::async(std::launch::async, greet);
  const std::string& message = future_result.get();
  ASSERT_EQ(std::string("Hello, World! from std::async"), message);
}
