//
// Created by 李远铄 on 2022/8/27.
//


#pragma once

#include <string>
#include <sstream>
#include <set>


namespace moe {

//  you should implement operator << (std::ostream &, T)
template<typename ... Ts>
std::string concat_all(Ts && ... ts) {
	auto ss = std::stringstream();
	((ss << ts), ...);
	auto res = std::string();
	ss >> res;
	return res;
}

template<typename T>
bool enum_in(T val, std::set<T> enumSet) {
	static_assert(std::is_enum<T>().value);
	return enumSet.count(val);
}

}