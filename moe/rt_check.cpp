#include "rt_check.hpp"
#include <cstdlib>


namespace moe {
std::string_view get_exit_info(ExitType panicType) {
	switch (panicType) {
		case ExitType::assert_failed: return "Assert failed.";
		case ExitType::panic: return "Panic.";
		case ExitType::run_to_todo_func: return "Run to a `todo`.";
		case ExitType::not_implemented: return "Not implemented.";
	}
	return "";
}

void moe_exit(ExitType exitType) {
	std::cerr << "Exit because [" << get_exit_info(exitType) << "]." << std::endl;
	exit(itype::i32(exitType));
}

void panic(std::string_view codePos, std::string_view msg) {
	if (!msg.empty()) {
		std::cerr << "Panic at [" << codePos << "] with message [" << msg << "]." << std::endl;
	} else {
		std::cerr << "Panic at [" << codePos << "]." << std::endl;
	}
	moe_exit(ExitType::panic);
}
}

