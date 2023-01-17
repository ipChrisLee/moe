//
// Created by 李远铄 on 2022/8/27.
//

#pragma once

#include <string>


namespace moe {

// ref: https://stackoverflow.com/a/26221725/17924585
template<typename ... Args>
std::string format_str(const std::string & format, Args ... args) {
	int sizeS = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
	if (sizeS <= 0) { throw std::runtime_error("Error during formatting."); }
	auto size = static_cast<size_t>( sizeS );
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return {buf.get(), buf.get() + size - 1};
}
}