//
// Created by 李远铄 on 2022/8/27.
//

#pragma once

#include <functional>
#include <vector>


namespace moe {

class ArgOption {
  public:
	char shortOpt;
	const char * longOpt;
	bool requireArg;
	std::function<void(const char *)> callOptArg;
	
	ArgOption(
		char shortOpt, const char * longOpt, bool requireArg,
		std::function<void(const char *)> callOptArg
	);
};

class ArgParser {
  protected:
	std::vector<ArgOption> options;
	std::function<void(const char *)> funcToHandleNonOptionArg;
  
  public:
	ArgParser();
	
	template<typename ... T>
	void emplace_option(T ... t) {
		options.template emplace_back(std::move(t)...);
	}
	
	void add_func_to_handle_non_option_arg(
		std::function<void(const char *)> funcToHandleNonOptionArg
	);
	
	int parse(int argc, char * argv[]);
};

}
