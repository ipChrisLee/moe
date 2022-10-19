#pragma once

#include <string>
#include "moe_typedef.hpp"


namespace moe::now {

//  Day of month.
i32 day();

//  Hour of day, 24 split.
i32 hour();

//  Minute of hour, 60 split.
i32 minute();

//  Second of minute, 60 split.
i32 second();

//  24 hour time
std::string formatTime();

}



