# HUC (Huck's Ugly Cas)
A small project trying to implement a ~~basic computer algebra system~~ mathematical template library(mtl)? + mtl::algorithms?

Todo
- Polynomial
  - Fast Fourier Transform for integer mult (http://www.cs.toronto.edu/~denisp/csc373/docs/tutorial3-adv-writeup.pdf)
  - (single var done (work on factoring for Integers?))
- Integers (done (using gmp))
- Gaussian Integers
- Rationals (done)
- Matrices (multidim?) [taken from C++ Programming Language 4th ed]
  - determinant
  - characterisic polynomial / minimal polynomial
  - Decompositions
  - Spectral stuff
- functions / functors

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

# MTL
Probably make most objects templated containers with operations attatched to them
- ```Polynomials<RE>```
- ```Matrix<RE, m, n>```
and then a templated algorithms library for things like
- ```auto huc::gcd<EDE>(auto a, auto b)```
