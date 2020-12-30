#include <iostream>
#include <string>
#include "alg_struct.hh"
#include "Rings/Integer.hh"
#include "Modules/Polynomial.hh"
#include "Modules/Matrix.hh"
#include "Modules/CartesianProduct.hh"

using namespace huc;

template<Ring RE>
RE add(const RE &a, const RE &b){
    return a+b;
}

template<Ring RE, Module<RE> ME>
ME addOther(const ME &a, const ME &b){
    return a + b;
}

int main(){
    Integer a{"12345667123983"};
    Integer b{"23432412345667123983"};
    Integer c{"0"};
    Integer d{"1"};
    std::cout<<a<<std::endl;
    std::cout<<b<<std::endl;
    std::cout<<c<<std::endl;
    std::cout<<d<<std::endl;
    std::cout<<a+b<<std::endl;

    std::cout<<add<Integer>(a, b)<<std::endl;
    std::cout<<add<int>(3, 2)<<std::endl;

    PolynomialUnivariateDense<Integer> p1{3,2,-1, 3,4};
    PolynomialUnivariateDense<Integer> p2{4,2,1};

    p1 += p2;

    std::cout<<p1<<std::endl;
    std::cout<<p2<<std::endl;
    std::cout<<p1(c)<<std::endl;
    std::cout<<p1(d)<<std::endl;
    std::cout<<p1(a)<<std::endl;
    std::cout<<addOther<Integer, PolynomialUnivariateDense<Integer>>(p1, p2)<<std::endl;

    /*
    CartesianProduct<Integer, Integer, Integer> cp;
    std::cout<<cp.dimension()<<std::endl;
    std::cout<<cp<<std::endl;
    std::cout<<get<0>(cp.cp)<<std::endl;
    //p1*a;
    MatrixDense<Integer, 3>(1,2,3);
    /**/
    return 0;
}