#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <functional>
#include <cstdint>

#include "names.hpp"

struct EventBase{};

template <unsigned int N>
struct Event : EventBase {
	static constexpr unsigned int idx = N;
};


struct EventEqual{
	template <unsigned int L, unsigned int R>
    constexpr bool operator() (const Event<L>& lhs, const Event<R>& rhs) const {
		return (lhs.idx == rhs.idx);
	}
};

template <unsigned int N>
struct EventHash {
    std::size_t operator()(const Event<N>& k) const
	{

		return std::hash<unsigned int>{}(k.idx);
	}
};

#endif
