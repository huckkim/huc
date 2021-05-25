#ifndef HUC_CARTESIAN_PRODUCT_MODULE_HH
#define HUC_CARTESIAN_PRODUCT_MODULE_HH

#include "huc/algebraic/Structures.hh"
#include <tuple>
#include <iostream>

namespace huc{

template<Ring ...RES>
class CartesianProduct{
public:
    std::tuple<RES...> cp;
    CartesianProduct() = default;
    ~CartesianProduct() = default;
    CartesianProduct(const CartesianProduct &) = default;
    CartesianProduct &operator=(const CartesianProduct &) = default;
    CartesianProduct(CartesianProduct &&) = default;
    CartesianProduct &operator=(CartesianProduct &&) = default;

    size_t size() const { return std::tuple_size<decltype(cp)>::value; }
    size_t dimension() const { return std::tuple_size<decltype(cp)>::value; }

    template<Ring ..._RES>
    friend constexpr std::ostream &operator<<(std::ostream &os, const CartesianProduct<_RES...> &cp);
};

}

#endif
