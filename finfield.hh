#ifndef FINFIELD_H
#define FINFIELD_H

#include <cstddef>
#include <iostream>

namespace schoof{

class Zmod{
    int modulus;
    int n;
public:
    Zmod(int modulus = 2, int n = 0):modulus{modulus}, n{n % modulus}{}
    int val(){return n;}
    const int val() const {return n;}

    int mod(){return modulus;}
    const int mod() const{return modulus;}
};

std::ostream &operator<<(std::ostream &os, const Zmod &z){
    os<<z.val();
    return os;
}

Zmod operator+(const Zmod &z1, const Zmod &z2){
    return Zmod{z1.mod(), z1.val() + z2.val()};
}

Zmod operator*(const Zmod &z1, const Zmod &z2){
    return Zmod{z1.mod(), z1.val() * z2.val()};
}

}

#endif