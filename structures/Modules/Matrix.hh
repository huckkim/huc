#ifndef __HUC_MATRIX_MODULE_HH__
#define __HUC_MATRIX_MODULE_HH__

#include <cstddef>
#include <vector>
#include "alg_struct.hh"

namespace huc{

template<Ring RE, size_t N>
class Matrix_initalizer_list{

};

class DenseMatrixBase{

};

// reference to a submatrix
template<Ring RE, size_t N>
class DenseMatrixRef : public DenseMatrixBase{

};


template<size_t N>
struct DenseMatrixSlice{
    size_t size;
    size_t start;
    std::array<size_t, N> extents;
    std::array<size_t, N> strides;

    DenseMatrixSlice() = default;
};

class MismatchDimension{};

template<Ring RE, size_t N>
class MatrixDense : public DenseMatrixBase{
    static constexpr size_t order = N;
    using value_type            = RE;
    using iterator              = typename std::vector<RE>::iterator;
    using const_iterator        = typename std::vector<RE>::const_iterator;
public:
    MatrixDense() = default;
    ~MatrixDense() = default;
    MatrixDense(const MatrixDense &) = default;
    MatrixDense &operator=(const MatrixDense &) = default;
    MatrixDense(MatrixDense &&) = default;
    MatrixDense &operator=(MatrixDense &&) = default;

    template<Ring URE>
    MatrixDense(const DenseMatrixRef<URE, N> &); // copy from MatrixRef
    template<Ring URE>
    MatrixDense &operator=(const DenseMatrixRef<URE, N> &);

    /*
    template<Ring URE>
    MatrixDense(DenseMatrixRef<URE, N> &&); // move from MatrixRef
    template<Ring URE>
    MatrixDense &operator=(DenseMatrixRef<URE, N> &&);
    */

    template<typename ...Exts>
    explicit MatrixDense(Exts... exts); // specify from Extents

    MatrixDense(Matrix_initalizer_list<RE, N>);
    MatrixDense &operator=(Matrix_initalizer_list<RE, N>);

    // only initalize from Matrix_initalizer_lists
    template<Ring URE>
    MatrixDense(std::initalizer_list<RE>) = delete;
    template<Ring URE>
    MatrixDense &operator=(std::initalizer_list<RE>) = delete;

    RE *data() noexcept { return elems.data(); }
    const RE *data() const noexcept { return elems.data(); }
private:
    DenseMatrixSlice<N> desc; // gives extents in each the N dimensions
    std::vector<RE> elems;
};

}

#endif