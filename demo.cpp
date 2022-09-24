#include <iostream>
#include <iomanip>

#include "decorator.hpp"
#include "arg_parser.hpp"
#include "stl_pro.hpp"


int main() {
	std::cout << moe::set_decorator(moe::Decorator::c_red) << "Hello!"
	          << moe::reset_decorator() << std::endl;
	return 0;
}
