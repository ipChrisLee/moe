//
// Created by 李远铄 on 2022/8/27.
//

#include "ArgParser.hpp"
#include "FmtString.hpp"
#include "EmptyFunction.hpp"

#include <getopt.h>
#include <map>
#include <stdexcept>


namespace moe {

ArgOption::ArgOption(
	char shortOpt, const char * longOpt, bool requireArg,
	std::function<void(const char *)> callOptArg
) :
	shortOpt(shortOpt),
	longOpt(longOpt),
	requireArg(requireArg),
	callOptArg(std::move(callOptArg)) {
	if (!this->callOptArg) {
		throw std::logic_error(
			"`callOptArg` should not be null, you can use `EmptyFunction` instead."
		);
	}
}

inline std::tuple<int, int>
checkArgOptions(const std::vector<ArgOption> & options) {
	auto checked = true;
	auto longOptionCnt = std::map<std::string, int>();
	auto shortOptionCnt = std::map<char, int>();
	std::for_each(
		options.begin(), options.end(),
		[&longOptionCnt, &shortOptionCnt, &checked](const ArgOption & argOption) {
			if (argOption.longOpt) {
				++longOptionCnt[argOption.longOpt];
			}
			if (argOption.shortOpt) {
				++shortOptionCnt[argOption.shortOpt];
			}
			checked &= (argOption.longOpt || argOption.shortOpt);
		}
	);
	if (!checked) {
		throw std::invalid_argument(
			"For every `ArgOption`, there is either a `longOpt` or a `shortOpt`."
		);
	}
	std::for_each(
		longOptionCnt.begin(), longOptionCnt.end(),
		[&checked](const auto & kv) {
			checked &= (kv.second == 1);
		}
	);
	std::for_each(
		shortOptionCnt.begin(), shortOptionCnt.end(),
		[&checked](const auto & kv) {
			checked &= (kv.second == 1);
		}
	);
	if (!checked) {
		throw std::invalid_argument("Duplicate opt name!");
	}
	return {int(shortOptionCnt.size()), int(longOptionCnt.size())};
}

int ArgParser::parse(int argc, char * argv[]) {
	auto [shortOptionCnt, longOptionCnt] = checkArgOptions(options);
	auto up = std::unique_ptr<option[]>(new option[longOptionCnt + 1]);
	auto * pLongOptions = up.get();
	auto * p = pLongOptions;
	std::for_each(
		options.begin(), options.end(),
		[&p](const ArgOption & argOption) {
			if (argOption.longOpt) {
				p->name = argOption.longOpt;
				p->has_arg = argOption.requireArg ? required_argument : no_argument;
				p->flag = nullptr;
				p->val = 0;
				++p;
			}
		}
	);
	memset(p, 0, sizeof(option));
	auto shortOptionsStr = std::string("-:");
	std::for_each(
		options.begin(), options.end(),
		[&shortOptionsStr](const ArgOption & argOption) {
			if (argOption.shortOpt) {
				shortOptionsStr.push_back(argOption.shortOpt);
				if (argOption.requireArg) {
					shortOptionsStr.push_back(':');
				}
			}
		}
	);
	
	optind = 0;
	while (true) {
		int optionIndex = 0;
		int c = getopt_long(
			argc, argv, shortOptionsStr.c_str(), pLongOptions, &optionIndex
		);
		if (c == -1) {
			break;
		}
		switch (c) {
			case 0: {
				//  long option
				std::for_each(
					options.begin(), options.end(),
					[optionIndex, pLongOptions](const ArgOption & argOption) {
						if (argOption.longOpt == pLongOptions[optionIndex].name) {
							argOption.callOptArg(optarg);
						}
					}
				);
				break;
			}
			case 1: {
				//  non-option argv-element
				funcToHandleNonOptionArg(optarg);
				break;
			}
			case '?': {
				throw std::invalid_argument(
					format_str(
						"Unsupported opt [%c] caught.", char(optopt)
					)
				);
			}
			case ':': {
				throw std::invalid_argument(
					"Missing option argument of option."
				);
			}
			default:
				//  short option or error
				auto found = false;
				std::for_each(
					options.begin(), options.end(),
					[c, &found](const ArgOption & argOption) {
						if (argOption.shortOpt == c) {
							found = true;
							argOption.callOptArg(optarg);
						}
					}
				);
				if (found) {
					break;
				} else {
					throw std::logic_error(
						format_str("getopt returned character code 0%o", c)
					);
				}
		}
	}
	return 0;
}

void ArgParser::add_func_to_handle_non_option_arg(
	std::function<void(const char *)> paraFuncToHandleNonOptionArg
) {
	funcToHandleNonOptionArg = std::move(paraFuncToHandleNonOptionArg);
}

ArgParser::ArgParser() : funcToHandleNonOptionArg(empty_func<void, const char *>) {
}

}
