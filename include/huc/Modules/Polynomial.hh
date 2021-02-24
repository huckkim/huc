#ifndef HUC_POLYNOMIAL_MODULE_HH
#define HUC_POLYNOMIAL_MODULE_HH

#include <vector>
#include "huc/Rings/RingConcept.hh"

namespace huc{

template<Ring RE>
class PolynomialUnivariateSparse{

};

template<Ring RE>
class PolynomialUnivariateDense{
    std::vector<RE> p;

    using value_type                    = typename std::vector<RE>::value_type;
    using iterator                      = typename std::vector<RE>::iterator;
    using const_iterator                = typename std::vector<RE>::const_iterator;
    
    using reverse_iterator              = typename std::vector<RE>::reverse_iterator;
    using const_reverse_iterator        = typename std::vector<RE>::const_reverse_iterator;
public:
    PolynomialUnivariateDense(std::initializer_list<RE> lst){
        for(auto a : lst){
            p.push_back(a);
        }
    }

    PolynomialUnivariateDense() = default;
    PolynomialUnivariateDense(const PolynomialUnivariateDense &) = default;
    PolynomialUnivariateDense &operator=(const PolynomialUnivariateDense &) = default;
    PolynomialUnivariateDense(PolynomialUnivariateDense &&) = default;
    PolynomialUnivariateDense &operator=(PolynomialUnivariateDense &&) = default;
    ~PolynomialUnivariateDense() = default;

    constexpr RE &operator[](size_t i){ return p[i]; }
    constexpr const RE &operator[](size_t i) const { return p[i]; }

    constexpr iterator begin() noexcept { return p.begin(); }
    constexpr iterator end() noexcept { return p.end(); }

    constexpr const_iterator begin() const noexcept { return p.begin(); }
    constexpr const_iterator end() const noexcept { return p.end(); }

    constexpr reverse_iterator rbegin() noexcept { return p.rbegin(); }
    constexpr reverse_iterator rend() noexcept { return p.rend(); }

    constexpr const_reverse_iterator rbegin() const noexcept { return p.rbegin(); }
    constexpr const_reverse_iterator rend() const noexcept { return p.rend(); }

    PolynomialUnivariateDense operator-(){
        std::vector<RE> tmp;
        for(auto &c : p){
            tmp.push_back(-c);
        }
        return tmp;
    }
    PolynomialUnivariateDense &operator-=(const PolynomialUnivariateDense &other){
        size_t deg = (size() > other.size()) ? size() : other.size();
        for(size_t i = 0; i < deg; ++i){
            if(i < size() && i < other.size()){
                p[i] -= other[i];        
            }
            else if(i >= size()){
                p.push_back(-other[i]);
            }
        }
        // remove leading zeros
        while(rbegin() != rend() && *rbegin() == 0){
            p.pop_back();
        }
        return *this;
    }
    PolynomialUnivariateDense &operator+=(const PolynomialUnivariateDense &other){
        size_t deg = (size() > other.size()) ? size() : other.size();
        for(size_t i = 0; i < deg; ++i){
            if(i < size() && i < other.size()){
                p[i] += other[i];        
            }
            else if(i >= size()){
                p.push_back(other[i]);
            }
        }
        // remove leading zeros
        while(rbegin() != rend() && *rbegin() == 0){
            p.pop_back();
        }
        return *this;
    }

    PolynomialUnivariateDense &operator*=(const RE &s){
        for(auto &c : p){
            p *= s;
        }
        return *this;
    }

    // Horners method
    RE operator()(const RE &x){
        auto a_n = rbegin();
        RE b_n = *a_n;
        ++a_n;
        while(a_n != rend()){
            b_n = *a_n + b_n*x;
            ++a_n;
        }
        return b_n;
    }

    // TODO: Technically an Algebra as well as a module
    PolynomialUnivariateDense &operator*=(const PolynomialUnivariateDense &other){

    }

    constexpr bool operator==(const PolynomialUnivariateDense &other){ return p == other.p; }
    constexpr bool operator!=(const PolynomialUnivariateDense &other){ return p != other.p; }

    constexpr size_t size() const noexcept{ return p.size(); }
    constexpr size_t degree() const noexcept{ return p.size() ? p.size()-1 : p.size(); }

    template<Ring _RE>
    friend PolynomialUnivariateDense<_RE> operator+(const PolynomialUnivariateDense<_RE> &a, const PolynomialUnivariateDense<_RE> &b);
    template<Ring _RE>
    friend PolynomialUnivariateDense<_RE> operator-(const PolynomialUnivariateDense<_RE> &a, const PolynomialUnivariateDense<_RE> &b);
    template<Ring _RE>
    friend PolynomialUnivariateDense<_RE> operator*(const PolynomialUnivariateDense<_RE> &a, const _RE &s);
    template<Ring _RE>
    friend PolynomialUnivariateDense<_RE> operator*(const _RE &s, const PolynomialUnivariateDense<_RE> &a);
    template<Ring _RE>
    friend PolynomialUnivariateDense<_RE> operator*(const PolynomialUnivariateDense<_RE> &s, const PolynomialUnivariateDense<_RE> &a);
    template<Ring _RE>
    friend std::ostream &operator<<(std::ostream &os, const PolynomialUnivariateDense<_RE> &a);
};

template<Ring RE>
PolynomialUnivariateDense<RE> operator+(const PolynomialUnivariateDense<RE> &a, const PolynomialUnivariateDense<RE> &b){
    PolynomialUnivariateDense<RE> tmp(a);
    tmp += b;
    return tmp;
}
template<Ring RE>
PolynomialUnivariateDense<RE> operator-(const PolynomialUnivariateDense<RE> &a, const PolynomialUnivariateDense<RE> &b){
    PolynomialUnivariateDense<RE> tmp(a);
    tmp -= b;
    return tmp;
}
template<Ring RE>
PolynomialUnivariateDense<RE> operator*(const PolynomialUnivariateDense<RE> &a, const PolynomialUnivariateDense<RE> &b){
    PolynomialUnivariateDense<RE> tmp(a);
    tmp *= b;
    return tmp;
}

// Scalar Multiplication
template<Ring RE>
PolynomialUnivariateDense<RE> operator*(const PolynomialUnivariateDense<RE> &a, const RE &s){
    PolynomialUnivariateDense<RE> tmp(a);
    tmp *= s;
    return tmp;
}

template<Ring RE>
PolynomialUnivariateDense<RE> operator*(const RE &s, const PolynomialUnivariateDense<RE> &a){
    PolynomialUnivariateDense<RE> tmp(a);
    tmp *= s;
    return tmp;
}

template<Ring RE>
std::ostream &operator<<(std::ostream &os, const PolynomialUnivariateDense<RE> &a){
    RE zero;
    size_t deg = a.degree();
    for(auto it = a.rbegin(); it != a.rend(); ++it){
        if(*it != zero){
            os<<*it<<"x^"<<deg<<" ";
        }
        --deg;
    }
    return os;
}

};

#endif