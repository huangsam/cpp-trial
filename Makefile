.PHONY: run test format

SRC_FILES := $(wildcard src/*.cpp src/*.hpp)
TEST_FILES := $(wildcard test/*.cpp test/*.hpp)
BUILD_DEPS := $(SRC_FILES) $(TEST_FILES)

# This Makefile runs and tests a C++ project using CMake and GoogleTest.
# It assumes that the source files are in the src directory and the test files are in the test directory.
# The build artifacts will be placed in the build directory.
all: run test

run: build
	./build/bin/main.out

test: build
	./build/bin/test.out

format:
	clang-format --style="LLVM" -i $(BUILD_DEPS)

# Step 1: Set source and build, download GoogleTest, generate CMake assets
# Step 2: Run the build process and place binaries in build/bin
build: $(BUILD_DEPS)
	cmake -S . -B build
	cmake --build build

clean:
	rm -rf build
