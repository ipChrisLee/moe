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
}