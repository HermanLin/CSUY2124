/* 
    POLYNOMIAL HEADER FILE
    Herman Lin
*/

#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <vector>
#include <cmath>

class Polynomial {
    struct Node;
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);
    friend bool operator==(const Polynomial&, const Polynomial&);
public:
    Polynomial (const std::vector<int>& = {0});
    Polynomial (const Polynomial&);
    Polynomial& operator=(const Polynomial&);
    ~Polynomial();
    Polynomial& operator+=(const Polynomial&);
    int evaluate (int);
private:
    int degree;
    Node* coeffPtr;
};

Polynomial operator+(const Polynomial&, const Polynomial&);
bool operator==(const Polynomial&, const Polynomial&);
bool operator!=(const Polynomial&, const Polynomial&);

#endif