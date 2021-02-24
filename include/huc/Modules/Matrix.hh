#ifndef HUC_MATRIX_MODULE_HH
#define HUC_MATRIX_MODULE_HH

#include <cstddef>
#include <vector>
#include <type_traits>
#include "huc/Ring/RingConcept.hh"

namespace huc{

namespace MatrixImpl{

}

template<Ring RE, size_t N>
class MatrixInitalizer{

};

class DenseMatrixBase{

};

// reference to a submatrix
template<Ring RE, size_t N>
class DenseMatrixRef : public DenseMatrixBase{
};


template<size_t N>
struct DenseMatrixSlice{
    DenseMatrixSlice() = default;
    DenseMatrixSlice(size_t offset, std::initializer_list<size_t> exts);
    DenseMatrixSlice(size_t offset, std::initializer_list<size_t> exts, std::initializer_list<size_t> strs);

    template<typename ... Dims>
    DenseMatrixSlice(Dims ...dims);

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

    template<typename ...Exts>
    explicit MatrixDense(Exts... exts); // specify from Extents

    MatrixDense(MatrixInitalizer<RE, N>);
    MatrixDense &operator=(MatrixInitalizer<RE, N>);

    // only initalize from Matrix_initalizer_lists
    template<Ring URE>
    MatrixDense(std::initializer_list<URE>) = delete;
    template<Ring URE>
    MatrixDense &operator=(std::initializer_list<URE>) = delete;

    RE *data() noexcept { return elems.data(); }
    const RE *data() const noexcept { return elems.data(); }

    // Subscripting and Slicing
    template<typename... Args>
    typename std::enable_if<MatrixImpl::Requesting_element<Args ...>, RE&>::type
    operator()(Args... args);

    template<typename... Args>
    typename std::enable_if<MatrixImpl::Requesting_element<Args ...>, const RE&>::type
    operator()(Args... args);

private:
    DenseMatrixSlice<N> desc; // gives extents in each the N dimensions
    std::vector<RE> elems;
};

template<Ring RE, size_t N>
template<typename ...Exts>
MatrixDense<RE, N>::MatrixDense(Exts ...exts): desc{exts...}, elems(desc.size) {}

template<Ring RE, size_t N>
MatrixDense<RE, N>::MatrixDense(MatrixInitalizer<RE, N> init){
    /*
    desc.extents = MatrixImpl::derive_extents(init);
    Matrix_impl::compute_strides(desc);
    elems.reserve(desc.size);
    Matrix_iml::insert_flat(init, elems);
    assert(elems.size() == desc.size);
    */
}

template<Ring RE, size_t N>
MatrixDense<RE, N> &MatrixDense<RE, N>::operator=(MatrixInitalizer<RE, N> init){
    /*
    desc.extents = MatrixImpl::derive_extents(init);
    Matrix_impl::compute_strides(desc);
    elems.reserve(desc.size);
    Matrix_iml::insert_flat(init, elems);
    assert(elems.size() == desc.size);
    */
    return *this;
}

template<Ring RE, size_t N>
template<Ring URE>
MatrixDense<RE, N>::MatrixDense(const DenseMatrixRef<URE,N> &x): desc{x.desc}, elems{x.begin(), x.end()}{
    static_assert(std::is_convertible<URE, RE>(), "Matrix Constructor: incompatible element types");
}

template<Ring RE, size_t N>
template<Ring URE>
MatrixDense<RE, N> &MatrixDense<RE, N>::operator=(const DenseMatrixRef<URE,N> &x){
    static_assert(std::is_convertible<URE, RE>(), "Matrix Constructor: incompatible element types");
    
    desc = x.desc;
    elems.assign(x.begin(), x.end());
    return *this;
}


}

#endif