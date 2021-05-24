#ifndef HUC_MISC_UTILITY_HH
#define HUC_MISC_UTILITY_HH

#include <iterator>

namespace huc::utility{

// Applies a binary function to elements from two different containers and outputs the result to out
template<typename InputIt1, typename InputIt2, typename OutputIt, typename BinaryOp>
void for_each_binary(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt out, BinaryOp binary_op){
    while(first1 != last1){
        *out++ = binary_op(*first1++, *first2++);
    }
}

// range version?

// Returns true if the two containers are equal with respect to their elements
template<typename InputIt1, typename InputIt2>
bool container_equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2){
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

}


#endif
