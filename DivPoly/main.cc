#include <iostream>
#include "poly.hh"

using schoof::Polynomial;

int main(){
    Polynomial<int> f{1,1,1,1,1};
    Polynomial<int> g = f;
    std::cout<<f<<std::endl;
    std::cout<<g<<std::endl;

    Polynomial<int> h = f + g;
    std::cout<<h<<std::endl;

    h = f * g;
    std::cout<<h<<std::endl;

    return 0;
}