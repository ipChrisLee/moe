//
// Created by 李远铄 on 2022/8/27.
//


#pragma once

#include <string>
#include <sstream>
#include <set>
#include <vector>
#include "moe_typedef.hpp"
#include "rt_check.hpp"


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
	std::string_view str, const std::vector<char> & delimiters = {' ', '\n'}
);

std::vector<std::string>
split_string_on_char(
	std::string_view str, std::string_view delimiters = " \n"
);

//  get vec[begin..end] (INCLUDE)
//  for negative index idx, it will convert to sz+idx
template<typename T>
std::vector<T> sub_vector(std::vector<T> && vec, i32 begin, i32 end) {
	auto sz = i32(vec.size());
	if (begin < 0) { begin = begin + end; }
	if (end < 0) { end = sz + end; }
	moe_assert(begin < sz && end < sz, "Out of range.")
	auto res = std::vector<T>();
	for (auto i = begin; i <= end; ++i) {
		res.template emplace_back(std::move(vec[i]));
	}
	return res;
}

}