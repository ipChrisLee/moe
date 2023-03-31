//	Ref: https://stackoverflow.com/a/64018031
#pragma once

template<typename...Ts>
struct overload : Ts ... {
	using Ts::operator()...;
};

template<typename...Ts>
overload(Ts...)->overload<Ts...>;