#pragma once

#include <memory>
#include <string_view>
#include <fstream>


namespace moe {

class STDLog {
	friend void register_std_log(std::string_view logFilePath);
	
	friend STDLog & std_log();
  
  protected:
	static std::unique_ptr<STDLog> upStdLog;
  
  protected:
	std::ofstream ofs;
	
	explicit STDLog(std::string_view logFilePath);
  
  
  public:
	
};

void register_std_log(std::string_view logFilePath);

STDLog & std_log();


}
