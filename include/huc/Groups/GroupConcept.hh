#ifndef HUC_GROUP_CONCEPT_HH
#define HUC_GROUP_CONCEPT_HH

#include <concepts>

template<typename GE>
concept Group = requires(GE a, GE b){
    {-a}->std::same_as<GE>;
    {a-b}->std::same_as<GE>;
    {a+b}->std::same_as<GE>;
    {a==b}->std::same_as<bool>;
    {a!=b}->std::same_as<bool>;
    a+=b; a-=b;
    GE{}; GE();
};

#endif
