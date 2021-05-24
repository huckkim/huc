#include <iostream>
#include <string>
#include "huc/Rings/Integer.hh"
#include "huc/Modules/Polynomial.hh"
// #include "huc/Modules/Matrix.hh"
// #include "huc/Modules/CartesianProduct.hh"
// #include "huc/Rings/IntegerMod.hh"

using namespace huc;

int main(){
    PolynomialUnivariateDense<Integer> f{1,2,3,4};
    PolynomialUnivariateDense<Integer> g;

    //f *= g; 

    std::cout << f << std::endl;

    return 0;
}
