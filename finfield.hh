#ifndef FINFIELD_H
#define FINFIELD_H

#include <cstddef>
#include <iostream>

namespace schoof{

template<typename T>
concept Field = requires(T a, T b){
    {a.zero()}->std::same_as<T>;
    {a.one()}->std::same_as<T>;
    {a.negative()}->std::same_as<T>
    {a.inverse()}->std::same_as<T>;
    {a+b}->std::same_as<T>;
    {a*b}->std::same_as<T>;
};


}

#endif