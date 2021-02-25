#include <iostream>
#include <string>
#include "huc/Rings/Integer.hh"
#include "huc/Modules/Polynomial.hh"
// #include "huc/Modules/Matrix.hh"
// #include "huc/Modules/CartesianProduct.hh"
// #include "huc/Rings/IntegerMod.hh"

using namespace huc;

int main(){
    PolynomialUnivariateDense<Integer> f;
    PolynomialUnivariateDense<Integer> g;

    f *= g; 

    return 0;
}
