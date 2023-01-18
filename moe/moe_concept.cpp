#include "moe_concept.hpp"

namespace moe {

std::unique_ptr<Cutable> cut_to_unique_ptr(Cutable && o) {
	return o.cut_to_unique_ptr_to_impl();
}

}
