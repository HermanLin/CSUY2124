/* 
    RATIONAL HEADER FILE
    Herman Lin
*/

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

namespace CS2124 {
    class Rational {
        friend std::ostream& operator<<(std::ostream&, const Rational&);
        friend std::istream& operator>>(std::istream&, Rational&);
        friend bool operator==(const Rational&, const Rational&);
        friend bool operator<(const Rational&, const Rational&);
    private:
        int numerator, denominator;
        void normalize();
    public:
        Rational (int num = 0, int denom = 1);

        Rational& operator+=(const Rational&);
        Rational& operator++();
        Rational operator++(int);
        explicit operator bool() const;
    };
}

#endif