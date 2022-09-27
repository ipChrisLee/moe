#pragma once

#include <memory>
#include <string_view>
#include <fstream>
#include "moe_macro.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include "time_pro.hpp"
#include <string>
#include <sstream>
#include <sstream>
#include "restorer.hpp"


namespace moe {

enum class LogContextItem {
	ch_space,       //  ' '
	ch_newline,     //  '\n'
	ch_colon,       //  ':'
	ch_l_bracket,   //  '['
	ch_r_bracket,   //  ']'
	
	code_file,      //  file of print context.
	code_line,      //  line of print context
	
	time_hour,      //  print time - hour
	time_minute,    //  print time - minute
	time_second,    //  print time - second
};


class LogContext {
  protected:
	std::vector<LogContextItem> items;
  
  public:
	explicit LogContext(std::vector<LogContextItem> items);
	
	[[nodiscard]] std::string
	to_string(std::string_view codeFile, std::string_view codeLine) const {
		auto fill_zero = [](i32 x) {
			auto ss = std::stringstream();
			ss << std::setfill('0') << std::setw(2) << x;
			auto res = std::string();
			ss >> res;
			return res;
		};
		auto res = std::string();
		for (auto item: items) {
			switch (item) {
				case LogContextItem::ch_space:
					res.push_back(' ');
					break;
				case LogContextItem::ch_newline:
					res.push_back('\n');
					break;
				case LogContextItem::code_file:
					res += codeFile;
					break;
				case LogContextItem::code_line:
					res += codeLine;
					break;
				case LogContextItem::ch_colon:
					res.push_back(':');
					break;
				case LogContextItem::time_hour: {
					res += fill_zero(now::hour());
					break;
				}
				case LogContextItem::time_minute:
					res += fill_zero(now::minute());
					break;
				case LogContextItem::time_second:
					res += fill_zero(now::second());
					break;
				case LogContextItem::ch_l_bracket:
					res.push_back('[');
					break;
				case LogContextItem::ch_r_bracket:
					res.push_back(']');
					break;
			}
		}
		return res;
	}
};

class STDLog {
	friend void register_std_log(
		std::string_view logFilePath, std::string_view sep, LogContext header
	);
	
	friend STDLog & std_log();
  
  protected:
	static std::unique_ptr<STDLog> upStdLog;
  
  protected:
	std::ofstream ofs;
	LogContext header;
	std::string_view sep;
	
	STDLog(std::string_view logFilePath, LogContext header, std::string_view sep);
  
  
  public:
	bool enabled;
	
	void set_sep(std::string_view newSep) { sep = newSep; }
	
	template<typename  ... Ts>
	void info(std::string_view codeFile, std::string_view codeLine, Ts  ... ts) {
		if (enabled) {
			ofs << header.to_string(codeFile, codeLine);
			((ofs << ts << sep), ...);
			if (sep == "\n") {
			} else {
				ofs << std::endl;
			}
			ofs.flush();
		}
	}
};

void register_std_log(
	std::string_view logFilePath, std::string_view sep = " ",
	LogContext header = LogContext(
		{
			LogContextItem::ch_l_bracket, LogContextItem::code_file,
			LogContextItem::ch_colon, LogContextItem::ch_colon,
			LogContextItem::code_line, LogContextItem::ch_r_bracket,
			LogContextItem::ch_space,
			LogContextItem::ch_colon,
			LogContextItem::ch_space,
		}
	));

STDLog & std_log();

#define moe_slog_info(...) moe::std_log().info(MOE_CONTEXT_FILE,MOE_CONTEXT_LINE,__VA_ARGS__)

#define moe_slog_enable_here() moe_r_set(moe::std_log().enabled, true)
#define moe_slog_disable_here() moe_r_set(moe::std_log().enabled, false)

class LocalLog {
  protected:
	std::ofstream ofs;
	std::string_view sep;
	bool enabled;
  
  public:
	explicit LocalLog(
		std::string_view logFilePath, std::string_view sep = " ", bool enable = true,
		const std::string & head = ""
	);
	
	template<typename  ... Ts>
	void info(Ts  ... ts) {
		if (enabled) {
			((ofs << ts << sep), ...);
			if (sep == "\n") {
			} else {
				ofs << std::endl;
			}
			ofs.flush();
		}
	}
};

#define moe_llog(logFilePath, sep, enable, headComment) \
    moe::LocalLog(logFilePath, sep, enable, moe::concat_all(headComment "\t", MOE_CODE_POS "\t", moe::now::formatTime()))
	
	
}
