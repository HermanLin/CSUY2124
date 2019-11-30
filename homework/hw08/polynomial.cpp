// #include "polynomial.h"
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

class Polynomial {
    friend ostream& operator<<(ostream&, const Polynomial);
    friend bool operator==(const Polynomial&, const Polynomial&);
private:
    Node* coeffPtr;
    int degree;
public:
    Polynomial (vector<int>);

    /* copy control */
    // Polynomial (const Polynomial&);
    // Polynomial& operator=(const Polynomial&);
    // ~Polynomial();

    /* overloaded unary operator */
    // Polynomial& operator+=(const Polynomial&);
};

/* overloaded binary operators */
// Polynomial operator+(const Polynomial&, const Polynomial&);
bool operator!=(const Polynomial&, const Polynomial&);

/* doNothing */
// void doNothing(Polynomial temp) {}

int main() {
	
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -1x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7
    Polynomial has_leading_zeros({0, 0, 2}); // 2
	
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;
    cout << "has_leading_zeros: " << has_leading_zeros << endl;
    cout << "===================" << endl;

    Polynomial p4_1({5,4,3,2,1});
    Polynomial p4_2({5,4,3,1,2});

    cout << "p4_1: " << p4_1 << endl;
    cout << "p4_2: " << p4_2 << endl;
    cout << "evaluating p4 == p4_1: " << (p4 == p4_1) << endl;
    cout << "evaluating p4 == p4_2: " << (p4 == p4_2) << endl;
    cout << "evaluating p4 != p4_1: " << (p4 != p4_1) << endl;
    cout << "evaluating p4 != p4_2: " << (p4 != p4_2) << endl;
    cout << "evaluating p4 == p1: " << (p4 == p1) << endl;
    cout << "evaluating p4 != p1: " << (p4 != p1) << endl;
    cout << "===================" << endl;

    // cout << "testing copy constructor..." << endl;
    // Polynomial p5(p4);
    // cout << "p5 (should be same as p4): " << p5 << endl;
    // cout << "===================" << endl;
}

/* ======================== */
/* POLYNOMIAL FUNCTIONALITY */
/* ======================== */

Polynomial::Polynomial (vector<int> coeffs) {
    // clean leading zeros before processing Polynomial Linked List
    int highestNonZero = 0;
    while (coeffs[highestNonZero] == 0) ++highestNonZero;
    // set the degree of the polynomial
    degree = coeffs.size() - 1 - highestNonZero;
    // index = last index of coeffs
    int index = coeffs.size() - 1;
    // first node of linked list is last coeff
    coeffPtr = new Node(coeffs[index]);
    Node* ptr = coeffPtr;
    // loop through coeffs backwards, adding nodes to the linked list
    while (index != highestNonZero) {
        --index;
        ptr->next = new Node(coeffs[index]);
        ptr = ptr->next;
    }
}

// Polynomial::Polynomial (const Polynomial& rhs) : degree(rhs.degree) {
//     coeffPtr = new Node();
// }

// Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {

// }

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    // check for same degree polynomial
    if (lhs.degree != rhs.degree) return false;
    Node* lhsPtr = lhs.coeffPtr;
    Node* rhsPtr = rhs.coeffPtr;
    // if any of the coefficients are not equal, return false
    while (lhsPtr) {
        if (lhsPtr->data != rhsPtr->data) return false;
        lhsPtr = lhsPtr->next;
        rhsPtr = rhsPtr->next;
    }
    return true;
}

ostream& operator<<(ostream& os, const Polynomial poly) {
    // use an temp array to print
    int index = 0;
    int prntArr [poly.degree + 1];
    Node* ptr = poly.coeffPtr;
    // fill array in order of linked list
    while (ptr) {
        prntArr[index] = ptr->data;
        ptr = ptr->next;
        ++index;
    }
    // loop through array backwards to print, using index as the 'power'
    for (int i = poly.degree; i > 0; --i) { 
        // if the coefficient is 0, don't print
        if (prntArr[i] == 0) continue;
        // elseif the coefficient is 1, only print 'x'
        else if (prntArr[i] == 1) os << 'x';
        else os << prntArr[i] << 'x';

        // if the degree is 1, print " + "
        if (i == 1) os << " + ";
        else os << '^' << i << " + ";
    }
    // print constant
    os << prntArr[0];
    return os;
}