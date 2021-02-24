#include "huc/Rings/Integer.hh"

namespace huc{

Integer::Integer(mpz_class &&n): n{std::move(n)} {}
Integer::Integer(const mpz_class &n): n{n} {}

Integer::Integer(int n): n{n} {}
Integer::Integer(std::string s): n{s} {}

bool Integer::operator==(const Integer &other){
    return n == other.n;
}
bool Integer::operator!=(const Integer &other){
    return n != other.n;
}

Integer &Integer::operator+=(const Integer &other){
    n += other.n;
    return *this;
}
Integer &Integer::operator-=(const Integer &other){
    n -= other.n;
    return *this;
}
Integer &Integer::operator*=(const Integer &other){
    n *= other.n;
    return *this;
}

Integer Integer::operator-(){ return Integer{-n}; }

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
