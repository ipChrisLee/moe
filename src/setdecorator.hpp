/**
 * @brief Support for rich text (ANSI 8 color).
 * @author ipLee
 * @date Created 2022/08/27
 * @refitem https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
 */

#pragma once

#include <string>
#include <type_traits>


namespace moe {
enum Decorator : unsigned {
	c_black,
	c_red,
	c_green,
	c_yellow,
	c_blue,
	c_magenta,
	c_cyan,
	c_white,
	
	bg_black,
	bg_red,
	bg_green,
	bg_yellow,
	bg_blue,
	bg_magenta,
	bg_cyan,
	bg_white,
	
	d_bold,
	d_underline,
	d_reserved,
	
	reset,
};

std::string_view decorator_to_str(Decorator decorator);

template<typename ...T>
std::string set_decorator(T ... decorators) {
	static_assert(
		((std::is_same<T, Decorator>::value) && ...),
		"Arguments should be `Decorator`."
	);
	auto res = std::string();
	((res += decorator_to_str(decorators)), ...);
	return res;
}

std::string_view reset_decorator();


}
