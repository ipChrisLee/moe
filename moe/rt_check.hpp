#pragma once

#include "moe_macro.hpp"
#include "moe_typedef.hpp"
#include <cstdlib>
#include <string_view>
#include <iostream>
#include <cstdio>


namespace moe {
enum class ExitType : i8 {
	assert_failed = -128,
	panic,
	run_to_todo_func,
};


std::string_view get_exit_info(ExitType panicType);

[[noreturn]] void moe_exit(ExitType exitType);

#define moe_panic(msg) if(1){ \
    std::cerr << "Panic at [" MOE_CODE_POS "] with message [" msg "]." << std::endl; \
    moe_exit(moe::ExitType::panic);                         \
}

//  compile-time `to-do` check or run-time `to-do` check
#define moe_todo() static_assert(0, "TODO")
#define moe_rt_todo() if(1) { \
    std::cerr << "TODO on [" MOE_CODE_POS "]." <<std::endl; \
    moe::moe_exit(moe::ExitType::run_to_todo_func); \
}

#define moe_assert_selector(arg0, arg1, arg2, ...) arg2

#define moe_assert_with_msg(b, msg) { \
    if(!(b)){                   \
        std::cerr << "Assert [" #b "] failed at [" MOE_CODE_POS "] with message [" msg "]." << std::endl; \
        moe_exit(moe::ExitType::assert_failed);                             \
    }                         \
}
#define moe_assert_without_msg(b) { \
    if(!(b)){                   \
        std::cerr << "Assert [" #b "] failed at [" MOE_CODE_POS "]." << std::endl; \
        moe_exit(moe::ExitType::assert_failed);                             \
    }                         \
}

//  moe_assert(fun()) or moe_assert(fun(), "Haha")
#define moe_assert(...) moe_assert_selector(__VA_ARGS__, moe_assert_with_msg(__VA_ARGS__),moe_assert_without_msg(__VA_ARGS__))

}
