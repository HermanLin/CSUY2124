#include "polynomial.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

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