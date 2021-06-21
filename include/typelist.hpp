#ifndef TYPELIST_HPP_
#define TYPELIST_HPP_

#include <type_traits>
#include <utility> //for std::index_sequence
#include <cstdint>
#include <algorithm>//for std::find

template<class A, class B>
struct is_same : std::false_type{};

template<class T>
struct is_same<T, T> : std::true_type{};



template <class T>
struct just_type{
	using type = T;
};


template <class... Ts>
struct type_pack{};

using empty_pack = type_pack<>;


template <class... Ts>
constexpr std::size_t size(type_pack<Ts...>) {
	return sizeof...(Ts);
}

template <class... Ts>
constexpr bool empty(type_pack<Ts...> tp) {
	return size(tp) == 0;
}


template <class T, class... Ts>
constexpr just_type<T> head(type_pack<T, Ts...>) {
	return {};
}


template <class T, class... Ts>
constexpr type_pack<Ts...> tail(type_pack<T, Ts...>) {
	return {};
}


template <class T, class U>
constexpr bool operator==(just_type<T>, just_type<U>) {
	return false;
}

template <class T>
constexpr bool operator==(just_type<T>, just_type<T>){
	return true;
}

template <class T, class U>
constexpr bool operator!=(just_type<T>, just_type<U>) {
	return true;
}

template <class T>
constexpr bool operator!=(just_type<T>, just_type<T>) {
	return false;
}

template <class T, class U>
constexpr auto operator+(just_type<T>, just_type<U>) {
	return type_pack<T, U>{};
}


template <class... Ts, class... Us>
constexpr bool operator==(type_pack<Ts...>, type_pack<Us...>) {
	return false;
}

template <class... Ts>
constexpr bool operator==(type_pack<Ts...>, type_pack<Ts...>) {
	return true;
}


template <class... Ts, class... Us>
constexpr bool operator!=(type_pack<Ts...>, type_pack<Us...>) {
	return true;
}

template <class... Ts>
constexpr bool operator!=(type_pack<Ts...>, type_pack<Ts...>) {
	return false;
}

template <class... Ts, class U>
constexpr auto operator+(type_pack<Ts...>, just_type<U>) {
	return type_pack<Ts..., U>{};
}

template <class... Ts, class... Us>
constexpr auto operator+(type_pack<Ts...>, type_pack<Us...>) {
	return type_pack<Ts..., Us...>{};
}


template <class... Ts, class T>
constexpr type_pack<T, Ts...> push_front(type_pack<Ts...>, just_type<T>) {
	return {};
}


template <class T, class... Ts>
constexpr type_pack<Ts...> pop_front(type_pack<T, Ts...>) {
	return {};
}

template <class T, class... Ts>
constexpr type_pack<Ts..., T> push_back(type_pack<Ts...>, just_type<T>) {
	return {};
}


template <class T, class... Ts>
constexpr bool contains(type_pack<Ts...>, just_type<T>) {
	return 	(... || std::is_same_v<T, Ts>);
}

template <class T, class... Ts>
constexpr std::size_t find(type_pack<Ts...> tp, just_type<T> t) {
    bool bs[] = { std::is_same_v<t, Ts>...};
    return std::find(bs, bs+size(tp), true) - bs;
}

#endif
