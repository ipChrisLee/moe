#include <iostream>
#include <iomanip>
#include <charconv>

#include "decorator.hpp"
#include "arg_parser.hpp"
#include "stl_pro.hpp"
#include "rt_check.hpp"
#include "log.hpp"
#include "restorer.hpp"
#include "debugger.hpp"
#include "time_pro.hpp"
#include "empty_function.hpp"


void fun() {
	moe_slog_enable_here();
	moe_slog_info("Hello fun! ", MOE_FUNC_INFO);
}

void gun() {
	auto lLog = moe_llog("demo_folder/local_log.txt", " ", true, "//");
	lLog.info("Hello!");
	lLog.info("a -> b", 1);
	lLog.info("b -> c", 2);
}

struct Tes {
	int a = 10;
	
	int & get_a() {
		return a;
	}
} tes;


int main([[maybe_unused]]int argc, [[maybe_unused]]char ** argv) {
	struct CompilerInfo {
		bool help;
		int optiLevel;
		std::string outPath;
		std::vector<std::string> files;
	} cInfo{false, 0, "", { }};
	auto argParser = moe::ArgParser("STD Compiler");
	argParser.add_option(
		moe::ArgOption(
			'h', std::nullopt, false, [&cInfo](std::string_view) {
				cInfo.help = true;
			}, "Print help info before parsing."
		)
	);
	argParser.add_option(
		moe::ArgOption(
			'o', std::nullopt, true, [&cInfo](std::string_view path) {
				cInfo.outPath = path;
			}, "Output exe file path."
		)
	);
	argParser.add_option(
		moe::ArgOption(
			'O', std::nullopt, true, [&cInfo](std::string_view optiLevel) {
				std::from_chars(optiLevel.begin(), optiLevel.end(), cInfo.optiLevel);
			}, "Opti level of your compiler."
		)
	);
	argParser.add_func_to_handle_non_option_arg(
		[&cInfo](std::string_view path) {
			cInfo.files.emplace_back(path);
		}
	);
	argParser.parse(argc, argv);
	
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
				moe::LogContextItem::ch_r_bracket,
				moe::LogContextItem::ch_colon,
				moe::LogContextItem::ch_space,
			}
		));
	moe_slog_info("Hello 01");
	moe_slog_info("Hello 02");
	{
		moe_slog_disable_here();
		moe_slog_info("Hello 03");      //  disabled
	}
	moe_slog_info("Hello 04");          //  normal
	
	std::cout << moe::set_decorator(moe::Decorator::c_blue) << moe::now::formatTime()
	          << moe::reset_decorator() << std::endl;
	using namespace std::string_literals;
	auto s = "12 23 abc \n\n xy \n"s;
	auto res = moe::split_string_on_char(s, {'\n', ' '});
	std::for_each(
		res.begin(), res.end(), [](const auto & s) { std::cout << s << std::endl; }
	);
	moe_assert(res[0] == "12", "?");
	fun();
	gun();
//	moe_dbg("a");
	auto * a = new int(10);
	std::cerr << *a << std::endl;
	moe_dbg(a, *a);
	moe_dbg(tes.get_a());
	moe_r_set(tes.a, tes.get_a() + 1);
	moe_dbg(tes.get_a());
	return 0;
}
