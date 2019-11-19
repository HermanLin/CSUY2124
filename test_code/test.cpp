#include <iostream>
#include <vector>
#include <string>

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

/* class Embedded {
public:
    Embedded() { cout << "A"; }
};
class Base {
public:
    Base() { cout << "B"; }
};
class Derived : public Base {
public:
    Derived() { cout << "C"; }
    Embedded e;
};

int main() {
    Derived der;
} */

/* ==================================================================== */
/* ==================================================================== */

/* class Parent {};
class Child : public Parent {};
class Grandchild : public Child {};

void func(Parent& base) { cout << "func(Parent)\n"; }
void func(Child& derived) {cout << "func(Child)\n"; }
  
void func(Parent& base, Child& derived) { ; }
void func(Child& derived, Parent& base) { ; }


void otherFunc(Parent& base) {
    func(base);
}

int main() {
    Parent parent;
    func(parent);
    Child child;
    func(child);

    Grandchild gc;
    func(gc);

    //func(gc, gc);

    otherFunc(child);
} */

/* ==================================================================== */
/* ==================================================================== */

/* int* data = new int[12];

&data[5];

[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
data -> 0x0;
data[5] = 4;
&data[5] -> 0x4;
data+5 -> 0x4; */

/* ==================================================================== */
/* ==================================================================== */

/* class Derived;

class Base {
public:
    virtual void method (Base& arg) {
        cout << "Base::method(Base)\n";
    }
    virtual void method(Derived& arg) {
        cout << "Base::method(Derived)\n";
    }
};

class Derived : public Base {
public:
    void method(Base& arg) {
        cout << "Derived::method(Base)\n";
    }
    void method (Derived& arg) {
        cout << "Derived::method(Derived)\n";
    }
};

void someFunc(Base& argA, Base& argB) {
    argA.method(argB);
}

int main() {
    Derived der;
    Base base;
    someFunc(base, der);
} */

/* ==================================================================== */
/* ==================================================================== */

/* class FlyingMachine {
public:
    FlyingMachine() {}
    virtual void fly() { cout << "In fm fly()" ; }
};

class HangGlider : public FlyingMachine {
public:
    virtual void crash() { cout << "HangGlider Crashing"; }
    void fly() { cout << "in hg fly()"; }
};

int main() {
    HangGlider hanger;
    FlyingMachine flier;
    flier = hanger;
    flier.fly();
    // flier.crash();
} */

/* ==================================================================== */
/* ==================================================================== */

/* class Base {};

class Derived : public Base {
public:
    // Derived der2 = der1;
    Derived (const Derived& rhs)
        : Base(rhs), foo(rhs.foo)
    {}

    // der2 = der1;
    Derived& operator=(const Derived& rhs) {
        if (this != &rhs) {
            Base::operator=(rhs);
            foo = rhs.foo;
        }
        return *this;
    }


private:
    int foo;
}; */

/* ==================================================================== */
/* ==================================================================== */

// class Company;
// class Employee;
// class Geek;
// class NerdPower;

// /* EMPLOYEE */
// // Company* boss
// // string name
// // int salary
// class Employee {
// public:
//     virtual void display(ostream& os) const = 0;

//     Employee (const string& name, int celery) 
//         : employeeName(name), salary(celery), boss(nullptr)
//     {}

//     void setCompany(Company* newBoss) { boss = newBoss; }
//     int getDivSize() const { return boss->sizeOf(); }

//     Company* isHired() const { return boss; }
// protected:
//     Company* boss;
//     string employeeName;
//     int salary;
// };

// /* GEEK */
// // class Geek : public Employee {...}
// // NerdPower np(iq, nb)
// class Geek : public Employee {
// public:
//     void display(ostream& os) const {
//         os << "Geek: " << employeeName << "; Salary: " << salary << "; ";
//         os << np << endl;
//     }

//     Geek (const string& name, const int salary, const int iq, const int baths)
//         : Employee(name, salary), np(iq, baths)
//     {}
// private:
//     NerdPower np;
// };

// /* MANAGER */

// /* NERDPOWER */
// // int iq
// // int numBaths
// // NerdPower() {...}
// // friend ostream& operator<<(...) {...}

// /* COMPANY */
// // vector<Employee*> employees
// // hire(Employee&) {...}
// // sizeOf()
// class Company{
//     friend ostream& operator<<(ostream& os, const Company& rhs) {
//         os << "Company: " << rhs.companyName << endl;
//         for (Employee* employee : rhs.employees) {
//             employee->display(os);
//         }
//         return os;
//     }
// public:
//     Company (const string& name) : companyName(name) {}

//     int sizeOf() const {
//         return employees.size();
//     }

//     bool hire(Employee& hiree) {
//         if (hiree.isHired()) return false;
//         else if (hiree.isHired() == this) return false;
//         hiree.setCompany(this);
//         employees.push_back(&hiree);
//         return true;
//     }
// private:
//     vector<Employee*> employees;
//     string companyName;
// };

// int main() {
//     Geek wally("Wally", 150, 120, 10);
//     wally.getDivSize();
// }

/* int main() {
    int* data = new int[12];
    data[5] = 100;
    cout << *data+5 << endl;
    cout << *(data+5) << endl;
} */

/* ==================================================================== */
/* ==================================================================== */

// /* FOOD */
// // int numIng
// // string* ingPtr; (= new string[0])
// // implement assignment
// // prototypes for copy and destructor

// /* CHOCOLATE */
// // class Chocolate : public Food {...}
// // int* percentage = new int(50)

// class Food {
//     friend ostream& operator<<(ostream& os, const Food& rhs) {
//         for (size_t i = 0; i < numIng; ++i) { os << rhs.ingPtr[i] << ' '; }
//         return os;
//     }
// public:
//     Food () : ingPtr(new string[0]), numIng(0) {}
//     Food (const Food& rhs);
//     virtual ~Food();
//     Food& operator=(const Food& rhs) {
//         if (this != &rhs) {
//             delete [] ingPtr;
//             numIng = rhs.numIng;
//             ingPtr = new string[numIng];
//             for (size_t i = 0; i < numIng; ++i) {
//                 string* newIng = new string(rhs.ingPtr[i]);
//                 ingPtr[i] = *newIng;
//             } 
//         }
//         return *this;
//     }
//     explicit operator bool() const { return numIng > 0; }
// private:
//     string* ingPtr;
//     int numIng;
// };

// class Chocolate : public Food {
// public:
//     Chocolate (int percent = 50) : Food(), percentage(new int(percent)) {
//         Food::addIngredient("cocoa");
//     }
//     Chocolate& operator=(const Chocolate& rhs) {
//         if (this != &rhs) {
//             Food::operator=(rhs);
//             delete percentage;
//             percentage = new int(*(rhs.percentage)); }
//         return *this; 
//     }
//     Chocolate (const Chocolate& rhs) : Food(rhs) {
//         percentage = new int(*(rhs.percentage)); }
//     ~Chocolate() { delete percentage; }
// private: 
//     int* percentage; 
// };

/* ==================================================================== */
/* ==================================================================== */

/* class Parent {
public:
   virtual void foo() { cout << "Parent\n"; }
};

class Child : public Parent {
public:
    void foo() { cout << "Child\n"; }
};

class GrandChild : public Child {
public:
    void foo() { cout << "GrandChild\n"; }
};

int main() {
    GrandChild gc;
    Child* cp = new GrandChild();
    // Child* cp = &gc;
    // gc.foo();
    cp->foo();
} */

/* ==================================================================== */
/* ==================================================================== */

/* class Dragon {};
class Elder {
public:
    Elder (const string& rC) {}
};

class Skyrim : public Elder {
    friend ostream& operator<<(ostream& os, const Skyrim& rhs) {
        os << "Name: " << rhs.name << " Dragons: ";
        for (Dragon* dragon : rhs.dragons) {
            os << *dragon << ' ';
        }
        return os;
    }
public:
    Skyrim (const string& name, const string& regisCode)
        : Elder(regisCode), name(name)
    {}

    Skyrim& operator=(const Skyrim& rhs) {
        if (this != &rhs) {
            Elder::operator=(rhs);
            for (Dragon* dragon : dragons) {
                delete dragon;
            }
            name = rhs.name;
            for (Dragon* dragon : rhs.dragons) {
                Dragon* newDragon = new Dragon(*dragon);
                dragons.push_back(newDragon);
            }
        }
        return *this;
    }

    Skyrim (const Skyrim& rhs) : Elder(rhs), name(rhs.name) {
        for (Dragon* dragon : rhs.dragons) {
            Dragon* newDragon = new Dragon(*dragon);
            dragons.push_back(newDragon);
        }
    }

    ~Skyrim() {
        for (Dragon* dragon : dragons) {
            delete dragon;
        }
    }

    // skyrim1 == skyrim2
    bool operator==(const Skyrim& rhs) {
        if (dragons.size() != rhs.dragons.size()) return false;
        for (size_t index = 0; index < dragons.size(); ++index) {
            if (dragons[index] != rhs.dragons[index]) return false;
        }
        return true;
    }
private:
    string name;
    vector<Dragon*> dragons;
}; */