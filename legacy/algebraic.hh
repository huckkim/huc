#ifndef RING_CONCEPTS_H
#define RING_CONCEPTS_H

#include <concepts>

namespace huc{
/**
 * Requirements of a GroupElement
 * 
 * A GroupElement requires the elements to be closed under addition
 */
template<typename GE>
concept GroupElement = requires(GE a, GE b){
    {-a}->std::same_as<GE>;
    {a-b}->std::same_as<GE>;
    {a+b}->std::same_as<GE>;
    {a==b}->std::same_as<bool>;
    a+=b; a-=b;
    GE{};
    GE(0);
};

/**
 * Requirements of RingElement
 * 
 * A RingElement requires elements be closed under addition and multiplication
 */
template<typename RE>
concept RingElement = requires(RE a, RE b){
    {-a}->std::same_as<RE>;
    {a-b}->std::same_as<RE>;
    {a+b}->std::same_as<RE>;
    {a*b}->std::same_as<RE>;
    {a==b}->std::same_as<bool>;
    a+=b; a*=b; a-=b;
    RE{};
    RE(0);
    RE(1);
};

/**
 * Requirements of FieldElement
 * 
 * A FieldElement requires elements be closed under addition and multiplication
 * as well as division defined for all values except the zero();
 */
template<typename FE>
concept FieldElement = requires(FE a, FE b){
    {-a}->std::same_as<FE>;
    {a-b}->std::same_as<FE>;
    {a.inv()}->std::same_as<FE>;
    {a+b}->std::same_as<FE>;
    {a*b}->std::same_as<FE>;
    {a/b}->std::same_as<FE>;
    {a==b}->std::same_as<bool>;
    a-=b; a+=b; a*=b; a/=b;
    FE{};
    FE(0);
    FE(1);
};

} // namespace huc
#endif