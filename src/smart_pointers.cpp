#include "smart_pointers.h"

#include <stdexcept>
#include <utility>

// FileHandler implementation
FileHandler::FileHandler(const std::string& filename)
    : file_(fopen(filename.c_str(), "w+"), FileDeleter{}) {
  if (!file_) {
    throw std::runtime_error("Failed to open file: " + filename);
  }
  std::cout << "File opened: " << filename << "\n";
}

void FileHandler::writeData(const std::string& data) const {
  if (file_) {
    fwrite(data.c_str(), sizeof(char), data.size(), file_.get());
    fflush(file_.get());
  }
}

std::string FileHandler::readData() const {
  // Return empty string if file not open
  if (!file_) return "";

  // Seek to beginning and read entire file content
  fseek(file_.get(), 0, SEEK_SET);
  std::string data;
  char buffer[1024];
  size_t bytesRead;
  while ((bytesRead = fread(buffer, 1, sizeof(buffer), file_.get())) > 0) {
    data.append(buffer, bytesRead);
  }
  return data;
}

// SharedResource implementation
SharedResource::SharedResource(std::string name) : name_(std::move(name)) {
  std::cout << "SharedResource created: " << name_ << "\n";
}

SharedResource::~SharedResource() {
  std::cout << "SharedResource destroyed: " << name_ << "\n";
}

void SharedResource::useResource() const {
  std::cout << "Using resource: " << name_ << "\n";
}

std::string SharedResource::getName() const { return name_; }

// Parent implementation
Parent::Parent(std::string name) : name_(std::move(name)) {
  std::cout << "Parent created: " << name_ << "\n";
}

Parent::~Parent() { std::cout << "Parent destroyed: " << name_ << "\n"; }

void Parent::setChild(const std::shared_ptr<Child>& child) { child_ = child; }

void Parent::showFamily() const {
  std::cout << "Parent " << name_;
  if (const auto child = child_.lock()) {
    std::cout << " has child " << child->getName();
  } else {
    std::cout << " has no child";
  }
  std::cout << "\n";
}

// Child implementation
Child::Child(std::string name) : name_(std::move(name)) {
  std::cout << "Child created: " << name_ << "\n";
}

Child::~Child() { std::cout << "Child destroyed: " << name_ << "\n"; }

void Child::setParent(const std::shared_ptr<Parent>& parent) {
  parent_ = parent;
}

void Child::showFamily() const {
  std::cout << "Child " << name_;
  if (const auto parent = parent_.lock()) {
    std::cout << " has parent " << parent->getName();
  } else {
    std::cout << " has no parent";
  }
  std::cout << "\n";
}

std::string Child::getName() const { return name_; }

// SmartContainer implementation
SmartContainer::SmartContainer() = default;

void SmartContainer::addResource(std::unique_ptr<std::string> resource) {
  resources_.push_back(std::move(resource));
}

void SmartContainer::processResources() const {
  for (const auto& resource : resources_) {
    if (resource) {
      std::cout << "Processing: " << *resource << "\n";
    }
  }
}

size_t SmartContainer::getResourceCount() const { return resources_.size(); }

// ExceptionSafeManager implementation
ExceptionSafeManager::ExceptionSafeManager() = default;

void ExceptionSafeManager::addResourceWithExceptionSafety(
    const std::string& data) {
  // Using make_shared ensures exception safety - if an exception occurs,
  // the shared_ptr won't be created, preventing resource leaks
  const auto resource = std::make_shared<std::string>(data);

  // Simulate potential exception after resource creation
  if (data == "throw") {
    throw std::runtime_error("Simulated exception");
  }

  resources_.push_back(resource);
  std::cout << "Added resource safely: " << data << "\n";
}

size_t ExceptionSafeManager::getResourceCount() const {
  return resources_.size();
}

// Factory functions
std::unique_ptr<FileHandler> createFileHandler(const std::string& filename) {
  return std::make_unique<FileHandler>(filename);
}

std::shared_ptr<SharedResource> createSharedResource(const std::string& name) {
  return std::make_shared<SharedResource>(name);
}

std::shared_ptr<Parent> createParent(const std::string& name) {
  return std::make_shared<Parent>(name);
}

std::shared_ptr<Child> createChild(const std::string& name) {
  return std::make_shared<Child>(name);
}

void createFamily(const std::shared_ptr<Parent>& parent,
                  const std::shared_ptr<Child>& child) {
  parent->setChild(child);
  child->setParent(parent);
}
