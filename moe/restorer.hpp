#pragma once

#include <typeinfo>
#include <functional>
#include "moe_macro.hpp"


namespace moe {
template<
	typename T,
	class=typename std::enable_if<!std::is_lvalue_reference<T>::value>::type
>
class Restorer {
	T savedVal;
	T & ref;
  public:
	
	Restorer(T & _ref, T && newVal) :
		savedVal(std::move(_ref)), ref(_ref) {
		//  This is just for note.
		static_assert(
			!std::is_lvalue_reference<T>::value,
			"newVal should be rvalue. Remember to add `std::move`."
		);
		_ref = std::move(newVal);
	}
	
	~Restorer() {
		ref = std::move(savedVal);
	}
};

struct defer {
	std::function<void(void)> f;
	
	~defer() { f(); }

#define moe_defer(...) auto moe_cVar = moe::defer{[&](){__VA_ARGS__}};
};
}
/**
 * @brief A macro for auto-restore set.
 * @details The value of @c var will be restored automatically when leaving the scope of this macro used.
 * @ref https://stackoverflow.com/questions/207965/general-way-to-reset-a-member-variable-to-its-original-value-using-the-stack
 * @note The type of @c var should have move-constructor, move-assignment.
 * @note One line can only contain exact one macro.
 * @note Multiple usage of this macro in one scope will @b NOT cause fault.
 */
#define moe_r_set(var, newVal) moe::Restorer<decltype(var)> MOE_CONCAT(__restorer,__COUNTER__) ((var),(newVal))