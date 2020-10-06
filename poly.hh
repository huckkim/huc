#ifndef POLY_H

#define POLY_H

#include "algebraic.hh"
#include <iostream>
#include <cstddef>
#include <utility>
#include <initializer_list>

namespace schoof{

/**
 * @brief Polynomial class that takes coefficients from some generated by some 
 * ring R. Supports basic functions such as coefficient/degree access, multiplication,
 * addition, and evaluation at a RingElement.
 * 
 * @tparam Some Ring R adhering to the Ring concept, see algebraic.hh 
 */
template<Ring R>
class Polynomial{
    typedef typename R::element RElem;
    size_t degree;
    RElem* coeff;
public:
    /**
     * @brief Initalizes polynomial with degree and each coefficent being x
     * @param degree degree of polynomial
     * @param x value of each coefficients, default is default constructor
     */
    Polynomial(size_t degree, RElem x = RElem{}):degree{degree},
        coeff{static_cast<RElem*>(operator new(sizeof(RElem)*(degree+1)))}{
        for(size_t i = 0; i <= degree; ++i){
            new (coeff+i) RElem(x);
        }
    }
    /**
     * @brief Initalizes a polynomial with coefficents from an initalizer list
     * @param init initalizer list of RElem's for coefficients
     */
    Polynomial(std::initializer_list<RElem> init):degree{init.size()-1},
        coeff{static_cast<RElem*>(operator new(sizeof(RElem)*init.size()))}{
        size_t i = 0;
        for(auto x : init){
            new(coeff+(i++)) RElem(x);
        }
    }
    /**
     * @brief Copy constructor for Polynomial
     * @param other Polynomial to be copied from
     */
    Polynomial(const Polynomial<R> &other):degree{other.degree}, coeff{static_cast<RElem*>(operator new(sizeof(RElem)*(degree+1)))}{
        for(size_t i = 0; i < degree; ++i){
            new (coeff+i) RElem(other.coeff[i]);
        }
    }
    /**
     * @brief Move constructor for Polynomial
     * @param other Polynomial to be moved from
     */
    Polynomial(Polynomial<R> &&other):degree{other.degree}, coeff{other.coeff}{
        other.coeff = nullptr;
    }
    /**
     * @brief Copy assignment for Polynomial
     * @param other Polynomial to copy from
     * @return pointer to this
     */
    Polynomial<R> &operator=(const Polynomial<R> &other){
        Polynomial<R> tmp = other;
        using std::swap;
        swap(degree, tmp.degree);
        swap(coeff, tmp.coeff);
        return *this;
    }
    /**
     * @brief Move assignment for Polynomial
     * @param other Polynomial to move from
     * @return pointer to this
     */
    Polynomial<R> &operator=(Polynomial<R> &&other){
        using std::swap;
        swap(degree, other.degree);
        swap(coeff, other.coeff);
        return *this;
    }
    /**
     * @brief Deconstructs each coefficient, preparing to deconstruct Polynomial
     * @return (void)
     */
    void clear(){
        ++degree;
        for(; degree != 0; --degree){
            coeff[degree-1].~RElem();
        }
    }
    /**
     * @brief Deconstructs Polynomial
     */
    ~Polynomial(){
        clear();
        operator delete(coeff);
    }

    /** Member functions */

    /**
     * @brief Return coefficient for x of exponent i
     * @param i coeffcient of x with exponent i
     * @return RElem
     */
    RElem &operator[](size_t i){ return coeff[i]; }
    /**
     * @overload
     */
    const RElem &operator[](size_t i) const { return coeff[i]; }
    /**
     * @brief Evaluates the Polynomial at value x
     * @param x value to evaluate at
     * @return RElem
     */
    RElem operator()(const RElem &x){
        RElem sum = RElem{};
        for(size_t i = 0; i <= degree; ++i){
            if(i == 0) sum += coeff[i];
            else if(i == 1) sum += coeff[i] * x;
            else{
                RElem nx = x;
                for(size_t j = 2; j <= i; ++j){
                    nx *= x;
                }
                sum += coeff[i] * nx;
            }
        }
        return sum;
    }
    /**
     * @brief Returns degree of Polynomial
     * @return size_t
     */
    size_t getDegree(){ return degree; }
    /**
     * @overload
     */
    const size_t getDegree() const { return degree; }
};

/**
 * @brief Returns a new Polynomial that is the sum of the two polynomials
 * @tparam R must satisfy the Ring concept
 * @param p1 A Polynomial over a ring R
 * @param p2 A Polynomial over a ring R
 * @return Polynomial<R>
 */
template <Ring R>
Polynomial<R> operator+(const Polynomial<R> &p1, const Polynomial<R> &p2){
    size_t mx;
    size_t p1mx = p1.getDegree();
    size_t p2mx = p2.getDegree();
    if(p1mx > p2mx) mx = p1mx;
    else mx = p2mx;
    Polynomial<R> p(mx);
    for(size_t i = 0; i <= mx; ++i){
        if(mx > p1mx) p[i] = p2[i];
        else if(mx > p2mx) p[i] = p1[i];
        else p[i] = p1[i] + p2[i];
    }
    return p;
} 

/**
 * @brief Returns a new Polynomial that is the product of the two polynomials
 * @tparam R must satisfy the Ring concept
 * @param p1 A Polynomial over a ring R
 * @param p2 A Polynomial over a ring R
 * @return Polynomial<R>
 */
template <Ring R>
Polynomial<R> operator*(const Polynomial<R> &p1, const Polynomial<R> &p2){
    typedef typename R::element RElem;
    Polynomial<R> p(p1.getDegree() + p2.getDegree());
    for(size_t k = 0; k <= p1.getDegree() + p2.getDegree(); ++k){
        RElem new_coeff{};
        RElem f{};
        RElem g{};
        RElem sum{};
        for(size_t i = 0; i <= k; ++i){
            new_coeff = RElem{};
            if(i <= p1.getDegree()) f = p1[i];
            else f = RElem{};
            if((k-i) <= p2.getDegree()) g = p2[k-i];
            else g = RElem{};
            new_coeff = f * g;
            sum += new_coeff;
        }
        p[k] = sum;
    }
    return p;
}

/**
 * @brief Output operation overloading
 * @tparam R must satisfy the Ring concept
 * @param out Ouput stream
 * @param p Polynomial over R
 * @return ostream
 */
template <Ring R>
std::ostream &operator<<(std::ostream &out, const Polynomial<R> &p){
    for(size_t i = 0; i <= p.getDegree(); ++i){
        out<<"("<<p[i]<<"x^"<<i<<")";
    }
    return out;
}

} // namespace schoof
#endif