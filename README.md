# CPP Trial

Coding in C++ to explore tools like [CMake](https://cmake.org/) and [GoogleTest](https://google.github.io/googletest/).

## Getting started

Please install tools like `cmake` and `clang-format` first. You can do this with Homebrew on Mac by running `brew install cmake clang-format`.

Once all the tool requirements are met, you can proceed with building, testing and formatting code.

### Building code

To use `cmake` for building, run:

```shell
bash build.sh
```

From there, you can run binaries from `build/bin`.

```shell
./build/bin/main.out # for main executable
./build/bin/test.out # for GoogleTest executable
```

### Testing code

To use `ctest` for testing, run:

```shell
bash test.sh
```

### Formatting code

To use `clang-format` for formatting, run:

```shell
bash format.sh
```

## Helpful resources

- https://cplusplus.com/
- https://google.github.io/styleguide/cppguide.html
- https://google.github.io/googletest/reference/assertions.html
- https://cmake.org/cmake/help/git-master/manual/cmake-commands.7.html
- https://github.com/fffaraz/awesome-cpp
