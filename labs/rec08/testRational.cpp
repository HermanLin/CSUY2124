/*
	testRational.cpp
	CS2124
	Implement the class Rational, so that the following program works.

    Herman Lin
 */

#include <iostream>

// If time allows use separate compilation, otherwise just define the class below
//#include "Rational.h"

using namespace std;

// If time allows after implementing separate compilation, then wrap the class in a namespace.
//using namespace CS2124;

int gcd(int, int);

class Rational {
    friend ostream& operator<<(ostream&, const Rational&);
    friend istream& operator>>(istream&, Rational&);
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

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational summation(lhs);
    return summation += rhs;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

Rational& operator--(Rational& rational) {
    Rational negOne(-1);
    rational += negOne;
    return rational;
}

Rational operator--(Rational& rational, int dummy) {
    Rational negOne(-1);
    Rational original(rational);
    rational += negOne;
    return original;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return (rhs < lhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return (rhs < lhs) || (rhs == lhs);
}

int main() {
    Rational twoThirds(2,3);
    cout << twoThirds << endl;
    
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << a << endl; 
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    cout << b << endl;

    const Rational one = 1;
    //cout << one << endl;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;

    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // // Even though the above example, (a++ ++), compiled, the
    // // following shouldn't.
    // // But some compiler vendors might let it...  Is your compiler
    // // doing the right thing?
    // cout << "a-- -- = " << (a-- --) << endl;
    // cout << "a = " << a << endl;
    // ^^^ Doesn't compile ^^^ //

    // <, <=, >, >= test calls
    Rational c(a);
    cout << "\na = " << a << ", b = " << b << ", c = " << c << endl;
    cout << "a < b = " << (a < b) << endl;
    cout << "b < a = " << (b < a) << endl;
    cout << "a <= b = " << (a <= b) << endl;
    cout << "b <= a = " << (b <= a) << endl;
    cout << "a <= c = " << (a <= c) << endl;
    cout << "a > b = " << (a > b) << endl;
    cout << "b > a = " << (b > a) << endl;
    cout << "a >= b = " << (a >= b) << endl;
    cout << "b >= a = " << (b >= a) << endl;
    cout << "a >= c = " << (a >= c) << endl;

    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 
}

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

