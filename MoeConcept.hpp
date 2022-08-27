//
// Created by 李远铄 on 2022/8/27.
//

#pragma once

#include <memory>
#include <stdexcept>
#include "STLPro.hpp"


namespace moe {

class Cloneable {
  protected:
	[[nodiscard]] virtual std::unique_ptr<Cloneable>
	clone_to_unique_ptr_to_impl() const = 0;
  
  public:
	[[nodiscard]] virtual std::unique_ptr<Cloneable>
	clone_to_unique_ptr() const final {
		std::unique_ptr<Cloneable> clonedUniquePtr = clone_to_unique_ptr_to_impl();
		Cloneable * clonedPtr = clonedUniquePtr.get();//NOLINT
		// For `-Wpotentially-evaluated-expression`.
		if (typeid(*clonedPtr) != typeid(*this)) {
			throw std::runtime_error(
				moe::concat_all(
					"Calling `clone_to_unique_ptr`method from type [",
					typeid(*clonedPtr).name(),
					"], which is different to the type of `this` [",
					typeid(*this).name(),
					"]. Check if you have implemented `clone_to_unique_ptr` method of type",
					typeid(*this).name(),
					" first."
				));
		}
		return clonedUniquePtr;
	}
	
	virtual ~Cloneable() = default;
};

class Cutable {
  protected:
	[[nodiscard]] virtual std::unique_ptr<Cutable> cut_to_unique_ptr_to_impl() = 0;
  
  public:
	virtual ~Cutable() = default;
	
	friend std::unique_ptr<Cutable> cut_to_unique_ptr(Cutable && o);
};

#define CUTABLE_DEFAULT_IMPLEMENT { return std::make_unique<std::remove_reference<decltype(*this)>::type>(std::move(*this));}
#define CLONEABLE_DEFAULT_IMPLEMENT { return std::make_unique<std::remove_const<std::remove_reference<decltype(*this)>::type>::type>(*this);}

}