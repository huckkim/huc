#include <utility>
#include "poly.hh"

using schoof::Polynomial;

Polynomial::Polynomial(size_t degree = 0):degree{degree}, coeff{new int [degree+1]}{
    for(size_t i = 0; i <= degree; ++i)
        coeff[i] = 0;
}

Polynomial::~Polynomial(){delete [] coeff;}

Polynomial::Polynomial(const Polynomial &other):degree{other.degree},coeff{new int[degree+1]}{
    for(size_t i = 0; i <= degree; ++i){
        coeff[i] = other.coeff[i];
    }
}

Polynomial::Polynomial(Polynomial &&other):degree{other.degree}, coeff{other.coeff}{
    other.coeff = nullptr;
}

Polynomial &Polynomial::operator=(const Polynomial &other){
    Polynomial tmp = other;
    using std::swap;
    swap(degree, tmp.degree);
    swap(coeff, tmp.coeff);
    return *this;
}

Polynomial &Polynomial::operator=(Polynomial &&other){
    using std::swap;
    swap(degree, other.degree);
    swap(coeff, other.coeff);
    return *this;
}

Polynomial schoof::operator+(const Polynomial &p1, const Polynomial &p2){
    size_t mx;
    size_t p1mx = p1.getDegree();
    size_t p2mx = p2.getDegree();
    if(p1mx > p2mx) mx = p1mx;
    else mx = p2mx;
    Polynomial p(mx);
    for(size_t i = 0; i <= mx; ++i){
        if(mx > p1mx) p[i] = p2[i];
        else if(mx > p2mx) p[i] = p1[i];
        else p[i] = p1[i] + p2[i];
    }
    return p;
}

Polynomial schoof::operator*(const Polynomial &p1, const Polynomial &p2){
    Polynomial p{p1.getDegree() + p2.getDegree()};
    for(size_t k = 0; k <= p1.getDegree() + p2.getDegree(); ++k){
        int new_coeff = 0;
        int f,g;
        int sum = 0;
        for(size_t i = 0; i <= k; ++i){
            new_coeff = 0;
            if(i <= p1.getDegree()) f = p1[i];
            else f = 0;
            if((k-i) <= p2.getDegree()) g = p2[k-i];
            else g = 0;
            new_coeff = f * g;
            sum += new_coeff;
        }
        p[k] = sum;
    }
    return p;
}

std::ostream &schoof::operator<<(std::ostream &out, const Polynomial &p){
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