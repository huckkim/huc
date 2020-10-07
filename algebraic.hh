#ifndef RING_CONCEPTS_H
#define RING_CONCEPTS_H

#include <concepts>

namespace schoof{
/**
 * Requirements of a GroupElement
 * 
 * A GroupElement requires the elements to be closed under addition
 */
template<typename GE>
concept GroupElement = requires(GE a, GE b){
    {-a}->std::same_as<GE>;
    {a+b}->std::same_as<GE>;
    {a==b}->std::same_as<bool>;
};

/**
 * Requirements of a Group
 * 
 * A Group requires elements from GroupElements and an additive identity
 */
template<typename G>
concept Group = requires(G g){
    typename G::element;
    {g.zero()}->std::same_as<typename G::element>;
} && GroupElement<typename G::element>;

/**
 * Requirements of RingElement
 * 
 * A RingElement requires elements be closed under addition and multiplication
 */
template<typename RE>
concept RingElement = requires(RE a, RE b){
    {-a}->std::same_as<RE>;
    {a+b}->std::same_as<RE>;
    {a*b}->std::same_as<RE>;
    {a==b}->std::same_as<bool>;
};

/**
 * Requirements of Ring
 * 
 * A Ring requires elements from RingElement and an additive/multiplicative identity
 */
template<typename R>
concept Ring = requires(R r){
    typename R::element;
    {r.zero()}->std::same_as<typename R::element>;
    {r.one()}->std::same_as<typename R::element>;
} && RingElement<typename R::element>;

/**
 * Requirements of FieldElement
 * 
 * A FieldElement requires elements be closed under addition and multiplication
 * as well as division defined for all values except the zero();
 */
template<typename FE>
concept FieldElement = requires(FE a, FE b){
    {-a}->std::same_as<FE>;
    {a.inv()}->std::same_as<FE>
    {a+b}->std::same_as<FE>;
    {a*b}->std::same_as<FE>;
    {a/b}->std::same_as<FE>;
    {a==b}->std::same_as<bool>;
};

/**
 * Requirements of Field
 * 
 * A Field requires elements from FieldElement and an additive/multiplicative identity
 */
template<typename F>
concept Field = requires(F f){
    typename F::element;
    {f.zero()}->std::same_as<typename F::element>;
    {f.one()}->std::same_as<typename F::element>;
} && FieldElement<typename R::element>;
}

#endif