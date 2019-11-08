/* 
    rec09.cpp
    Herman Lin
*/

#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
    // friend ostream& operator<<(ostream& os, const PrintedMaterial& pm) {
    //     os << pm.numberOfPages;
    //     return os;
    // }
public:
    PrintedMaterial (unsigned numPages) : numberOfPages(numPages) {}

    // void displayNumPages() const { cout << numberOfPages; }
    //virtual void displayNumPages() const { cout << numberOfPages; }
    virtual void displayNumPages() const = 0;
    //  -- main() is using this method (don't put in protected or private)
    //  -- virtual lets the compiler know to use a derived's display method
    //  before using the base's display method
    //  -- pure declares this base class as an abstract class:
    //      # you cannot create an instance of this class
    //      # any derived classes must override this method if it is
    //      to be a concrete class (i.e. be created)
protected:
    // unsigned getNumPages() const { return numberOfPages; }
    //  -- refrain from using getters
    //  (don't know how many fields a class will have)
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine (unsigned numPages) : PrintedMaterial(numPages) {}

    // void displayNumPages() const { cout << getNumPages();}
    void displayNumPages() const { PrintedMaterial::displayNumPages(); }
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book (unsigned numPages) : PrintedMaterial(numPages) {}

    //  -- does not need to override the pure virtual display method
    //  because is a base class for other derived classes
protected:
private:
};

class TextBook : public Book {
public:
    //TextBook (unsigned numPages) : PrintedMaterial(numPages) {}
    //  -- TextBook does not know that Book's parent is PrintedMaterial
    TextBook (unsigned numPages, unsigned numIndexPages = 0) 
        : Book(numPages), numOfIndexPages(numIndexPages)
    {}

    void displayNumPages() const {
        cout << "Pages: ";
        PrintedMaterial::displayNumPages(); 
        //  -- TextBook cannot access PrintedMaterial's private variable
        cout << ", Index: " << numOfIndexPages;
    }
protected:
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    //Novel (unsigned numPages) : PrintedMaterial(numPages) {}
    //  -- Novel does not know that Book's parent is PrintedMaterial
    Novel (unsigned numPages) : Book(numPages) {}

    // void displayNumPages() const { cout << getNumPages();}
    void displayNumPages() const { PrintedMaterial::displayNumPages(); }
protected:
private:
};

/* TASK 12 */
void displayNumberOfPages(PrintedMaterial& pm) {
    pm.displayNumPages();
}
//  -- the Principle of Substitutability will let use call the function with
//  any form of PrintedMaterial, base or derived. The virtual keyword on 
//  PrintedMaterial's display method allows for polymorphism (i.e. a display 
//  method on a derived class will be used instead of the base's)

/* TASK 14 */
void PrintedMaterial::displayNumPages() const { cout << numberOfPages; }
//  -- Need to let the derived classes utilize the an abstract base class's display method

// tester/modeler code
int main()
{
	TextBook t(123);
    TextBook t1(901, 2);
	Novel n(456);
	Magazine m(78);

    // cout << t << endl;
    // cout << n << endl;
    // cout << m << endl;
    
    cout << "Testing display methods..." << endl;
    t.displayNumPages();
    cout << endl;
    t1.displayNumPages();
    cout << endl;
    n.displayNumPages();
    cout << endl;
    m.displayNumPages();
    cout << endl;

    // cout << "\nTesting assignment with display method..." << endl;
    // PrintedMaterial pm = t; // like putting a TextBook into a vector of PrintedMaterials
    // cout << "pm = t: ";
    // pm.displayNumPages();
    // cout << endl;
    //  -- After making PrintedMaterial an abstract class, you cannot create one

    cout << "\nTesting assignment of pointers and addresses with display method..." << endl;
    PrintedMaterial* pmPtr;
    pmPtr = &t;
    /* instead of putting an actual PrintedMaterial object into the vecotr, we put
        a pointer to a PrintedMaterial object (t) into a vector of 
        pointers-to-PrintedMaterial (that is, pointers to the Base class). We'll be
        "managing" our objects by using pointers to PrintedMaterial values. */
    pmPtr->displayNumPages();
    cout << endl;
    //  -- An assignment of a PrintedMaterial* with the address of a derived class works

    cout << "\nTesting displayNumberOfPages function..." << endl;
    displayNumberOfPages(t);
    cout << endl;

    cout << "\nTesting on a vector of PrintedMaterial..." << endl;
    vector<PrintedMaterial*> pmVec;
    pmVec.push_back(&t);
    pmVec.push_back(&t1);
    pmVec.push_back(&n);
    pmVec.push_back(&m);
    for (PrintedMaterial* pmPtr : pmVec) {
        pmPtr->displayNumPages();
        cout << endl;
    }
}