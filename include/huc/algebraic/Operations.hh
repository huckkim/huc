#ifndef HUC_ALGEBRAIC_AXIOMS_HH
#define HUC_ALGEBRAIC_AXIOMS_HH

#include <concepts>

namespace huc{

template<typename N>
concept has_neg = requires(N a){
    {-a}->std::same_as<N>;
};

template<typename A>
concept has_add = requires(A a, A b){
    {a+b}->std::same_as<A>;
    a += b;
};

template<typename S>
concept has_sub = requires(S a, S b){
    {a-b}->std::same_as<S>;
    a -= b;
};

template<typename M>
concept has_mult = requires(M a, M b){
    {a*b}->std::same_as<M>;
    a *= b;
};

template<typename D>
concept has_div = requires(D a, D b){
    {a/b}->std::same_as<D>;
    a /= b;
};

// LOOK AT std::equality_comparible 
template<typename E>
concept has_eq = std::equality_comparable<E>;

// default constructable gives zero
template<typename Z>
concept has_zero = requires(Z a){
    Z();
    Z{};
};

// int constructor that atleast accepts 1
template<typename O>
concept has_one = requires(O a){
    O(1);
};

}

#endif 
