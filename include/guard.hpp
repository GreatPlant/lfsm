#ifndef GUARD_HPP_
#define GUARD_HPP_

enum class Guard : unsigned int {
	NO_GUARD,
	NO_LED
};


struct GuardEqual{
	constexpr bool operator() (const Guard& lhs, const Guard& rhs){
		return lhs == rhs;
	}
};


#endif
