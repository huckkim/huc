#ifndef HUC_MISC_UTILITY_HH
#define HUC_MISC_UTILITY_HH

#include <ranges>
#include <iterator>
#include <cassert>

namespace huc::utility{

// Applies a binary function to elements from two different containers and outputs the result to out
template<typename InputIt1, typename InputIt2, typename OutputIt, typename BinaryOp>
constexpr void for_each_binary(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
                               OutputIt out, BinaryOp binary_op){
    auto d1 = std::distance(first1, last1);
    auto d2 = std::distance(first2, last2);
    assert(d1 == d2);
    while(first1 != last1){
        *out++ = binary_op(*first1++, *first2++);
    }
}

// range version?

namespace ranges{

// WIP
struct for_each_binary_fn{
    template<std::input_iterator I1, std::sentinel_for<I1> S1,
             std::input_iterator I2, std::sentinel_for<I2> S2,
             typename O1, typename BinaryOp>
    constexpr void operator()(I1 first1, S1 last1, I2 first2, S2 last2, O1 out, BinaryOp binary_op) const{
        auto d1 = std::distance(first1, last1);
        auto d2 = std::distance(first2, last2);
        assert(d1 == d2);
        while(first1 != last1){
            *out++ = binary_op(*first1++, *first2++);
        }
    }
    template<std::ranges::input_range R1, std::ranges::input_range R2, 
             typename O1, typename BinaryOp>
    constexpr void operator()(R1 &&r1, R2 &&r2, O1 out, BinaryOp binary_op) const {
        (*this)(std::ranges::begin(r1), std::ranges::end(r1),
                std::ranges::begin(r2), std::ranges::end(r2), 
                out, binary_op);
    }
};

inline constexpr for_each_binary_fn for_each_binary;

}

// Returns true if the two containers are equal with respect to their elements
template<std::input_iterator I1, std::input_iterator I2>
constexpr bool container_equal(I1 first1, I1 last1, I2 first2, I2 last2){
    auto d1 = std::distance(first1, last1);
    auto d2 = std::distance(first2, last2);
    if( d1 != d2)
        return false;
    while(first1 != last1){
        if(*first1++ != *first2++)
            return false;
    }
    return true;
}

template<std::input_iterator I1, std::input_iterator I2, typename BinaryOp>
constexpr bool container_equal(I1 first1, I1 last1, I2 first2, I2 last2, BinaryOp binary_op){
    auto d1 = std::distance(first1, last1);
    auto d2 = std::distance(first2, last2);
    if( d1 != d2)
        return false;
    while(first1 != last1){
        if(!binary_op(*first1++, *first2++))
            return false;
    }
    return true;
}

namespace ranges{

// Ranges version
struct container_equal_fn{
    template<std::input_iterator I1, std::sentinel_for<I1> S1,
             std::input_iterator I2, std::sentinel_for<I2> S2>
    constexpr bool operator()(I1 first1, S1 last1, I2 first2, S2 last2) const {
        auto d1 = std::distance(first1, last1);
        auto d2 = std::distance(first2, last2);
        if( d1 != d2)
            return false;
        while(first1 != last1){
            if(*first1++ != *first2++) return false;
        }
        return true;
    }
    template<std::ranges::input_range R1, std::ranges::input_range R2>
    constexpr bool operator()(R1 &&r1, R2 &&r2) const {
        return (*this)(std::ranges::begin(r1), std::ranges::end(r1),
                       std::ranges::begin(r2), std::ranges::end(r2));
    }

    template<std::input_iterator I1, std::sentinel_for<I1> S1,
             std::input_iterator I2, std::sentinel_for<I2> S2,
             typename BinaryOp>
    constexpr bool operator()(I1 first1, S1 last1, I2 first2, S2 last2, BinaryOp binary_op) const {
        auto d1 = std::distance(first1, last1);
        auto d2 = std::distance(first2, last2);
        if( d1 != d2)
            return false;
        while(first1 != last1){
            if(!binary_op(*first1++, *first2++)) return false;
        }
        return true;
    }
    template<std::ranges::input_range R1, std::ranges::input_range R2, typename BinaryOp>
    constexpr bool operator()(R1 &&r1, R2 &&r2, BinaryOp binary_op) const {
        return (*this)(std::ranges::begin(r1), std::ranges::end(r1),
                       std::ranges::begin(r2), std::ranges::end(r2),
                       binary_op);
    }
};

inline constexpr container_equal_fn container_equal;

}

}


#endif
