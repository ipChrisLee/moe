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
					res += std::to_string(now::hour());
					break;
				}
				case LogContextItem::time_minute:
					res += std::to_string(now::minute());
					break;
				case LogContextItem::time_second:
					res += std::to_string(now::second());
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
	friend void register_std_log(std::string_view logFilePath, LogContext header);
	
	friend STDLog & std_log();
  
  protected:
	static std::unique_ptr<STDLog> upStdLog;
  
  protected:
	std::ofstream ofs;
	LogContext header;
	
	STDLog(std::string_view logFilePath, LogContext header);
  
  
  public:
	bool enabled;
	
	template<typename  ... Ts>
	void info(std::string_view codeFile, std::string_view codeLine, Ts  ... ts) {
		if (enabled) {
			ofs << header.to_string(codeFile, codeLine);
			((ofs << ts), ...);
			ofs << std::endl;
		}
	}
};

void register_std_log(
	std::string_view logFilePath, LogContext header = LogContext(
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


}
