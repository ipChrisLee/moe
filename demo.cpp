#include <iostream>
#include <iomanip>

#include "decorator.hpp"
#include "ArgParser.hpp"
#include "STLPro.hpp"


int main() {
	std::cout << moe::set_decorator(moe::Decorator::c_red) << "Hello!"
	          << moe::reset_decorator() << std::endl;
	return 0;
}
