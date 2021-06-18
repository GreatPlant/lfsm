#ifndef STATE_HPP_
#define STATE_HPP_
#include <string>

#include "typelist.hpp"
#include "names.hpp"

template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }

    char value[N];
};

struct StateBase{};

template <unsigned int N, typename Action = void>
struct State : StateBase {

	static constexpr unsigned int idx = N;
	using action_t = Action;
};

#endif
