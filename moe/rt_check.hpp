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
};


std::string_view get_exit_info(ExitType panicType);

[[noreturn]] void moe_exit(ExitType exitType);

#define moe_exit_with_reason()

#define moe_panic(msg) { \
    std::cerr << "Panic at [" MOE_CODE_POS "] with message [" msg "]." << std::endl; \
    moe_exit(moe::ExitType::panic);                         \
}

#define moe_assert_selector(arg0, arg1, arg2, ...) arg2

#define moe_assert_with_msg(b, msg) { \
    if(!(b)){                   \
        std::cerr << "Assert [" #b "] failed at [" MOE_CODE_POS "] with message [" #msg "]." << std::endl; \
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
