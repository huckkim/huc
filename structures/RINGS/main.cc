#include "integer_ring.hh"
#include <iostream>

using namespace huc;

int main(){
    Integer m1{"170141183460469231731687303715884105727"};
    Integer m2{"162259276829213363391578010288127"};
    Integer m3 = add(m1,m2);
    Integer m4 = sub(m3, m1);
    std::cout<<std::boolalpha<<(m4==m2)<<std::endl;
    std::cout<<m3<<std::endl;
    std::cout<<m1<<std::endl;
    std::cout<<m4<<std::endl;

    return 0;
}
