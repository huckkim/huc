#ifndef HUC_POLYNOMIAL_MODULE_HH
#define HUC_POLYNOMIAL_MODULE_HH

#include "huc/Groups/GroupConcept.hh"
#include "huc/Rings/RingConcept.hh"

#include <vector>
#include <ostream>
#include <algorithm>
#include <ranges>

namespace huc{

template<Ring RE>
class PolynomialUnivariateSparse{

};

template<Ring RE>
class PolynomialUnivariateDense{
    std::vector<RE> p;
public:

    using value_type                    = typename std::vector<RE>::value_type;
    using iterator                      = typename std::vector<RE>::iterator;
    using const_iterator                = typename std::vector<RE>::const_iterator;
    using reverse_iterator              = typename std::vector<RE>::reverse_iterator;
    using const_reverse_iterator        = typename std::vector<RE>::const_reverse_iterator;

    PolynomialUnivariateDense(std::initializer_list<RE> lst){
        for(auto a : lst){
            p.push_back(a);
        }
    }
    PolynomialUnivariateDense(const std::vector<RE> &p) : p{p} {}
    PolynomialUnivariateDense(std::vector<RE> &&p) : p{std::move(p)} {}

    PolynomialUnivariateDense() = default;
    // Copy
    PolynomialUnivariateDense(const PolynomialUnivariateDense &) = default;
    PolynomialUnivariateDense &operator=(const PolynomialUnivariateDense &) = default;
    // Move
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

    // Negate a polymomial and return the new one
    PolynomialUnivariateDense operator-(){
        std::vector<RE> tmp;
        for(auto &c : p){
            tmp.push_back(-c);
        }
        return tmp;
    }

    // Subtract two polynomials
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
    // add two polynomials
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

    // Scalar multiplication makes it a vector space
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

    // // TODO: Technically an Algebra as well as a module
    // template<Ring _RE,
    //          typename std::enable_if_t<std::is_convertible<_RE, Integer>::value>* = nullptr>
    // PolynomialUnivariateDense<_RE> &operator*=(const PolynomialUnivariateDense<_RE> &other){
    //     return *this;
    // }

    bool operator==(const PolynomialUnivariateDense &other) const = default;

    constexpr size_t size() const noexcept{ return p.size(); }
    constexpr size_t degree() const noexcept{ return p.size() ? p.size()-1 : p.size(); }

    friend PolynomialUnivariateDense operator+(const PolynomialUnivariateDense &a, const PolynomialUnivariateDense &b){
        PolynomialUnivariateDense tmp(a);
        tmp += b;
        return tmp;
    }

    friend PolynomialUnivariateDense operator-(const PolynomialUnivariateDense &a, const PolynomialUnivariateDense &b){
        PolynomialUnivariateDense tmp(a);
        tmp -= b;
        return tmp;
    }

    // Scalar multiplication left
    friend PolynomialUnivariateDense operator*(const PolynomialUnivariateDense &a, const RE &s){
        PolynomialUnivariateDense<RE> tmp(a);
        tmp *= s;
        return tmp;
    }

    // Scalar mutltiplication right
    friend PolynomialUnivariateDense operator*(const RE &s, const PolynomialUnivariateDense &a){
        PolynomialUnivariateDense<RE> tmp(a);
        tmp *= s;
        return tmp;
    }

    // Algebra Multiplication, bilinear product
    friend PolynomialUnivariateDense operator*(const PolynomialUnivariateDense &s, const PolynomialUnivariateDense &a){

    }

    friend std::ostream &operator<<(std::ostream &os, const PolynomialUnivariateDense &a){
        RE zero;
        size_t deg = a.degree();
        for(auto coeff : std::views::reverse(a)){
            if(coeff != zero){
                os << coeff << "x^" << deg << " ";
            }
            --deg;
        }
        return os;
    }
};

};

#endif
