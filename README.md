# C++ Trial

Coding in C++ to explore tools like [CMake](https://cmake.org/) and [GoogleTest](https://google.github.io/googletest/).

## Getting started

Please install tools like `cmake` and `clang-format` first. You can do this with Homebrew on Mac by
running `brew install cmake clang-format`.

Once all tool requirements are met, you can proceed with building, testing and formatting code.

### Build binaries

To use `cmake` for building, run:

```shell
# Run end-to-end build
make build
```

### Run binaries

Now you can run the compiled binaries:

```shell
# Run main binary
make run

# Run test binary
make test
```

### Format code

To use `clang-format` for formatting, run:

```shell
# Run clang-format on CPP and HPP files
make format
```

## Helpful resources

- <https://cplusplus.com/>
- <https://en.cppreference.com/w/>
- <https://google.github.io/styleguide/cppguide.html>
- <https://google.github.io/googletest/reference/assertions.html>
- <https://cmake.org/cmake/help/git-master/manual/cmake-commands.7.html>
- <https://github.com/fffaraz/awesome-cpp>
- <https://github.com/oz123/awesome-c>
