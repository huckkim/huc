#ifndef POLY_H

#define POLY_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <initializer_list>

namespace schoof{

template <typename T> class Polynomial{
    size_t degree;
    T* coeff;
public:
    Polynomial(size_t degree = 0, T x = T{}):degree{degree}, coeff{static_cast<T*> (operator new(sizeof(T)*(degree+1)))}{
        for(size_t i = 0; i <= degree; ++i){
            new(coeff+i) T(x);
        }
    }
    Polynomial():degree{0}, coeff{static_cast<T*> (operator new(sizeof(T)))}{}
    Polynomial(std::initializer_list<T> init):degree{init.size()-1}, coeff{static_cast<T*> (operator new(sizeof(T) * (degree+1)))}{
        size_t i = 0;
        for(auto x : init){
            new(coeff+(i++)) T(x);
        }
    }

    Polynomial(const Polynomial<T> &other):degree{other.degree}, coeff{static_cast<T*> (operator new(sizeof(T)*(degree+1)))}{
        for(size_t i = 0; i <= degree; ++i)
            new(coeff+i) T(other.coeff[i]);

    }
    Polynomial(Polynomial<T> &&other):degree{other.degree}, coeff{other.coeff}{
        other.coeff = nullptr;
    }
    Polynomial<T> &operator=(const Polynomial<T> &other){
        Polynomial<T> tmp = other;
        using std::swap;
        swap(degree, tmp.degree);
        swap(coeff, tmp.coeff);
        return *this;
    }
    Polynomial<T> &operator=(Polynomial<T> &&other){
        using std::swap;
        swap(degree, other.degree);
        swap(coeff, other.coeff);
        return *this;
    }

    void clear(){
        ++degree;
        for(; degree != 0;--degree)
            coeff[degree-1].~T();
    }

    ~Polynomial(){
        clear();
        operator delete(coeff);
    }

    T &operator[](size_t i){return coeff[i];}
    const T &operator[](size_t i) const {return coeff[i];}

    size_t getDegree(){return degree;}
    const size_t getDegree() const{return degree;}

};

template <typename T> std::ostream &operator<<(std::ostream &out, const Polynomial<T> &p){
    bool lc = true;
    for(size_t i = p.getDegree(); i != 0; --i){
        if(p[i] == 0) continue;
        else if(p[i] > 0){
            if(i == 1){
                if(p[i] == 1) out<<(lc? "" : "+")<<"x";
                else out<<(lc? "" : "+")<<p[i]<<"x";
            }
            else{
                if(p[i] == 1) out<<(lc? "" : "+")<<"x^"<<i;
                else out<<(lc? "" : "+")<<p[i]<<"x^"<<i;
            }
        }
        else{
            if(i == 1){
                if(p[i] == -1) out<<"-x";
                else out<<p[i]<<"x";
            }
            else{
                if(p[i] == -1) out<<"-x^"<<i;
                else out<<p[i]<<"x^"<<i;
            }
        }
        lc = false;
    }
    if(p[0] == 0);
    else if(p[0] > 0){
        if(p[0] == 1) out<<"+1";
        else out<<"+"<<p[0];
    }
    else{
        if(p[0] == -1) out<<"-1";
        else out<<p[0];
    }
    return out;
}

template <typename T> Polynomial<T> operator+(const Polynomial<T> &p1, const Polynomial<T> &p2){
    size_t mx;
    size_t p1mx = p1.getDegree();
    size_t p2mx = p2.getDegree();
    if(p1mx > p2mx) mx = p1mx;
    else mx = p2mx;
    Polynomial<T> p(mx);
    for(size_t i = 0; i <= mx; ++i){
        if(mx > p1mx) p[i] = p2[i];
        else if(mx > p2mx) p[i] = p1[i];
        else p[i] = p1[i] + p2[i];
    }
    return p;
}

template <typename T> Polynomial<T> operator*(const Polynomial<T> &p1, const Polynomial<T> &p2){
    Polynomial<T> p(p1.getDegree() + p2.getDegree());
    for(size_t k = 0; k <= p1.getDegree() + p2.getDegree(); ++k){
        T new_coeff{};
        T f,g;
        T sum{};
        for(size_t i = 0; i <= k; ++i){
            new_coeff = T{};
            if(i <= p1.getDegree()) f = p1[i];
            else f = T{};
            if((k-i) <= p2.getDegree()) g = p2[k-i];
            else g = T{};
            new_coeff = f * g;
            sum += new_coeff;
        }
        p[k] = sum;
    }
    return p;
}
}
#endif