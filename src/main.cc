#include <iostream>
#include <string>
#include "huc/Rings/Integer.hh"
#include "huc/Modules/Polynomial.hh"
// #include "huc/Modules/Matrix.hh"
// #include "huc/Modules/CartesianProduct.hh"
// #include "huc/Rings/IntegerMod.hh"

using namespace huc;

int main(){
    std::vector<int> f_b{1,2,3,4,0,0,0};
    PolynomialUnivariateDense<int> f(f_b);
    PolynomialUnivariateDense<int> g;

    //f *= g; 

    std::cout << f << std::endl;
    std::cout << "deg: " << f.degree() << std::endl;

    f *= g;

    // will not compile ... for now
    // PolynomialUnivariateDense<Integer> h1;
    // PolynomialUnivariateDense<Integer> h2;
    // h1 *= h2;

    return 0;
}
