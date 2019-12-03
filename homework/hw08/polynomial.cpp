/* 
    POLYNOMIAL SOURCE FILE 
    Herman Lin
*/

#include "polynomial.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/* ========================= */
/* POLYNOMIAL IMPLEMENTATION */
/* ========================= */

struct Polynomial::Node {
    Node (int data = 0, Node* next = nullptr)
        : data(data), next(next)
    {}

    int data;
    Node* next;
};

Polynomial::Polynomial (const vector<int>& coeffs) {
    // check for "zero polynomial"
    if (coeffs.size() == 1 && coeffs[0] == 0) {
        coeffPtr = new Node(0);
        degree = 0;
    }
    else {
        // "clean" leading zeros before processing the vector
        int highestNonZero = 0;
        while (coeffs[highestNonZero] == 0) ++highestNonZero;
        degree = coeffs.size() - 1 - highestNonZero;

        int index = coeffs.size() - 1;
        coeffPtr = new Node(coeffs[index]);
        Node* ptr = coeffPtr;
        while (index != highestNonZero) {
            --index;
            ptr->next = new Node(coeffs[index]);
            ptr = ptr->next;
        }
    }
}

Polynomial::Polynomial (const Polynomial& rhs) {
    degree = rhs.degree;
    vector<int> coeffs;
    Node* rhsPtr = rhs.coeffPtr;

    // loop throuh rhs coefficients and add to coeffs
    while (rhsPtr) {
        coeffs.push_back(rhsPtr->data);
        rhsPtr = rhsPtr->next;
    }

    // loop through coeffs
    coeffPtr = new Node(coeffs[0]);
    Node* thisPtr = coeffPtr;
    for (size_t i = 1; i < coeffs.size(); ++i) {
        thisPtr->next = new Node(coeffs[i]);
        thisPtr = thisPtr->next;
    }
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    // check for self assignment
    if (this != &rhs) {
        // delete
        Node* ptr = coeffPtr;
        while (ptr) {
            Node* nextPtr = ptr->next;
            delete ptr;
            ptr = nextPtr;
        }
        degree = 0;

        // allocate and copy
        degree = rhs.degree;
        vector<int> coeffs;
        Node* rhsPtr = rhs.coeffPtr;

        // loop throuh rhs coefficients and add to coeffs
        while (rhsPtr) {
            coeffs.push_back(rhsPtr->data);
            rhsPtr = rhsPtr->next;
        }

        // loop through coeffs
        coeffPtr = new Node(coeffs[0]);
        Node* thisPtr = coeffPtr;
        for (size_t i = 1; i < coeffs.size(); ++i) {
            thisPtr->next = new Node(coeffs[i]);
            thisPtr = thisPtr->next;
        }
    }
    // return self
    return *this;
}

Polynomial::~Polynomial() {
    // cout << "~~Running Polynomial Deconstructor~~" << endl;
    Node* ptr = coeffPtr;
    while (ptr) {
        // cout << "deleting " << ptr->data << endl;
        Node* nextPtr = ptr->next;
        delete ptr;
        ptr = nextPtr;
    }
}

int Polynomial::evaluate (int val) {
    Node* ptr = coeffPtr;
    if (degree == 0) return ptr->data;
    else {
        int result, power = 0;
        while (ptr) {
            result += (ptr->data) * (pow(5, power));
            ++power;
            ptr = ptr->next;
        }
        return result;
    }
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* thisPtr = coeffPtr;
    Node* rhsPtr = rhs.coeffPtr;
    // keep looping until either linkedlist reaches nullptr
    while (thisPtr && rhsPtr) {
        thisPtr->data += rhsPtr->data;
        thisPtr = thisPtr->next;
        rhsPtr = rhsPtr->next;
    }

    thisPtr = coeffPtr;
    // if rhs is a higher-degree polynomial, add rest of rhs to this
    if (rhs.degree > degree) {
        while (thisPtr->next) thisPtr = thisPtr->next;
        while (rhsPtr) {
            thisPtr->next = new Node(rhsPtr->data);
            ++degree;
            rhsPtr = rhsPtr->next;
            thisPtr = thisPtr->next;
        }
    }
    // remove any 'leading' zeros from the linked list
    /* if lhs is a higher degree than rhs, guarantees no leading zeros */
    /* adding the rest of rhs, if any, guarantees no leading zeros */
    else if (rhs.degree == degree) {
        // put all coefficients into an array
        int summation [degree + 1];
        for (int i = 0; i < degree + 1; ++i) {
            summation[i] = thisPtr->data;
            thisPtr = thisPtr->next;
        }

        // find first instance of leading zeros
        size_t startOfLeadZeros = degree;
        while (summation[startOfLeadZeros] == 0) --startOfLeadZeros;

        // loop through coefficients until reach the first leading zero
        thisPtr = coeffPtr;
        for (size_t i = 0; i < startOfLeadZeros; ++i) thisPtr = thisPtr->next;

        // set next to nullptr and delete leading zero nodes
        Node* leadZeros = thisPtr->next;
        thisPtr->next = nullptr;
        while (leadZeros) {
            Node* nextZero = leadZeros->next;
            delete leadZeros;
            --degree;
            leadZeros = nextZero;
        }
    }
    return *this;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result(lhs);
    return result += rhs;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if (lhs.degree != rhs.degree) return false;
    Polynomial::Node* lhsPtr = lhs.coeffPtr;
    Polynomial::Node* rhsPtr = rhs.coeffPtr;
    while (lhsPtr) {
        if (lhsPtr->data != rhsPtr->data) return false;
        lhsPtr = lhsPtr->next;
        rhsPtr = rhsPtr->next;
    }
    return true;
}   

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) { return !(lhs == rhs); }

ostream& operator<<(ostream& os, const Polynomial& poly) {
    // use a temporary array for printing
    int index = 0;
    int printArr [poly.degree + 1];
    Polynomial::Node* ptr = poly.coeffPtr;
    while (ptr) {
        printArr[index] = ptr->data;
        ptr = ptr->next;
        ++index;
    }

    // loop through the array backwards to print, using the index as the 'power'
    for (int i = poly.degree; i > 0; --i) {
        // if the coefficient == 0...
        if (printArr[i] == 0) continue;
        // else if the coefficient == 1...
        else if (printArr[i] == 1) os << 'x';
        else os << printArr[i] << 'x';

        // if the 'power' is 1...
        if (i == 1) os << " + ";
        else os << '^' << i << " + ";
    } 
    // print the constant
    os << printArr[0];
    return os;
}

