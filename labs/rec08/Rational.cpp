/* 
    RATIONAL SOURCE FILE
    Herman Lin
*/

#include "Rational.h"
#include <iostream>
using namespace std;

namespace CS2124 {
    //==============================//
    /* RATIONAL CLASS FUNCTIONALITY */
    //==============================//

    Rational::Rational (int num, int denom) : numerator(num), denominator(denom) {
        normalize();
    }

    int gcd (int a, int b) {
        while (b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    void Rational::normalize() {
        int greatestCommDenom = gcd(numerator, denominator);
        numerator /= greatestCommDenom;
        denominator /= greatestCommDenom;
        
        // make sure the negative sign is on the numerator only
        // also make sure signs are simplified i.e. -/- --> +/+
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }

    Rational& Rational::operator+=(const Rational& rhs) {
        /* 2/3 + 3/4 = 8/12 + 9/12 = 17/12 */
        numerator = (numerator * rhs.denominator) + (rhs.numerator * denominator);
        denominator *= rhs.denominator;
        this->normalize();
        return *this;
    }

    Rational& Rational::operator++() {
        numerator += denominator;
        return *this;
    }

    Rational Rational::operator++(int dummy) {
        Rational orig(*this);
        numerator += denominator;
        return orig;
    }

    Rational::operator bool() const {
        return numerator != 0;
    }

    bool operator==(const Rational& lhs, const Rational& rhs) {
        return (lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator);
    }

    bool operator<(const Rational& lhs, const Rational& rhs) {
        int left = lhs.numerator * rhs.denominator;
        int right = rhs.numerator * lhs.denominator;
        return left < right;
    }

    ostream& operator<<(ostream& os, const Rational& rational) {
        os << rational.numerator << "/" << rational.denominator;
        return os;
    }

    istream& operator>>(istream& is, Rational& rational) {
        char skipSlash;
        int num, denom;
        is >> num >> skipSlash >> denom;
        rational.numerator = num;
        rational.denominator = denom;
        rational.normalize();
        return is;
    }
}