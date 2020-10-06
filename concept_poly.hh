#ifndef CONCEPT_POLY_H
#define CONCEPT_POLY_H

#include <concepts>
#include <utility>
#include <cstddef>

namespace concept_testing{

// Enforces that Elements of a ring are closed under addition and multiplication
template<typename T>
concept RingElement = requires(T a, T b){
    {a+b}->std::same_as<T>;
    {a*b}->std::same_as<T>;
};

// Enforces existence of RingElements and zero/one elements
// Associativity, Commutivity, and existience of inverse/negative are left to
// programmer
template<typename R>
concept Ring = requires(R a){
    typename R::element;
    {a.zero()}->std::same_as<typename R::element>;
    {a.one()}->std::same_as<typename R::element>;
} && RingElement<typename R::element>;

// Ring without the multiplicative identity
template<typename R>
concept Rng = requires(R a, R b){
    typename R::element;
    {a.zero()}->std::same_as<typename R::element>;
} && RingElement<typename R::element>;

// Enfoces that Elements of a group are closed under addition
template<typename T>
concept GroupElement = requires(T a, T b){
    {a+b}->std::convertible_to<T>;
};

//Enforces existence of RingElements and zero element
// Associativity, Commutivity, and existience of negative are left to
// programmer
template<typename G>
concept Group = requires(G a, G b){
    typename G::element;
    {a.zero()}->std::same_as<typename G::element>;
    {a+b}->std::same_as<typename G::element>;
} && GroupElement<typename G::element>;

template<Ring R> class Polynomial{
    typedef typename R::element RElem;
    size_t degree;
    RElem* coeff;
public:
    Polynomial(size_t degree, RElem x):degree{degree},
        coeff{static_cast<RElem*>(operator new(sizeof(RElem)*(degree+1)))}{
        for(size_t i = 0; i < degree; ++i){
            new (coeff+i) RElem(x);
        }
    }
    Polynomial(std::initializer_list<RElem> init):degree{init.size()-1},
        coeff{static_cast<RElem*>(operator new(sizeof(RElem)*init.size()))}{
        size_t i = 0;
        for(auto x : init){
            new(coeff+(i++)) RElem(x);
        }
    }

    Polynomial(const Polynomial<R> &other):degree{other.degree}, coeff{static_cast<RElem*>(operator new(sizeof(RElem)*(degree+1)))}{
        for(size_t i = 0; i < degree; ++i){
            new (coeff+i) RElem(other.coeff[i]);
        }
    }

    Polynomial(Polynomial<R> &&other):degree{other.degree}, coeff{other.coeff}{
        other.coeff = nullptr;
    }

    Polynomial<R> &operator=(const Polynomial<R> &other){
        Polynomial<R> tmp = other;
        using std::swap;
        swap(degree, tmp.degree);
        swap(coeff, tmp.coeff);
        return *this;
    }

    Polynomial<R> &operator=(Polynomial<R> &&other){
        using std::swap;
        swap(degree, other.degree);
        swap(coeff, other.coeff);
        return *this;
    }

    void clear(){
        ++degree;
        for(; degree != 0; --degree){
            coeff[degree-1].~RElem();
        }
    }
    ~Polynomial(){
        clear();
        operator delete(coeff);
    }
};

}

#endif 