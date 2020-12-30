#ifndef __HUC_INTEGER_RING_H__
#define __HUC_INTEGER_RING_H__

#include <iostream>
#include <gmpxx.h>
#include <string>
#include <utility>

namespace huc{

/**
 * @brief Arbitrary Precision Integer wrapper, following Ring Concept
 * @author Huck Kim
 * @since Sat Oct 24 2020
 */
class Integer{
    mpz_class n;
public:
    Integer() {}
    Integer(mpz_class &&n): n{std::move(n)} {}
    Integer(const mpz_class &n): n{n} {}
    Integer(int n): n{n} {}
    Integer(std::string s): n{s} {}

    bool operator==(const Integer &other){
        return n == other.n;
    }
    bool operator!=(const Integer &other){
        return n != other.n;
    }

    Integer &operator+=(const Integer &other){
        n += other.n;
        return *this;
    }
    Integer &operator-=(const Integer &other){
        n -= other.n;
        return *this;
    }
    Integer &operator*=(const Integer &other){
        n *= other.n;
        return *this;
    }
    
    Integer operator-(){ return Integer{-n}; }

    friend Integer operator+(const Integer &a, const Integer &b);
    friend Integer operator-(const Integer &a, const Integer &b);
    friend Integer operator*(const Integer &a, const Integer &b);
    friend std::ostream &operator<<(std::ostream& os, const Integer &a);
};

std::ostream &operator<<(std::ostream& os, const Integer &a){
    os<<a.n;
    return os;
}

Integer operator+(const Integer &a, const Integer &b){
    return Integer{a.n+b.n};
}
Integer operator-(const Integer &a, const Integer &b){
    return Integer{a.n-b.n};
}
Integer operator*(const Integer &a, const Integer &b){
    return Integer{a.n*b.n};
}

}
#endif
