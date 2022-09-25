#pragma once

#include "moe_macro.hpp"
#include <iostream>
#include <string_view>


#define moe_dbg(x) std::cerr << MOE_CODE_POS << " => [" << #x << "] : " << x << std::endl

