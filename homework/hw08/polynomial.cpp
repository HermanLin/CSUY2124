// #include "polynomial.h"
#include <iostream>
#include <vector>
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

public:
    Polynomial (vector<int> coeffs) {
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
private:
    int degree;
    Node* coeffPtr;
};

int main() {
    // test constructor
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
}