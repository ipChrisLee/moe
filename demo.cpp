#include <iostream>
#include <iomanip>

#include "decorator.hpp"
#include "arg_parser.hpp"
#include "stl_pro.hpp"
#include "rt_check.hpp"


int main() {
	std::cout << moe::set_decorator(moe::Decorator::c_red) << "Hello!"
	          << moe::reset_decorator() << std::endl;
	auto res = moe::split_string_on_char("12 23 abc \n\n xy \n", {'\n', ' '});
	std::for_each(
		res.begin(), res.end(), [](const auto & s) { std::cout << s << std::endl; }
	);
	
	return 0;
}
