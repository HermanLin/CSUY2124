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
private:
    Node* coeffPtr;
    int degree;
public:
    Polynomial (vector<int>);
};

// void doNothing(Polynomial temp) {}

int main() {
	
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
    // cout << "p2 + p3: " << (p2+p3) << endl; 
    // cout << "p2 + p4: " << (p2+p4) << endl; 
    // cout << "p4 + p2: " << (p4+p2) << endl;


    // //test copy constructor - the statement below uses the copy constructor
    // //to initialize poly3 with the same values as poly4
    // Polynomial p5(p4);
    // p5 += p3;
    // cout << "Polynomial p5(p4);\n"
    //      << "p5 += p3;\n";

    // cout << "p4: " << p4 << endl;  
    // cout << "p5: " << p5 << endl;  

    // cout << "Calling doNothing(p5)\n";
    // doNothing(p5);
    // cout << "p5: " << p5 << endl;

    // //tests the assignment operator
    // Polynomial p6;
    // cout << "p6: " << p6 << endl;
    // cout << boolalpha;  // Causes bools true and false to be printed that way.
    // cout << "(p4 == p6) is " << (p4 == p6) << endl;
    // p6 = p4;
    // cout << "p6: " << p6 << endl;
    // cout << boolalpha;
    // cout << "(p4 == p6) is " << (p4 == p6) << endl;

    // //test the evaluaton
    // int x = 5;
    // cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    // cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
	
    // Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    // cout << "p7: " << p7 << endl;
    // cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    // cout << boolalpha;
    // cout << "(p1 == p2) is " << (p1 == p2) << endl;
    // cout << "(p1 != p2) is " << (p1 != p2) << endl;

	// /*=================================================================
	// NEW TEST CODE - test if cleaning the leading 0s
	// ===================================================================*/

	// Polynomial p8({ 1, 1 });
	// Polynomial p9({ -1, 1 });
	// Polynomial p10({ 0, 0, 2 });
	// //p8 + p9 tests if += does the cleanup()
	// //p10 tests if constructor does the cleanup()
	// cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;

    
}

/* ======================== */
/* POLYNOMIAL FUNCTIONALITY */
/* ======================== */

Polynomial::Polynomial (vector<int> coeffs) : degree(coeffs.size() - 1) {
    int index = coeffs.size() - 1; // last index
    coeffPtr = new Node(coeffs[index]); // first node is last coeff
    Node* ptr = coeffPtr;
    // loop through coeffs backwards, adding nodes to the linked list
    while (index) {
        --index;
        ptr->next = new Node(coeffs[index]);
        ptr = ptr->next;
    }
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