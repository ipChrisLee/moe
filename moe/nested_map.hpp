#pragma once
#include <map>
#include <unordered_map>
#include <memory>
#include <optional>


namespace moe {

namespace {
template<typename T, typename = std::void_t<>>
struct IsHashable : std::false_type {
};

template<typename T>
struct IsHashable<T, std::void_t<decltype(std::declval<std::hash<T>>()(std::declval<T>()))>> : std::true_type {
};
}

template<typename K, typename V>
class NestedMap {
  public:
	using Map = typename std::conditional<
		IsHashable<K>::value,
		std::unordered_map<K, V>,
		std::map<K, V>>::type;
  protected:
	Map map_;
	std::shared_ptr<NestedMap<K, V>> outer_;
  public:
	NestedMap() = default;
	
	explicit NestedMap(std::shared_ptr<NestedMap<K, V>> outer) : map_(), outer_(std::move(outer)) {}
	
	std::optional<std::reference_wrapper<V>> get_v(const K & k, bool recursive = true) {
		auto it = map_.find(k);
		if (it != map_.end()) {
			return it->second;
		} else if (recursive && outer_) {
			return (*outer_).get_v(k, recursive);
		} else {
			return std::nullopt;
		}
	}
	
	void insert(const K & k, const V & v) { map_.insert({k, v}); }
	
	bool erase(const K & k, bool recursive = true) {
		auto c = map_.erase(k);
		if (recursive && outer_) {
			return outer_->erase(k, recursive) || c;
		} else {
			return c;
		}
	}
	
	[[nodiscard]] bool exists(const K & k, bool recursive = true) const {
		return map_.count(k) != 0 || (recursive && outer_ && outer_->exists(k));
	}
	
	[[nodiscard]] bool is_root() const { return !outer_; }
};
}
