#ifndef CONCEPT_POLY_H
#define CONCEPT_POLY_H

#include <iostream>
#include <concepts>
#include <utility>
#include <cstddef>

namespace concept_testing{

// Enforces that Elements of a ring are closed under addition and multiplication
template<typename T>
concept RingElement = requires(T a, T b){
    {a+b}->std::same_as<T>;
    {a*b}->std::same_as<T>;
    a+=b;
    a*=b;
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
    Polynomial(size_t degree, RElem x = RElem{}):degree{degree},
        coeff{static_cast<RElem*>(operator new(sizeof(RElem)*(degree+1)))}{
        for(size_t i = 0; i <= degree; ++i){
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

    RElem &operator[](size_t i){ return coeff[i]; }
    const RElem &operator[](size_t i) const { return coeff[i]; }

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

    size_t getDegree(){ return degree; }
    const size_t getDegree() const { return degree; }
};

template <Ring R> std::ostream &operator<<(std::ostream &out, const Polynomial<R> &p){
    for(size_t i = 0; i <= p.getDegree(); ++i){
        out<<"("<<p[i]<<"x^"<<i<<")";
    }
    return out;
}

template <Ring R> Polynomial<R> operator+(const Polynomial<R> &p1, const Polynomial<R> &p2){
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

template <Ring R> Polynomial<R> operator*(const Polynomial<R> &p1, const Polynomial<R> &p2){
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
}

#endif 