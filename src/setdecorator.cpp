#include "setdecorator.hpp"


namespace moe {

std::string_view decorator_to_str(Decorator decorator) {
	auto s = std::string_view();
	switch (decorator) {
		case c_black:
			s = "\u001b[30m";
			break;
		case c_red:
			s = "\u001b[31m";
			break;
		case c_green:
			s = "\u001b[32m";
			break;
		case c_yellow:
			s = "\u001b[33m";
			break;
		case c_blue:
			s = "\u001b[34m";
			break;
		case c_magenta:
			s = "\u001b[35m";
			break;
		case c_cyan:
			s = "\u001b[36m";
			break;
		case c_white:
			s = "\u001b[37m";
			break;
		case bg_black:
			s = "\u001b[40m";
			break;
		case bg_red:
			s = "\u001b[41m";
			break;
		case bg_green:
			s = "\u001b[42m";
			break;
		case bg_yellow:
			s = "\u001b[43m";
			break;
		case bg_blue:
			s = "\u001b[44m";
			break;
		case bg_magenta:
			s = "\u001b[45m";
			break;
		case bg_cyan:
			s = "\u001b[46m";
			break;
		case bg_white:
			s = "\u001b[47m";
			break;
		case d_bold:
			s = "\u001b[1m";
			break;
		case d_underline:
			s = "\u001b[4m";
			break;
		case d_reserved:
			s = "\u001b[7m";
			break;
		case reset:
			s = "\u001b[0m";
			break;
	}
	return s;
}

std::string_view reset_decorator() {
	return decorator_to_str(Decorator::reset);
}

}
