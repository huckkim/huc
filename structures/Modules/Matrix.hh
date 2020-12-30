#ifndef __HUC_MATRIX_MODULE_HH__
#define __HUC_MATRIX_MODULE_HH__

#include <cstddef>
#include "alg_struct.hh"

namespace huc{

namespace MatrixImpl{

template<Ring RE, size_t N>
class MatrixRef{

};

template<size_t N>
struct MatrixSlice{
    size_t size;
    size_t start;
    std::array<size_t, N> extents;
    std::array<size_t, N> strides;

    MatrixSlice() = default;


};

}

class MismatchDimension{};

template<Ring RE, size_t N>
class MatrixDense{
    static constexpr size_t order = N;
    std::vector<RE> elems;
    MatrixImpl::MatrixSlice<N> desc;

    using iterator              = typename std::vector<RE>::iterator;
    using const_iterator        = typename std::vector<RE>::const_iterator;
public:
    MatrixDense() = default;
    ~MatrixDense() = default;
    MatrixDense(const MatrixDense &) = default;
    MatrixDense &operator=(const MatrixDense &) = default;
    MatrixDense(MatrixDense &&) = default;
    MatrixDense &operator=(MatrixDense &&) = default;
    
    template<typename ...Exts>
    MatrixDense(Exts... exts): desc{exts...}, elems(desc.size()) {}

/*
    MatrixDense(MatrixDense_initalizer<RE, N>);
    MatrixDense &operator=(MatrixDense_initalizer<RE, N>);
    /**/

/*
    template<typename _RE>
    MatrixDense(std::initalizer_list<_RE>) = delete;
    template<typename _RE>
    MatrixDense &operator=(std::initalizer_list<_RE>) = delete;
    /**/
};


}

#endif