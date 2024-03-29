#pragma once

#include <type_traits>


namespace moe {

template<typename TRet, typename ... Ts>
TRet empty_func([[maybe_unused]] Ts && ... ts) {
	if constexpr (std::is_same<TRet, void>::value) {
		return;
	} else {
		return { };
	}
}

}
