#include <iostream>
#include <concepts>
#include "poly.hh"
#include "finfield.hh"
#include "elliptic.hh"

using schoof::Polynomial;
using schoof::Zmod;
using schoof::Elliptic;

int main(){
    Polynomial<int> f{1,1,1,1,1};
    Polynomial<int> g = f;
    std::cout<<f<<std::endl;
    std::cout<<g<<std::endl;

    Polynomial<int> h = f + g;
    std::cout<<h<<std::endl;

    h = f * g;
    std::cout<<h<<std::endl;

    std::cout<<f(4)<<std::endl;

    /*
    Zmod a_5{5, 3};
    std::cout<<a_5<<std::endl;

    Zmod b_5{5, 12};
    std::cout<<b_5<<std::endl;

    std::cout<<a_5+b_5<<std::endl;
    std::cout<<a_5*b_5<<std::endl;
    */

    return 0;
}