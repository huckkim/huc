#ifndef HUC_MATRIX_MODULE_HH
#define HUC_MATRIX_MODULE_HH

#include <cstddef>
#include <vector>
#include <array>
#include <type_traits>
#include "huc/Rings/RingConcept.hh"

namespace huc{

template<size_t N>
struct Matrix_slice {
    Matrix_slice() = default;

    Matrix_slice(size_t offset, std::initializer_list<size_t> exts); // starting offset and extents
    Matrix_slice(size_t offset, std::initializer_list<size_t> exts, std::initializer_list<size_t> strs); // and strides

    template<typename... Dims> // N extents
    Matrix_slice(Dims... dims);

    template<typename... Dims,
             typename = std::enable_if_t<std::is_convertible_v<Dims, size_t>, ...>>
    size_t operator()(Dims... dims) const;


    size_t size;
    size_t start;

    std::array<size_t, N> extents;
    std::array<size_t, N> strides; 
};

template<Ring RE, size_t N>
class MatrixDense{
    Matrix_slice<N> desc;
    std::vector<RE> elems;
public:
    static constexpr size_t order = N;

    using value_type                        = typename std::vector<RE>::value_type;
    using iterator                          = typename std::vector<RE>::iterator;
    using const_iterator                    = typename std::vector<RE>::const_iterator;
    
    using reverse_iterator                  = typename std::vector<RE>::reverse_iterator;
    using const_reverse_iterator            = typename std::vector<RE>::const_reverse_iterator;

    MatrixDense() = default;
    // Copy
    MatrixDense (const MatrixDense &) = default;
    MatrixDense &operator=(const MatrixDense &) = default;
    // Move
    MatrixDense (MatrixDense &&) = default;
    MatrixDense &operator=(MatrixDense &&) = default;
    ~MatrixDense() = default;

    template<typename... Exts>
    explicit MatrixDense(Exts ...exts);

    template<Ring _RE>
    MatrixDense(std::initializer_list<RE>) = delete;

    template<Ring _RE>
    MatrixDense &operator=(std::initializer_list<RE>) = delete;

    // "Flat" data access
    RE *data() { return elems.data(); }
    const RE *data() const { return elems.data(); }
};

template<Ring RE, size_t N>
    template<typename... Exts>
    MatrixDense<RE, N>::MatrixDense(Exts... exts):
        desc{exts...}, // send the variadic arguments to desc
        elems(desc.size)
    {}

}

#endif