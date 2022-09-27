#include <iostream>
#include <iomanip>

#include "decorator.hpp"
#include "arg_parser.hpp"
#include "stl_pro.hpp"
#include "rt_check.hpp"
#include "log.hpp"
#include "restorer.hpp"
#include "debugger.hpp"
#include "time_pro.hpp"


void fun() {
	moe_slog_enable_here();
	moe_slog_info("Hello fun! ", MOE_FUNC_INFO);
}

void gun() {
	auto lLog = moe_llog("demo_folder/local_log.txt", "\n", true, "//");
	lLog.info("Hello!");
	lLog.info("a -> b");
	lLog.info("b -> c");
}


int main() {
	moe::register_std_log(
		"demo_folder/log.txt", " ",
		moe::LogContext(
			{
				moe::LogContextItem::ch_l_bracket,
				moe::LogContextItem::code_file,
				moe::LogContextItem::ch_colon, moe::LogContextItem::ch_colon,
				moe::LogContextItem::code_line,
				moe::LogContextItem::ch_space,
				moe::LogContextItem::time_hour,
				moe::LogContextItem::ch_colon,
				moe::LogContextItem::time_minute,
				moe::LogContextItem::ch_r_bracket
			}
		));
	moe_slog_info("Hello 01");
	moe_slog_info("Hello 02");
	moe_slog_disable_here();
	moe_slog_info("Hello 03");      //  disabled
	
	std::cout << moe::set_decorator(moe::Decorator::c_blue) << moe::now::formatTime()
	          << moe::reset_decorator() << std::endl;
	auto res = moe::split_string_on_char("12 23 abc \n\n xy \n", {'\n', ' '});
	std::for_each(
		res.begin(), res.end(), [](const auto & s) { std::cout << s << std::endl; }
	);
	moe_assert(res[0] == "12", "?");
	fun();
	gun();
	moe_dbg("a");
	return 0;
}
