This is library written by ipLee when participating in CSC2022. 

Compile this lib with C++17 and newer standard.

This lib provides some useful tools for C++ coding:

* `set_decorator` can be used to print colorful text on terminal.

  ```c++
  std::cout << moe::set_decorator(moe::bg_blue, moe::c_red, moe::d_underline)
            << "Hello! ";
  std::cout << "How are you?" << std::endl;
  std::cout << moe::set_decorator(moe::bg_cyan, moe::c_black, moe::d_bold)
            << "Fine, thank you! And you?" << std::endl;
  std::cout << moe::set_decorator(moe::reset);
  std::cout << "End of communication" << std::endl;
  ```

  ![](ref_of_readme/set_decorator_demo.png)

* `ArgParser` is like python lib [argparser](https://docs.python.org/3/library/argparse.html), makes it easy to write user-friendly command-line interfaces:

  For example, for llvm command line options, you can just code:

  ```c++
  auto argParser = moe::ArgParser();
  auto addDebugInfo = false;
  auto emitLLVM = false;
  auto verbose = false;
  auto fromFilePaths = std::vector<std::string>();
  auto toFilePath = std::string();
  auto dotFilePath = std::string();
  argParser.add_option(
      'g', nullptr, false, [&addDebugInfo](const char *) {
          addDebugInfo = true;
      }
  );
  argParser.add_option(
      0, "emit-llvm", false, [&emitLLVM](const char *) {
          emitLLVM = true;
      }
  );
  argParser.add_option(
      'v', "verbose", false, [&verbose](const char *) {
          verbose = true;
      }
  );
  argParser.add_option(
      'o', nullptr, true, [&toFilePath](const char * s) {
          toFilePath = s;
      }
  );
  argParser.add_option(
      0, "dot", true, [&dotFilePath](const char * s) {
          dotFilePath = s;
      }
  );
  argParser.add_func_to_handle_non_option_arg(
      [&fromFilePaths](const char * s) {
          fromFilePaths.emplace_back(s);
      }
  );
  argParser.parse(argc, argv);
  ```

* Some useful concept, like `cloneable` support of C++ (use smart pointer):

  Assume `B` is derived from`A`, and `A` derived from `moe::Cloneable`, and you implement `A::clone_to_unique_ptr_to_impl`, `B::clone_to_unique_ptr_to_impl` correctly, you can:

  ```c++
  std::unique_ptr<A> upA=std::make_unique<B>();
  auto upX=upA->clone_to_unique_ptr();
  auto upB=moe::dyn_cast_up<B>(upA->clone_to_unique_ptr());
  ```

  `clone_to_unique_ptr` will check if the entity who calls `clone_to_unique_ptr_to_impl` has the same type of what it clones to. This can prevent you from forgetting implementing `clone_to_unique_ptr_to_impl` of derived class.

* Some string support:

  `concat_all` can concat all things into one string (if you have implemented `operatr<<(std::ostream &, T t)`). For example:

  ```c++
  auto res=moe::concat_all(1, std::setprecision(1), 0.234, " 233", "?", 114514);
  ```

  Here `res` is `10.2 233?114514`.

To use this library with CMake, just clone this repo to the root of your project (we call it `projRoot`), and add these statements to your `projRoot/CMakeLists.txt`:

```cmake
target_link_libraries(YOUR_TARGET PUBLIC moe)
target_include_directories(YOUR_TARGET PUBLIC moe)
```

And then you can use `#include <moe/decorator.hpp>`

If you don't want `moe_demo` be one of your targets, just delete last two line of `moe/CMakeLists.txt`.

