#ifndef ELLIPTIC_H
#define ELLIPTIC_H

#include "algebraic.hh"
#include "poly.hh"

namespace schoof{

template<Field F>
class Elliptic{
    typedef typename F::Element FElem;
    F &field;
    Polynomial<F> relation;
public:
    class Element{
        F &field;
        bool infinity;
        FElem alpha, beta;
        Element():field{field}, infinity{true}, alpha{FElem{}}, beta{FElem{}}{}
        Element(FElem alpha, FElem beta):field{field}, infinity{false},alpha{alpha}, beta{beta}{}
    public:
        FElem &x(){ return alpha; }
        const FElem &x() const { return alpha; }

        FElem &y(){ return beta; }
        const FElem &y() const { return beta; }

        bool is_infinity(){ return infinity; }

        bool operator==(const Element &other){
            if(infinity) return other.is_infinity();
            else{
                return (alpha == other.alpha) && (beta == other.beta);
            }
        }

        const F &getF(){ return field; }

        friend class Elliptic;
    };

    Elliptic(F &field, FElem a, FElem b):field{field}, relation{Polynomial<F>{b, a, field.zero(), field.one()}}{}
    Element zero(){ return Element{field.zero(), field.one()}; }
    Element one(){ return Element{field.one(), field.one()}; }
};

template<Field F>
typename Elliptic<F>::Element operator+(const typename Elliptic<F>::Element &a, const typename Elliptic<F>::Element &b){
    // Point doubling
    if(a == b){
        if(a.x() == b.x()){
            if(a.y() == a.getF().zero());
            
        }
    }
    // Generic addition
    else{
        F gamma = (b.y() - a.y())/(b.x() - a.x());
        gamma *= gamma;
        F alpha3 = -a.x() + (-b.x()) + gamma;
        F beta3 = -a.y()+gamma*(a.x() - alpha3);
        return typename Elliptic<F>::Element{alpha3, beta3};
    }
}

}// namespace schoof

#endif