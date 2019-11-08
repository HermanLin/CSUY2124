/* 
    rec08.cpp
    Tester Code
    Herman Lin
*/

#include "Rational.h"
#include <iostream>
using namespace std;
using namespace CS2124;

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