#ifndef MATRIX_H
#define MATRIX_H

#include "algebraic.hh"

template<typename FE>
class Matrix {
    size_t n;
    size_t m;
    FE** mat;
public:
    Matrix(size_t n):n{n}, m{n}, mat{new FE[n][m]} {}
    Matrix(size_t n, size_t m): n{n}, m{m}, mat{new FE[n][m]}{}
    ~Matrix(){ delete mat; }
};

#endif