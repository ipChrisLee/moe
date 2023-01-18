# 相比上版本改动

此节为Moe库NakagawaNatsuki版本相比KousakaReina版本的变动说明。

在KousakaReina版本，我设计了非常多的用于更好地C++编程的组件，但是在后续的调查中，我发现我的设计远不如目前已有库（如`boost`库、`fmtlib/fmt`库）设计优秀，而这个库的根本用处是为了方便编程，既然我的设计不如已有库，那就不应该重复设计，遂删除了这些设计。

目前已经决定删除的模块和用于替代的选项：

* `decorator`全模块和`fmt_string`全模块：可以使用[`fmtlib/fmt`](https://github.com/fmtlib/fmt)替代，他们的实现考虑更多且更通用。
* `log`全模块：可以使用[`boost.log`](https://www.boost.org/doc/libs/1_81_0/libs/log/doc/html/index.html)替代。
* `arg_parser`全模块：可以使用[`boost.Program_options`](https://www.boost.org/doc/libs/1_81_0/doc/html/program_options.html)替代。
* `stl_pro`以下部分模块：
  * `concat_all`函数：可以使用`fmtlib/fmt`替代。
  * `split_string_on_char`函数：参考[这个教程](https://www.geeksforgeeks.org/boostsplit-c-library/)，可以使用`boost::split`替代。
  * `sub_vector`函数：没啥用的函数。。。
* `time_pro`：参考[这个教程](https://thispointer.com/get-current-date-time-in-c-example-using-boost-date-time-library/)，可以使用`boost.Posix_Time`替代。

保留的模块，包括为何保留及改进的部分：

* `rt_check`：建议用`boost.Assert`替代`assert`宏。至于`todo`宏，我用google等搜索引擎找了下，似乎没有什么库有做`todo`宏，所以这里就保留下来了。

  改进：增加了运行时警告`moe_rt_warning`宏，在运行时输出位置和警告信息。

* `restorer`全模块：这个需求终究比较小众，所以保留了下来。

  改进：修复了之前一行不能有两个`moe_r_set`的问题，现在`moe_r_set`可以在同一行了。

  增加`defer`：在这个里面增加了`moe_defer`宏，具体作用就是：在当前作用域结束后，执行`moe_defer`里面的内容。

* `moe_typedef`全模块：这也是一个小众需求，所以保留了下来。

  改进：现在`moe_typedef`在`moe::itype`这个namespace下了。

* `stl_pro`以下模块：

  * `enum_in`函数：其他库大多转入了利用反射的enum（比如`Boost.Describe`），但是对于一般的`enum`，这个函数还是很有用的。

* `moe_concept`全模块和`empty_func`全模块：小众需求。

* `debugger`全模块：这个本身就是搬运的别的库，设计非常优秀，且那个源就是全网star比较高的一个实现Rust-like `dbg`的repo，故保留。

* `moe_macro`全模块：辅助模块，其他的模块必须要的。

  改进：

  * 增加了`_moe_cVar`宏，表示无意义的变量（比如用在`moe_defer`宏里）。
  * 改变了`MOE_CODE_POS`宏展开之后的样子，现在它可以在CLion中被识别及点进。

# 如何使用

To use this library with CMake, just clone this repo to the root of your project (we call it `projRoot`), and add these statements to your `projRoot/CMakeLists.txt`:

```cmake
add_subdirectory(./moe)
include_directories(./moe)
```

And add content below to your target.

```cmake
target_link_libraries(YOUR_TARGET moe)
```

And then you can use `#include <moe/decorator.hpp>`

If you don't want `moe_demo` be one of your targets, just delete last two line of `moe/CMakeLists.txt`.

