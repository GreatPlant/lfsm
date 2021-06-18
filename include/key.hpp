#ifndef KEY_HPP_
#define KEY_HPP_

#include <functional>
#include <utility>

struct Key {

	unsigned int state_idx = 0;
	unsigned int event_idx = 0;
};


struct KeyEqual {
	constexpr bool operator() (const Key& lhs, const Key& rhs) const{
		return (lhs.state_idx == rhs.state_idx) &&
				(lhs.event_idx == rhs.event_idx);
	}
};

struct KeyHash {
	std::size_t operator()(const Key& k) const
	{
		std::size_t h1 = std::hash<unsigned int>{}(k.state_idx);
		std::size_t h2 = std::hash<unsigned int>{}(k.event_idx);

		return h1 ^ (h2 << 1);
	}
};


#endif
