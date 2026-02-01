#ifndef SMART_POINTERS_H
#define SMART_POINTERS_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Custom deleter for unique_ptr demonstrating resource management
struct FileDeleter {
  void operator()(FILE* file) const {
    if (file) {
      std::cout << "Closing file with custom deleter\n";
      fclose(file);
    }
  }
};

// Class demonstrating unique_ptr with custom deleter
class FileHandler {
 public:
  explicit FileHandler(const std::string& filename);
  ~FileHandler() = default;

  // Deleted copy operations to enforce unique ownership
  FileHandler(const FileHandler&) = delete;
  FileHandler& operator=(const FileHandler&) = delete;

  // Allow move operations
  FileHandler(FileHandler&&) noexcept = default;
  FileHandler& operator=(FileHandler&&) noexcept = default;

  void writeData(const std::string& data) const;
  std::string readData() const;

 private:
  std::unique_ptr<FILE, FileDeleter> file_;
};

// Class demonstrating shared_ptr with reference counting
class SharedResource : public std::enable_shared_from_this<SharedResource> {
 public:
  explicit SharedResource(std::string name);
  ~SharedResource();

  void useResource() const;
  std::string getName() const;

 private:
  std::string name_;
};

// Classes demonstrating weak_ptr to break circular references
class Parent;
class Child;

class Parent {
 public:
  explicit Parent(std::string name);
  ~Parent();

  void setChild(const std::shared_ptr<Child>& child);
  void showFamily() const;
  std::weak_ptr<Child> getChild() const { return child_; }
  std::string getName() const { return name_; }

 private:
  std::string name_;
  std::weak_ptr<Child> child_;  // Weak reference to avoid circular dependency
};

class Child {
 public:
  explicit Child(std::string name);
  ~Child();

  void setParent(const std::shared_ptr<Parent>& parent);
  void showFamily() const;
  std::string getName() const;
  std::weak_ptr<Parent> getParent() const { return parent_; }

 private:
  std::string name_;
  std::weak_ptr<Parent> parent_;  // Weak reference to avoid circular dependency
};

// Class following Rule of Zero/Five with smart pointers
class SmartContainer {
 public:
  SmartContainer();
  ~SmartContainer() = default;

  // Rule of Zero: No need to define copy/move operations
  // Smart pointers handle resource management automatically

  void addResource(std::unique_ptr<std::string> resource);
  void processResources() const;
  size_t getResourceCount() const;

 private:
  std::vector<std::unique_ptr<std::string>> resources_;
};

// Exception safety demonstration
class ExceptionSafeManager {
 public:
  ExceptionSafeManager();
  ~ExceptionSafeManager() = default;

  // Demonstrates exception safety with smart pointers
  void addResourceWithExceptionSafety(const std::string& data);

  size_t getResourceCount() const;

 private:
  std::vector<std::shared_ptr<std::string>> resources_;
};

// Factory functions demonstrating make_unique and make_shared best practices
std::unique_ptr<FileHandler> createFileHandler(const std::string& filename);
std::shared_ptr<SharedResource> createSharedResource(const std::string& name);
std::shared_ptr<Parent> createParent(const std::string& name);
std::shared_ptr<Child> createChild(const std::string& name);

// Function to demonstrate connecting parent and child without circular
// references
void createFamily(const std::shared_ptr<Parent>& parent,
                  const std::shared_ptr<Child>& child);

#endif  // SMART_POINTERS_H
