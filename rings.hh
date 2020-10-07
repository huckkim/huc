#ifndef RINGS_H
#define RINGS_H

namespace schoof{

#include <iostream>


/**
 * @brief A simple wrapper for the integers to satisfies the requirements for Ring the ring concept, see algebraic.hh
 */
class IntRing{
public:
    class Element{
        int n;
    public:
        Element(int n):n{n}{}
        Element():n{0}{}
        int& val(){ return n; }
        const int& val() const{ return n; }
        bool operator==(const Element& other){ return n == other.n; }
        Element operator-(){ return Element{-n}; }
        friend class IntRing;
    };

    Element zero(){ return Element{0}; }
    Element one(){ return Element{1}; }
};

IntRing::Element operator+(const IntRing::Element &a, const IntRing::Element &b){
    return IntRing::Element{a.val() + b.val()};
}


IntRing::Element operator*(const IntRing::Element &a, const IntRing::Element &b){
    return IntRing::Element{a.val() * b.val()};
}

std::ostream &operator<<(std::ostream &os, const IntRing::Element &a){
    os<<a.val();
    return os;
}

}

#endif
