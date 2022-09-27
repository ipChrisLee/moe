#include "log.hpp"
#include "rt_check.hpp"

#include <memory>
#include <filesystem>


namespace moe {
std::unique_ptr<STDLog> STDLog::upStdLog = nullptr;

static std::unique_ptr<STDLog> stdLog;

STDLog & std_log() {
	moe_assert(STDLog::upStdLog, "You should register log first.");
	return *STDLog::upStdLog;
}

void register_std_log(
	std::string_view logFilePath, std::string_view sep, LogContext header
) {
	moe_assert(!STDLog::upStdLog, "You have registered a log. Check your code!");
	STDLog::upStdLog = std::unique_ptr<STDLog>(
		new STDLog(logFilePath, std::move(header), sep));
}

STDLog::STDLog(
	std::string_view logFilePath, LogContext header, std::string_view sep
) :
	header(std::move(header)), sep(sep), enabled(true) {
//	moe_assert(std::filesystem::exists(logFilePath), "File path does not exists!");
	ofs = std::ofstream(logFilePath);
}


LogContext::LogContext(std::vector<LogContextItem> items) :
	items(std::move(items)) {
}

LocalLog::LocalLog(
	std::string_view logFilePath, std::string_view sep, bool enable,
	const std::string & head
) : sep(sep), enabled(enable) {
	ofs = std::ofstream(logFilePath);
	if (!head.empty()) {
		ofs << head << std::endl;
	}
}
}

