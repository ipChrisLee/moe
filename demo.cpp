#include <iostream>
#include <iomanip>

#include "decorator.hpp"
#include "arg_parser.hpp"
#include "stl_pro.hpp"
#include "rt_check.hpp"


int main() {
	std::cout << moe::set_decorator(moe::Decorator::c_red) << "Hello!"
	          << moe::reset_decorator() << std::endl;
	moe_assert(1 == 2, "233");
	return 0;
}
