#ifndef FIELDS_H
#define FEILDS_H

#include <iostream>

namespace schoof{

class Rationals{
public:
    class Element{
        int a, b;
    public:
        Element():a{0},b{1}{}
        Element(int a, int b): a{a}, b{b}{}

        Element &operator+=(const Element &other){
            a = a*other.b + other.a*b;
            b *= other.b;
            return *this;
        }
        Element &operator-=(const Element &other){
            a = a*other.b - other.a*b;
            b *= other.b;
            return *this;
        }
        Element &operator*=(const Element &other){
            a *= other.a;
            b *= other.b;
            return *this;
        }
        Element &operator/=(const Element &other){
            // WARNING DOES NOT WORK WHEN DIVIDING BY SELF
            int na = a * other.b;
            b *= other.a;
            a = na;
            return *this;
        }
        bool operator==(const Element &other){
            int n = b * other.a;
            int d = a * other.b;
            return n == d;
        }
        Element operator-(){
            return Element{-a, b};
        }
        Element inv(){
            return Element{b, a};
        }

        int &num(){ return a; }
        const int &num() const{ return a; }

        int &denom(){ return b; }
        const int &denom() const{ return b; }
    };

    Element one(){ return Element{1,1}; }
    Element zero(){ return Element{0,1}; }
};

Rationals::Element operator+(const Rationals::Element &a, const Rationals::Element &b){
    return Rationals::Element{a.num()*b.denom()+b.num()*a.denom(), a.denom() * b.denom()};
}
Rationals::Element operator-(const Rationals::Element &a, const Rationals::Element &b){
    return Rationals::Element{a.num()*b.denom()-b.num()*a.denom(), a.denom() * b.denom()};
}
Rationals::Element operator*(const Rationals::Element &a, const Rationals::Element &b){
    return Rationals::Element{a.num()*b.num(), a.denom()*b.denom()};
}
Rationals::Element operator/(const Rationals::Element &a, const Rationals::Element &b){
    return Rationals::Element{a.num()*b.denom(), a.denom()*b.num()};
}

std::ostream &operator<<(std::ostream &os, const Rationals::Element &r){
    os<<"("<<r.num()<<"/"<<r.denom()<<")";
    return os;
}

class Zmod{

};

}
#endif