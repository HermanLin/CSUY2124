// #include "polynomial.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Polynomial {
    struct Node {
        Node (int data = 0, Node* next = nullptr)
            : data(data), next(next)
        {}

        int data;
        Node* next;
    };

    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        /* Node* ptr = poly.coeffPtr;
        while (ptr) {
            os << ptr->data << ' ';
            ptr = ptr->next;
        } */

        // use a temporary array for printing
        int index = 0;
        int printArr [poly.degree + 1];
        Node* ptr = poly.coeffPtr;
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

    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
public:
    Polynomial (const vector<int>& coeffs = {0}) {
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

    Polynomial (const Polynomial& rhs) {
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

    Polynomial& operator=(const Polynomial& rhs) {
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

    ~Polynomial() {
        // cout << "~~Running Polynomial Deconstructor~~" << endl;
        Node* ptr = coeffPtr;
        while (ptr) {
            // cout << "deleting " << ptr->data << endl;
            Node* nextPtr = ptr->next;
            delete ptr;
            ptr = nextPtr;
        }
    }

    Polynomial& operator+=(const Polynomial& rhs) {
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

    int evaluate (int val) {
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
private:
    int degree;
    Node* coeffPtr;
};

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

void doNothing(Polynomial temp) {}

int main() {

    /* ======================================== */
    /* ========== PERSONAL TEST CODE ========== */
    /* ======================================== */
    // // test constructor
    // Polynomial p1({17});                        // 17
    // Polynomial p2({1, 2});                      // x + 2
    // Polynomial p3({-1, 5});                     // -1x + 5
    // Polynomial p4({5, 4, 3, 2, 1});             // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    // Polynomial has_a_zero({4, 0, 1, 7});        // 4x^3 + x + 7
    // Polynomial has_leading_zeros({0, 0, 2});    // 2
	
    // cout << "p1: " << p1 << endl;
    // cout << "p2: " << p2 << endl;
    // cout << "p3: " << p3 << endl;
    // cout << "p4: " << p4 << endl;
    // cout << "has_a_zero: " << has_a_zero << endl;
    // cout << "has_leading_zeros: " << has_leading_zeros << endl;
    // cout << "===================" << endl;

    // cout << "testing copy constructor..." << endl;
    // Polynomial p5(p4);
    // cout << "p5 (should be same as p4): " << p5 << endl;
    // cout << "===================" << endl;
    
    // cout << "testing assignment operator..." << endl;
    // Polynomial p6 = has_a_zero;
    // cout << "p6 (should be the same as has_a_zero): " << p6 << endl;
    // cout << "===================" << endl;

    // cout << "testing copy constructor and deconstructor with doNothing()..." << endl;
    // doNothing(p4);
    // cout << "===================" << endl;

    // Polynomial p4_1({5,4,3,2,1});
    // Polynomial p4_2({5,4,3,1,2});

    // cout << "p1: " << p1 << endl;
    // cout << "p4: " << p4 << endl;
    // cout << "p4_1: " << p4_1 << endl;
    // cout << "p4_2: " << p4_2 << endl;
    // cout << boolalpha;
    // cout << "evaluating p4 == p4_1: " << (p4 == p4_1) << endl;
    // cout << boolalpha;
    // cout << "evaluating p4 == p4_2: " << (p4 == p4_2) << endl;
    // cout << boolalpha;
    // cout << "evaluating p4 != p4_1: " << (p4 != p4_1) << endl;
    // cout << boolalpha;
    // cout << "evaluating p4 != p4_2: " << (p4 != p4_2) << endl;
    // cout << boolalpha;
    // cout << "evaluating p4 == p1: " << (p4 == p1) << endl;
    // cout << boolalpha;
    // cout << "evaluating p4 != p1: " << (p4 != p1) << endl;
    // cout << "===================" << endl;

    // cout << "testing += operator..." << endl;
    // p5 += p4;
    // cout << "(same size polynomial) p5 += p4: " << p5 << endl;
    // p5 += p6;
    // cout << "(lhs has higher degree than rhs) p5 += p6: " << p5 << endl;
    // p1 += p5;
    // cout << "(rhs has higher degree than lhs) p1 += p5: " << p1 << endl;
    // cout << "===================" << endl;

    // cout << "testing += operator with leading zeros..." << endl;
    // Polynomial p7({-5, -4, 0, 1, 7});
    // Polynomial p8({5, 4, 3, -1, 1});
    // cout << "p7: " << p7 << endl;
    // cout << "p8: " << p8 << endl;
    // p7 += p8;
    // cout << "p7 += p8: " << p7 << endl;
    // cout << "===================" << endl;

    // cout << "testing + operator..." << endl;
    // Polynomial p9 = p2 + p3;
    // cout << "p2: " << p2 << endl;
    // cout << "p3: " << p3 << endl;
    // cout << "p9 = p2 + p3: " << p9 << endl;
    // cout << "===================" << endl;

    // cout << "testing evaluate()..." << endl;
    // int x = 5;
    // Polynomial p11({17});
    // Polynomial p12({1, 2});
    // cout << "Evaluating p11: " << p11 << " at " << x << " yields: " << p11.evaluate(5) << endl;
    // cout << "Evaluating p12: " << p12 << " at " << x << " yields: " << p12.evaluate(5) << endl;
    // Polynomial p0({3, 2, 1});           // 3x^2 + 2x + 1
    // cout << "p7: " << p0 << endl;
    // cout << "Evaluating p0 at " << x << " yields: " << p0.evaluate(5) << endl;
    // cout << "===================\n" << endl;
    /* ================================================================== */

    cout << "========== INSTRUCTOR'S TEST CODE ==========" << endl;
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -1x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7
	
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;
    cout << "p2 + p3: " << (p2+p3) << endl; 
    cout << "p2 + p4: " << (p2+p4) << endl; 
    cout << "p4 + p2: " << (p4+p2) << endl;


    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;  
    cout << "p5: " << p5 << endl;  

    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
	
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

	/*=================================================================
	NEW TEST CODE - test if cleaning the leading 0s
	===================================================================*/

	Polynomial p8({ 1, 1 });
	Polynomial p9({ -1, 1 });
	Polynomial p10({ 0, 0, 2 });
	//p8 + p9 tests if += does the cleanup()
	//p10 tests if constructor does the cleanup()
	cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;
}