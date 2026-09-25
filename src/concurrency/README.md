# Concurrency & Multithreading (`src/concurrency/`)

This directory covers concurrency, thread synchronization, race condition prevention, and asynchronous execution in modern C++.

## Files & Components

| Component | Focus & Role |
|---|---|
| **[`thread_simple.h`](thread_simple.h)** · [`cpp`](thread_simple.cpp) | Direct OS thread lifecycle, join semantics, and worker encapsulation |
| **[`safe_counter.h`](safe_counter.h)** · [`cpp`](safe_counter.cpp) | Critical section synchronization, RAII mutex locks, and atomic flags |
| **[`async_simple.h`](async_simple.h)** · [`cpp`](async_simple.cpp) | Asynchronous task execution and cross-thread future result retrieval |

---

## Realistic Engineering Goals: Bare-Metal Concurrency Without a VM

Unlike languages with managed green threads or virtual runtimes (Go goroutines, Java virtual threads, Node.js event loops), C++ concurrency operates **directly on native operating system threads and CPU memory**:

| VM / Runtime-Managed Concurrency | C++ Systems Concurrency | Engineering Implication |
|---|---|---|
| Background green-thread scheduler | Direct OS kernel threads (`std::thread`) | Predictable priority and hardware scheduling; zero runtime scheduler overhead. |
| Coarse / implicit synchronization | Explicit `std::mutex` & `std::lock_guard` | You control exact critical section granularity to minimize thread contention. |
| Implicit memory barriers | Explicit `std::atomic<T>` | Lock-free coordination mapped directly to hardware CPU atomic instructions. |
| Callback chains / runtime promises | `std::async` & `std::future` | Typed asynchronous task offloading with clean cross-thread exception propagation. |

---

## Detailed Topic Guides

### 1. Basic Thread Lifecycle (`thread_simple.h`)

#### Thread Creation and Joining
A `std::thread` represents an independent execution context. If a `std::thread` is destructed while still joinable (i.e. neither `join()` nor `detach()` was called), the runtime calls `std::terminate()`:

```cpp
void ThreadSimpleClass::start_worker_thread() {
  worker_finished_ = false;
  worker_thread_ = std::thread(&ThreadSimpleClass::worker_function, this);
}

void ThreadSimpleClass::join_worker_thread() {
  if (worker_thread_.joinable()) {
    worker_thread_.join();
  }
}
```

---

### 2. Thread Synchronization & Data Safety (`safe_counter.h`)

#### RAII Locking with `std::lock_guard`
Mutex locking must follow RAII principles so locks are reliably released even if an exception occurs during critical section execution:

```cpp
void SafeCounter::worker_function(int increments) {
  for (int i = 0; i < increments; ++i) {
    std::lock_guard<std::mutex> lock(mutex_); // Locks mutex upon entry, unlocks at scope exit
    ++count_;
  }
}

int64_t SafeCounter::get_count() const {
  std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(mutex_));
  return count_;
}
```

#### Lock-Free Atomic Coordination
Use `std::atomic<T>` for lightweight state flags that do not require full mutex contention:

```cpp
std::atomic<bool> all_workers_finished_{false};

// Reader
bool are_workers_finished() const {
  return all_workers_finished_.load();
}

// Writer
void join_worker_threads() {
  for (auto& thread : worker_threads_) {
    if (thread.joinable()) thread.join();
  }
  all_workers_finished_.store(true);
}
```

---

### 3. Asynchronous Programming (`async_simple.h`)

#### Launching Tasks with `std::async`
`std::async` abstracts thread creation, returning a `std::future<T>` that transparently manages value retrieval and exception propagation across threads:

```cpp
// Offload long-running work to a background thread
std::future<std::string> future_result = std::async(std::launch::async, greet);

// Block until ready and retrieve result
const std::string message = future_result.get();
```

#### Launch Policies:
- `std::launch::async`: Guarantees task runs on an asynchronous thread.
- `std::launch::deferred`: Runs synchronously on the calling thread only when `.get()` or `.wait()` is called.

---

## Key Learnings & Systems Insights

- **Always Join or Detach**: A joinable thread must be joined before destruction to prevent immediate process termination (`std::terminate`).
- **Minimize Critical Sections**: Keep lock durations as small as possible to minimize thread contention and CPU stalls.
- **Backend Relevance**:
  - Web servers handle concurrent requests by dispatching connections to worker thread pools.
  - Metrics aggregators use atomic primitives or partitioned mutexes to track request counters under high concurrency.
  - Background database writes and external API queries use async futures to avoid blocking main request threads.

---

## Running Associated Tests & Benchmarks

Unit tests:
- [test/concurrency/thread_simple_test.cpp](../../test/concurrency/thread_simple_test.cpp)
- [test/concurrency/safe_counter_test.cpp](../../test/concurrency/safe_counter_test.cpp)
- [test/concurrency/async_simple_test.cpp](../../test/concurrency/async_simple_test.cpp)

```shell
ctest --preset dev -R "ThreadSimpleTest|SafeCounterTest|AsyncSimpleTest" --output-on-failure

# Verify thread safety with ThreadSanitizer (data race detection)
cmake --preset tsan && cmake --build --preset tsan
ctest --preset tsan -R "ThreadSimpleTest|SafeCounterTest|AsyncSimpleTest" --output-on-failure
```

Performance benchmarks:
- [bench/concurrency_bench.cpp](../../bench/concurrency_bench.cpp)

```shell
cmake --preset release && cmake --build --preset release
./build/bin/bench/concurrency_bench.out
```
