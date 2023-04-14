#include <iostream>
#include <iomanip>
#include <charconv>
#include <cstdlib>

#include "stl_pro.hpp"
#include "rt_check.hpp"
#include "restorer.hpp"
#include "debugger.hpp"


struct Tes {
	int a = 10;
	
	int & get_a() {
		return a;
	}
} tes;

void deprecated_fun() {
	moe_rt_deprecated_warning("");
	moe_rt_warning("?");
}

int main([[maybe_unused]]int argc, [[maybe_unused]]char ** argv) {
	using namespace std::string_literals;
	auto s = "12 23 abc \n\n xy \n"s;

//	moe_dbg("a");
	auto * a = new int(10);
	std::cerr << *a << std::endl;
	moe_dbg(a, *a);
	moe_dbg(tes.get_a());
	moe_r_set(tes.a, tes.get_a() + 1);
	moe_r_set(tes.a, tes.get_a() + 1);
	moe_dbg(tes.get_a());
	
	moe_defer(
		puts("aaa");
	)
	moe_defer(
		puts("bbb");
	)
	puts("ccc");
	deprecated_fun();
	deprecated_fun();
	return 0;
}
