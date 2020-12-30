#ifndef ALG_STRUCT_H
#define ALG_STRUCT_H

#include <concepts>

namespace huc{

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

/**
 * Requirements of Modules
 * 
 * A Module requires a Ring (or more strictly Field) and exitence of scalar multiplicaiotn
 */
template<typename ME, typename RE>
concept Module = Ring<RE> && requires(ME a, ME b, RE s){
    {-a}->std::same_as<ME>;
    {a-b}->std::same_as<ME>;
    {a+b}->std::same_as<ME>;
    {a==b}->std::same_as<bool>;
    {a!=b}->std::same_as<bool>;
    {s*a}->std::same_as<ME>;
    {a*s}->std::same_as<ME>;
    a+=b; a-=b;
    ME{};
};

} // namespace huc

#endif
