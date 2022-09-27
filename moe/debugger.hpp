#pragma once

#include "moe_macro.hpp"
#include <iostream>
#include <string_view>
#include <string>


#define moe_dbg(x) if(1) { \
    std::cerr << MOE_CODE_POS << " => [" #x "] : " << x << std::endl; \
}
