#include <iostream>
using namespace std;

/* class Base {
protected:
    void protectedMethod();
};

class Derived : public Base {

};

int main() {
    Base b;
    b.protectedMethod(); // main() cannot access protected methods
    Derived d;
    d.protectedMethod(); // main() cannot access protected methods
} */

/* ==================================================================== */
/* ==================================================================== */

/* class Pet {
public:
    void eat() { cout << "Pet::eat\n"; }
};

class Cat : public Pet {
public:
    void eat() { cout << "Cat::eat\n"; }
};

int main() {
    Pet* petP = new Cat();
    petP->eat();
    // Cat* catP = petP; // Pet cannot be used to initialize Cats (slicing problem)
    // catP->eat();
} */

/* ==================================================================== */
/* ==================================================================== */

/* class Base {
public:
    virtual void display() { cout << "Base: " << n << endl; }
protected:
    int n = 42;
};

class Derived : public Base {
public:
    virtual void display() { cout << "Derived: " << n << endl; }
};

int main() {
    Base* base = new Derived();
    base->display(); // polymorphism
} */

/* ==================================================================== */
/* ==================================================================== */

/* class FlyingMachine {
public:
    FlyingMachine() {}
    void fly() { cout << "In FlyingMachine fly()\n"; }
};

class HangGlider : public FlyingMachine {
public:
    virtual void crash() { cout << "HangGlider crashing\n"; }
    void fly() { cout << "In HangGlider fly()\n"; }
};

int main() {
    HangGlider hanger;
    FlyingMachine flier;
    hanger.fly();
    flier.fly();
    flier = hanger;
    hanger.fly();
    flier.fly();
    // flier.crash(); // flier doesn't have a member crash()
} */

/* ==================================================================== */
/* ==================================================================== */

/* class Member {
public:
    Member() {cout << 1;}
    ~Member() {cout << 2;}
};

class Base {
public:
    Base() {cout << 3;}
    ~Base() {cout << 4;}
};

class Derived : public Base {
    Member member;
public:
    Derived() {cout << 5;}
    ~Derived() {cout << 6;}
};

int main() {
    Derived der;
    // initialization list initializes Base
    // Member member initializes member
    // calls Derived()
    // destructs der top down (Derived->Member->Base)
    //  as main runs out of scope
} */

/* ==================================================================== */
/* ==================================================================== */

