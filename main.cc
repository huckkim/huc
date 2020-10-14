#include <iostream>
#include "algebraic.hh"
// #include "poly.hh"
// #include "elliptic.hh"
#include "rings.hh"
#include "fields.hh"

using namespace schoof;

template<RingElement R>
R add(R a, R b){
    return a+b;
}

template<Ring R>
typename R::Element ring_add(R r){
    typename R::Element a = r.zero();
    typename R::Element b = r.one();
    return a+b;
}

template<Field F>
void test(F f){
    typename F::Element one = f.one();
    typename F::Element two = one + one;
    typename F::Element three = two + one;
    typename F::Element two_thirds = two/three;
    typename F::Element one_half = one/two;
    std::cout<<one<<" "<<two<<" "<<three<<" "<<two_thirds<<" "<<one_half<<std::endl;
    std::cout<<one_half + two_thirds<<std::endl;
}
int main(){
    IntRing I;
    IntRing::Element one = I.one();
    IntRing::Element two = add<IntRing::Element>(one, one);
    IntRing::Element three = one + two;
    IntRing::Element neg_three = -three;

    std::cout<<one<<" "<<two<<" "<<three<<" "<<neg_three<<std::endl;
    Rationals R;
    test<Rationals>(R);

    /*
    Polynomial<IntRing> f{one, two, three};
    std::cout<<"f: "<<f<<std::endl;

    IntRing::Element sum = add<IntRing::Element>(one, two);
    std::cout<<"sum: "<<sum<<std::endl;

    IntRing::Element val = f(two);
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

    Rationals R;

    Elliptic<Rationals> E(R, R.one(), R.zero());
    /**/
    return 0;
}