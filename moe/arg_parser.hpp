//
// Created by 李远铄 on 2022/8/27.
//

#pragma once

#include <functional>
#include <vector>
#include <string_view>
#include <string>
#include <optional>


namespace moe {

class ArgOption {
  public:
	const std::optional<char> shortOpt;
	const std::optional<std::string> longOpt;
	const bool requireArg;
	const std::function<void(std::string_view)> callOptArg;
	const std::optional<std::string> description;
	
	ArgOption(
		std::optional<char> shortOpt, std::optional<std::string> longOpt, bool requireArg,
		std::function<void(std::string_view)> callOptArg,
		std::optional<std::string> description
	);
};

class ArgParser {
  protected:
	std::string_view parserName;
	std::vector<ArgOption> options;
	std::function<void(std::string_view)> funcToHandleNonOptionArg;
  
  public:
	explicit ArgParser(std::string_view parserName = "ArgParser");
	
	void add_option(ArgOption argOption) {
		options.emplace_back(std::move(argOption));
	}
	
	void add_func_to_handle_non_option_arg(
		std::function<void(std::string_view)> funcToHandleNonOptionArg
	);
	
	int parse(int argc, char * argv[]);
	
	[[nodiscard]] std::string get_help() const;
};
}
