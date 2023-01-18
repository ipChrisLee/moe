#pragma once

#define MOE_CONCAT_TRUE(x, y) x ## y
#define MOE_CONCAT(x, y) MOE_CONCAT_TRUE(x,y)
#define MOE_STR(t) #t
#define MOE_LINE_STR(v) MOE_STR(v)
#define MOE_CODE_POS __FILE__ ":" MOE_LINE_STR(__LINE__)
#define MOE_FUNC_INFO __PRETTY_FUNCTION__

#define MOE_CONTEXT_FILE __FILE__
#define MOE_CONTEXT_LINE MOE_LINE_STR(__LINE__)

#define _moe_cVar MOE_CONCAT(_DO_NOT_USE_THIS_VAR, __COUNTER__)



