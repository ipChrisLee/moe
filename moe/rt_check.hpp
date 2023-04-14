#pragma once

#include "moe_macro.hpp"
#include "moe_typedef.hpp"
#include <cstdlib>
#include <string_view>
#include <iostream>
#include <cstdio>


namespace moe {
enum class ExitType : itype::i8 {
	assert_failed = -128,
	panic,
	run_to_todo_func,
	not_implemented,
};

std::string_view get_exit_info(ExitType panicType);

[[noreturn]] void moe_exit(ExitType exitType);

[[noreturn]] void panic(std::string_view codePos, std::string_view msg = "");

#define moe_panic(...) moe::panic(MOE_CODE_POS, ##__VA_ARGS__)

//  compile-time `to-do` check or run-time `to-do` check
#define moe_todo() static_assert(0, "TODO: " MOE_CODE_POS)
#define moe_rt_todo() if(1) { \
    std::cerr << "TODO on [" MOE_CODE_POS "]." <<std::endl; \
    moe::moe_exit(moe::ExitType::run_to_todo_func); \
}

#define moe_assert_selector(arg0, arg1, arg2, ...) arg2

#define moe_assert_with_msg(b, msg) if(1){ \
    if(!(b)){                   \
        std::cerr << "Assert [" #b "] failed at [" MOE_CODE_POS "] with message [" << msg << "]." << std::endl; \
        moe::moe_exit(moe::ExitType::assert_failed);                             \
    }                         \
}
#define moe_assert_without_msg(b) if(1){ \
    if(!(b)){                   \
        std::cerr << "Assert [" #b "] failed at [" MOE_CODE_POS "]." << std::endl; \
        moe::moe_exit(moe::ExitType::assert_failed);                             \
    }                         \
}

//  moe_assert(fun()) or moe_assert(fun(), "Haha")
#define moe_assert(...) moe_assert_selector(__VA_ARGS__, moe_assert_with_msg(__VA_ARGS__),moe_assert_without_msg(__VA_ARGS__))

#define moe_rt_warning(msg) if(1){ \
    std::cerr << "Warning at [" MOE_CODE_POS "] with message [" << msg << "]." << std::endl; \
}
#define moe_not_implemented(msg) if(1) { \
    std::cerr << "Not implemented at [" MOE_CODE_POS "] with message [" << msg << "]." << std::endl; \
    moe::moe_exit(moe::ExitType::not_implemented);                                         \
}
}
