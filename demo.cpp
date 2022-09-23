#include <iostream>
#include <iomanip>

#include "src/setdecorator.hpp"
#include "src/ArgParser.hpp"
#include "src/STLPro.hpp"


int main() {
	std::cout << moe::set_decorator(moe::Decorator::c_red) << "Hello!"
	          << moe::reset_decorator() << std::endl;
	return 0;
}
