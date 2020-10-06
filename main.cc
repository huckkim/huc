#include <iostream>
//#include "poly.hh"
//#include "finfield.hh"
#include "elliptic.hh"
#include "concept_poly.hh"

//using namespace schoof;

class IntRing{
public:
    class element{
        int n;
    public:
        element(int n):n{n}{}
        friend class IntRing;
        friend IntRing::element operator+(IntRing::element a, IntRing::element b);
        friend IntRing::element operator*(IntRing::element a, IntRing::element b);
        friend std::ostream &operator<<(std::ostream &os, element a);
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

std::ostream &operator<<(std::ostream &os, IntRing::element a){
    os<<a.n;
    return os;
}

template<concept_testing::RingElement R>
R add(R a, R b){
    return a+b;
}

template<concept_testing::Ring R>
typename R::element ring_add(R r){
    typename R::element a = r.zero();
    typename R::element b = r.one();
    return a+b;
}

using concept_testing::Polynomial;

int main(){
    IntRing I;
    IntRing::element zero = I.zero();
    IntRing::element one = I.one();

    //add<IntRing>(zero, one);

    std::cout<<add<IntRing::element>(zero, one)<<std::endl;

    std::cout<<ring_add<IntRing>(I)<<std::endl;

    Polynomial<IntRing> p(4, I.zero());
    Polynomial<IntRing> f{I.zero(), I.zero(), I.one()};

    Polynomial<IntRing> g = f;
    Polynomial<IntRing> h(2, I.one());
    h = g; 

    /*
    Polynomial<int> f{1,1,1,1,1};
    Polynomial<int> g = f;
    std::cout<<f<<std::endl;
    std::cout<<g<<std::endl;

    Polynomial<int> h = f + g;
    std::cout<<h<<std::endl;

    h = f * g;
    std::cout<<h<<std::endl;

    std::cout<<f(4)<<std::endl;
    */

    /*
    Zmod a_5{5, 3};
    std::cout<<a_5<<std::endl;

    Zmod b_5{5, 12};
    std::cout<<b_5<<std::endl;

    std::cout<<a_5+b_5<<std::endl;
    std::cout<<a_5*b_5<<std::endl;
    */
    //Polynomial<int> f;
    //Polynomial<Zmod> g;
    return 0;
}