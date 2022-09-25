//
// Created by 李远铄 on 2022/8/27.
//


#pragma once

#include <string>
#include <sstream>
#include <set>
#include <vector>


namespace moe {

//  you should implement operator << (std::ostream &, T)
template<typename ... Ts>
std::string concat_all(Ts && ... ts) {
	auto ss = std::stringstream();
	(ss<<...<<ts);
	return ss.str();
}

template<typename T>
bool enum_in(T val, std::set<T> enumSet) {
	static_assert(std::is_enum<T>().value);
	return enumSet.count(val);
}

std::vector<std::string>
split_string_on_char(
	const std::string & str, const std::vector<char> & delimiters = {' ', '\n'}
);

std::vector<std::string>
split_string_on_char(
	const std::string & str, std::string_view delimiters = " \n"
);

}