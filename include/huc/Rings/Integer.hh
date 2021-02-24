#ifndef HUC_INTEGER_RING_HH
#define HUC_INTEGER_RING_HH

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
    Integer() = default;

    Integer(const mpz_class &n);
    Integer(mpz_class &&n);

    Integer(int n);
    Integer(std::string s);

    bool operator==(const Integer &other);
    bool operator!=(const Integer &other);

    Integer &operator+=(const Integer &other);
    Integer &operator-=(const Integer &other);
    Integer &operator*=(const Integer &other);
    
    Integer operator-();

    friend Integer operator+(const Integer &a, const Integer &b);
    friend Integer operator-(const Integer &a, const Integer &b);
    friend Integer operator*(const Integer &a, const Integer &b);
    friend std::ostream &operator<<(std::ostream& os, const Integer &a);
};


}
#endif
