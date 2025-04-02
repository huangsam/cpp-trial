# For more about phony targets:
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
# https://stackoverflow.com/a/2145605/2748860
.PHONY: run test

# Define all build dependencies
SRC_FILES := $(wildcard src/*.cpp src/*.hpp)
TEST_FILES := $(wildcard test/*.cpp test/*.hpp)
BUILD_DEPS := $(SRC_FILES) $(TEST_FILES)

# This Makefile runs and tests a C++ project using CMake and GoogleTest.
# The build artifacts will be placed in the build directory.
all: run test

run: build
	./build/bin/main.out

test: build
	./build/bin/test.out

# Step 1: Set source and build, download GoogleTest, generate CMake assets
# Step 2: Run the build process and place binaries in build/bin
build: $(BUILD_DEPS)
	cmake -S . -B build -D CMAKE_BUILD_TYPE=RELEASE
	cmake --build build

# Install required software:
# https://formulae.brew.sh/formula/cmake
# https://formulae.brew.sh/formula/clang-format
setup:
	brew install --formula cmake clang-format

# Choose LLVM style based on preferences:
# https://clang.llvm.org/docs/ClangFormatStyleOptions.html#basedonstyle
format:
	clang-format --style="LLVM" -i $(BUILD_DEPS)

clean:
	rm -rf build
