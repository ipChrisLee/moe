#include "stl_pro.hpp"

#include "moe_macro.hpp"
#include "debugger.hpp"


namespace moe {

std::vector<std::string>
split_string_on_char(std::string_view str, const std::vector<char> & delimiters) {
//	 pos_end, delim_len = delimiter.length();
	auto res = std::vector<std::string>();
	auto posStart = std::string_view::size_type(0);
	while (posStart < str.size()) {
		auto iFirstDel = str.size();
		for (auto ch: delimiters) {
			auto i = str.find(ch, posStart);
			if (i != std::string_view::npos) {
				iFirstDel = std::min(iFirstDel, i);
			}
		}
		if (iFirstDel > posStart) {
			res.emplace_back(str.substr(posStart, iFirstDel - posStart));
		}
		posStart = iFirstDel + 1;
	}
	return res;
}

std::vector<std::string>
split_string_on_char(
	std::string_view str, std::string_view delimiters
) {
	auto res = std::vector<std::string>();
	auto posStart = std::string_view::size_type(0);
	while (posStart < str.size()) {
		auto iFirstDel = str.size();
		for (auto ch: delimiters) {
			auto i = str.find(ch, posStart);
			if (i != std::string_view::npos) {
				iFirstDel = std::min(iFirstDel, i);
			}
		}
		if (iFirstDel > posStart) {
			res.emplace_back(str.substr(posStart, iFirstDel - posStart));
		}
		posStart = iFirstDel + 1;
	}
	return res;
}
}