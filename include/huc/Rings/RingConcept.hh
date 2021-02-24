#ifndef HUC_RING_CONCEPTS_HH
#define HUC_RING_CONCEPTS_HH

#include <concepts>

/**
 * Requirements of Rings
 * 
 * A Ring requires it's elements be closed under addition and multiplication
 */
template<typename RE>
concept Ring = requires(RE a, RE b){
    {-a}->std::same_as<RE>;
    {a-b}->std::same_as<RE>;
    {a+b}->std::same_as<RE>;
    {a*b}->std::same_as<RE>;
    {a==b}->std::same_as<bool>;
    {a!=b}->std::same_as<bool>;
    a+=b; a*=b; a-=b;
    RE{};
};

#endif