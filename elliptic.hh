#ifndef ELLIPTIC_H
#define ELLIPTIC_H

#include "algebraic.hh"

namespace schoof{

template<Ring R>
class Elliptic{
    typedef typename R::element RElem;
    Polynomial<R> relation;
    class element{
        bool infinity;
        RElem alpha, beta;
        element(RElem alpha, RElem beta):alpha{alpha}, beta{beta}{}
        element(bool infinity):infinity{infinity}{}
    public:
        RElem &x(){ return alpha; }
        const RElem x() const { return alpha; }

        RElem &y(){ return beta; }
        const RElem y() const { return beta; }
    };
public:
    Elliptic(R &ring, RElem A, RElem B):relation{Polynomial<R> {B, A, ring.zero(), ring.one()}}{
        std::cout<<relation<<std::endl;
    }
    element zero();
    element one();
    bool is_singular();
};

template<Ring R>
typename Elliptic<R>::element operator+(const typename Elliptic<R>::element a, const typename Elliptic<R>::element b){
    if(a.x() == b.x()) return typename Elliptic<R>::element{true};
    typename Elliptic<R>::element nalpha;
    return sum;
}

}// namespace schoof

#endif