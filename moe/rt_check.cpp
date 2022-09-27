#include "rt_check.hpp"
#include <cstdlib>


namespace moe {
std::string_view get_exit_info(ExitType panicType) {
	switch (panicType) {
		case ExitType::assert_failed:
			return "Assert failed.";
		case ExitType::panic:
			return "Panic.";
		case ExitType::run_to_todo_func:
			return "Run to a `todo`.";
	}
}

void moe_exit(ExitType exitType) {
	std::cerr << "Exit because [" << get_exit_info(exitType) << "]." << std::endl;
	exit(i32(exitType));
}
}
