#ifndef HUC_INTEGER_MOD_RING_HH
#define HUC_INTEGER_MOD_RING_HH

#include "huc/Rings/Integer.hh"
#include <cstddef>

namespace huc{

template<const Integer &T>
class ZnZ{
    static constexpr const Integer &order = T;
    Integer n;
public:
    ZnZ(const Integer &&);
    ZnZ(Integer &&);

    ZnZ() = default;
    ZnZ(const ZnZ &) = default;
    ZnZ(ZnZ &&) = default;
    ZnZ &operator=(const ZnZ &) = default;
    ZnZ &operator=(ZnZ &&) = default;

    bool operator==(const ZnZ &);
    bool operator!=(const ZnZ &);

    ZnZ operator-();

    ZnZ &operator*(const ZnZ &);
    ZnZ &operator+(const ZnZ &);
    ZnZ &operator-(const ZnZ &);
};

template <const Integer &T>
ZnZ<T> operator*(const ZnZ<T> &, const ZnZ<T> &);

template <const Integer &T>
ZnZ<T> operator+(const ZnZ<T> &, const ZnZ<T> &);

template <const Integer &T>
ZnZ<T> operator-(const ZnZ<T> &, const ZnZ<T> &);

}

#endif