# HUC (Huck's Ugly Cas)
A small project trying to implement a basic computer algebra system

Todo
- Integers (done (using gmp))
- Gaussian Integers
- Rationals (done)
- Polynomials 
  - Fast Fourier Transform for integer mult
  - (single var done (work on factoring for Integers?))
- Polynomials (multiple var)
- Matrices (multidim?) [taken from C++ Programming Language 4th ed]
  - determinant
  - characterisic polynomial / minimal polynomial
  - Decompositions
  - Spectral stuff
Probably take a while
- Algebraic functions/variables
- Transcendentals
- Differentiation?
- Integration (we can only dream)

## requirements
Requires g++-10, or access to C++20 concepts 

## Future

```c++
// Direct Sum of ring elements
template<RingElem R1, RingElem... RArgs>
class DirectSum{};

template<RingElem R, 1>
class CartesianProd{
  RingElem Tail;
};

template<RingElem R, int N>
class CartesianProd : CartesianProd<R, N-1>{
  RingElem Tail;
};
```

Lexer to convert
