//  https://en.cppreference.com/w/cpp/io/manip/put_time

#include "time_pro.hpp"

#include <sstream>

#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>


namespace moe::now {

int day() {
	std::time_t
		t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm ltime{ };
	localtime_r(&t, &ltime);
	std::stringstream ss;
	ss << std::put_time(&ltime, "%d") << std::endl;
	auto res = i32(0);
	ss >> res;
	return res;
}

int hour() {
	std::time_t
		t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm ltime{ };
	localtime_r(&t, &ltime);
	std::stringstream ss;
	ss << std::put_time(&ltime, "%H") << std::endl;
	auto res = i32(0);
	ss >> res;
	return res;
}

int minute() {
	std::time_t
		t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm ltime{ };
	localtime_r(&t, &ltime);
	std::stringstream ss;
	ss << std::put_time(&ltime, "%M") << std::endl;
	auto res = i32(0);
	ss >> res;
	return res;
}

int second() {
	std::time_t
		t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm ltime{ };
	localtime_r(&t, &ltime);
	std::stringstream ss;
	ss << std::put_time(&ltime, "%S") << std::endl;
	auto res = i32(0);
	ss >> res;
	return res;
}

std::string formatTime() {
	std::time_t
		t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm ltime{ };
	localtime_r(&t, &ltime);
	std::stringstream ss;
	ss << std::put_time(&ltime, "%F %R") << std::endl;
	auto res = std::string();
	std::getline(ss, res);
	return res;
}

}

