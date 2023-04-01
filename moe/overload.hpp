//	Ref: https://stackoverflow.com/a/64018031
#pragma once

namespace moe {
template<typename...Ts>
struct type_match : Ts ... {
	using Ts::operator()...;
};

template<typename...Ts>
type_match(Ts...)->type_match<Ts...>;
}