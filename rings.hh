#ifndef RINGS_H
#define RINGS_H

namespace schoof{

#include <iostream>


/**
 * @brief A simple wrapper for the integers to satisfies the requirements for Ring the ring concept, see algebraic.hh
 */
class IntRing{
public:
    class Element{
        int n;
    public:
        /**
         * @brief Initalizes with value n
         * @param n value
         */
        Element(int n):n{n}{}

        /**
         * @brief Default constructs to zero in the ring
         */
        Element():n{0}{}

        /**
         * @brief Returns ref to n
         * @return ref to n
         */
        int& val(){ return n; }

        /**
         * @overload
         */
        const int& val() const{ return n; }

        /**
         * @brief Compares with other for equality
         * @param other
         * @return true of false
         */
        bool operator==(const Element& other){ return n == other.n; }

        /**
         * @brief The additive inverse of n
         * @return -n
         */
        Element operator-(){ return Element{-n}; }

        /**
         * @brief Add and assign
         * @param other Element to add
         * @return *this
         */
        Element &operator+=(const Element &other){
            n+=other.n;
            return *this;
        }

        /**
         * @brief Subtract and assign
         * @param other Element to subtract
         * @return *this
         */
        Element &operator-=(const Element &other){
            n-=other.n;
            return *this;
        }

        /**
         * @brief Multiply and assign
         * @param other Element to multiply
         * @return *this
         */
        Element &operator*=(const Element &other){
            n*=other.n;
            return *this;
        }

        friend class IntRing;
    };


    /**
     * @brief Returns the zero element
     * @return 0
     */
    Element zero(){ return Element{0}; }

    /**
     * @brief Returns the one element
     * @return 1
     */
    Element one(){ return Element{1}; }
};


/**
 * @brief Adds two Elements together
 * @param a
 * @param b
 * @return their sum
 */
IntRing::Element operator+(const IntRing::Element &a, const IntRing::Element &b){
    return IntRing::Element{a.val() + b.val()};
}

/**
 * @brief Subtracts two Elements together
 * @param a
 * @param b
 * @return their difference
 */
IntRing::Element operator-(const IntRing::Element &a, const IntRing::Element &b){
    return IntRing::Element{a.val() - b.val()};
}

/**
 * @brief Multiplies two Elements together
 * @param a
 * @param b
 * @return their product
 */
IntRing::Element operator*(const IntRing::Element &a, const IntRing::Element &b){
    return IntRing::Element{a.val() * b.val()};
}

/**
 * @brief output operator
 * @param os outputs stream
 * @param a Element to print
 * @return  ref to output
 */
std::ostream &operator<<(std::ostream &os, const IntRing::Element &a){
    os<<a.val();
    return os;
}

}

#endif
