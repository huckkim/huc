#include <iostream>
#include "poly.hh"
#include "elliptic.hh"

using namespace schoof;

class IntRing{
public:
    class element{
        int n;
    public:
        element():n{0}{}
        element(int n):n{n}{}

        element &operator+=(element a){
            n += a.n;
            return *this;
        }
        element &operator*=(element a){
            n *= a.n;
            return *this;
        }

        friend class IntRing;
        friend IntRing::element operator+(IntRing::element a, IntRing::element b);
        friend IntRing::element operator*(IntRing::element a, IntRing::element b);
        friend std::ostream &operator<<(std::ostream &os, const element &a);
    };
    element zero(){ return element{0}; }
    element one(){ return element{1}; }
};

IntRing::element operator+(IntRing::element a, IntRing::element b){
    return IntRing::element{a.n + b.n};
}

IntRing::element operator*(IntRing::element a, IntRing::element b){
    return IntRing::element{a.n * b.n};
}

std::ostream &operator<<(std::ostream &os, const IntRing::element &a){
    os<<a.n;
    return os;
}

template<RingElement R>
R add(R a, R b){
    return a+b;
}

template<Ring R>
typename R::element ring_add(R r){
    typename R::element a = r.zero();
    typename R::element b = r.one();
    return a+b;
}

int main(){
    IntRing I;
    IntRing::element one = I.one();
    IntRing::element two = one + one;
    IntRing::element three = one + two;

    std::cout<<one<<" "<<two<<" "<<three<<std::endl;

    Polynomial<IntRing> f{one, two, three};
    std::cout<<"f: "<<f<<std::endl;

    IntRing::element sum = add<IntRing::element>(one, two);
    std::cout<<"sum: "<<sum<<std::endl;

    IntRing::element val = f(two);
    std::cout<<"f(two): "<<val<<std::endl;

    Polynomial<IntRing> g(5, I.one());
    std::cout<<"g: "<<g<<std::endl;
    std::cout<<"g(two): "<<g(two)<<std::endl;

    Polynomial<IntRing> h = f * g;
    std::cout<<"f*g = h: "<<h<<std::endl;
    std::cout<<"h(two): "<<h(two)<<std::endl;

    Polynomial<IntRing> t{5};
    t = f+g;
    std::cout<<"f+g = t: "<<t<<std::endl;
    std::cout<<"t(two): "<<t(two)<<std::endl;

    return 0;
}