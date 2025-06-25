# C++ Trial

[![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/huangsam/cpp-trial/ci.yml)](https://github.com/huangsam/cpp-trial/actions)

Coding in C++ to explore tools like [CMake](https://cmake.org/) and [GoogleTest](https://google.github.io/googletest/).

<img src="images/cplusplus.webp" alt="C++" width="250px">

## Getting started

For everyone:

```shell
# Install developer tools
brew install --formula cmake llvm ninja

# Build binaries
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug

# Run binaries in their original form
./build/bin/main.out
./build/bin/test.out
```

For contributors:

```shell
# Ensure all files are formatted before PR
git ls-files '*.cpp' '*.h' | xargs clang-format -i
```

## Helpful resources

- <https://cplusplus.com/>
- <https://en.cppreference.com/w/>
- <https://google.github.io/styleguide/cppguide.html>
- <https://google.github.io/googletest/reference/assertions.html>
- <https://cmake.org/cmake/help/git-master/manual/cmake-commands.7.html>
- <https://clang.llvm.org/docs/ClangFormatStyleOptions.html>
- <https://clang.llvm.org/extra/clang-tidy/checks/list.html>
- <https://github.com/fffaraz/awesome-cpp>
