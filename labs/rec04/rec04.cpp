/*===========================================================
TASK 1:
Herman Lin
rec04.cpp

This file contains several tasks to demostrate the use of
pointers and addresses, as well as how to utilize the 
debug function within different IDEs (in this case, VS Code).
===========================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Complex {
    double real;
    double img;
};

class PlainOldClass {
public:
   PlainOldClass() : x(-72) {}
   int getX() const { return x; }
   void setX( int val )  { x = val; }
private:
   int x;
};

class PlainOldClassV2 {  
public:
   PlainOldClassV2() : x(-72) {}
   int getX() const { return x; }
   void setX( int x )  { this->x = x; } // HMMMM???
private:
   int x;
};

class Colour {  
public:       
    Colour(const string& name, unsigned r, unsigned g, unsigned b)       
        : name(name), r(r), g(g), b(b) {}       
    void display() const { 
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")"; 
    }   
private:       
    string name;      // what we call this colour       
    unsigned r, g, b; // red/green/blue values for displaying  
}; 

class SpeakerSystem {
   public:
   void vibrateSpeakerCones(unsigned signal) const {

      cout << "Playing: " << signal << "Hz sound..." << endl;
      cout << "Buzz, buzzy, buzzer, bzap!!!\n";
   }
};

class Amplifier {
public:
  void attachSpeakers(const SpeakerSystem& spkrs)
   {
      if(attachedSpeakers)
         cout << "already have speakers attached!\n";
      else
         attachedSpeakers = &spkrs;
   }
  
   void detachSpeakers() { // should there be an "error" message if not attached?
      attachedSpeakers = nullptr; 
   } 
  
   void playMusic( ) const {
      if (attachedSpeakers)
         attachedSpeakers -> vibrateSpeakerCones(440); 
      else
         cout << "No speakers attached\n"; 
   }
private:
   const SpeakerSystem* attachedSpeakers = nullptr;
};

class Person {  
public:       
    Person(const string& name) : name(name), roomie(nullptr) {}
    bool movesInWith(Person& newRoomate) {
        if (!roomie && !newRoomate.roomie) {
            roomie = &newRoomate;        // now I have a new roomie            
            newRoomate.roomie = this;    // and now they do too 
            return true;
        }
        return false;
    }       
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { 
        return roomie->getName(); 
    }  
private:
    Person* roomie;       
    string name;  
};    

int main() {

    //TASK 2
    int x;
    x = 10;
    cout << "x = " << x << endl;

    //TASK 8
    int* p;  
    p = &x;
    //p = 0x61fe14;
    cout << "p = " << p << endl;

    //TASK 10
    cout << "p points to where " << *p << " is stored\n";  
    cout << "*p contains " << *p << endl;

    //TASK 11
    *p = -2763;  
    cout << "p points to where " << *p << " is stored\n";  
    cout << "*p now contains " << *p << endl;  
    cout << "x now contains " << x << endl;

    //TASK 12
    int y(13);      
    cout << "y contains " << y << endl;      
    p = &y;      
    cout << "p now points to where " << *p << " is stored\n";      
    cout << "*p now contains " << *p << endl;      
    *p = 980;      
    cout << "p points to where " << *p << " is stored\n";      
    cout << "*p now contains " << *p << endl;      
    cout << "y now contains " << y << endl;

    //TASK 13
    int* q;      
    q = p;      
    cout << "q points to where " << *q << " is stored\n";      
    cout << "*q contains " << *q << endl;

    //TASK 14
    double d(33.44);      
    double* pD(&d);      
    *pD = *p;      
    *pD = 73.2343;      
    *p  = *pD;      
    *q  = *p;      
    //pD  = p;
    //p   = pD;

    //TASK 15
    int joe = 24;  
    const int sal = 19;    
    int*  pI;  
    pI = &joe;  
    *pI = 234;  
    //pI = &sal;    --------------------> A const variable cannot change
    *pI = 7623;    

    //Point to a variable, don't change the value of the variable
    const int* pcI;
    pcI = &joe;  
    //*pcI = 234;   --------------------> Cannot modify pcI because it is const
    pcI = &sal;  
    //*pcI = 7623;  --------------------> Cannot modify pcI because it is const

    //Point to a variable, be allowed to change the value, but never point away from the variable
    //int* const cpI;   ----------------> Requires an initializer
    int* const cpI(&joe);
    //int* const cpI(&sal); ------------> int* const points to an address of a modifiable int
    //cpI = &joe;   --------------------> cpI is a const pointer to an address; cannot be modified 
    *cpI = 234;  
    //cpI = &sal;   --------------------> cpI is a const pointer to an address; cannot be modified
    *cpI = 7623;    

    //Point to a variable, never change the value of the variable, and never point away from the variable
    //const int* const cpcI;    --------> Requires an initializer
    const int* const cpcI(&joe);
    //const int* const cpcI(&sal); -----> This works, commenting out to run code
    //cpcI = &joe;  
    //*cpcI = 234;  
    //cpcI = &sal;  
    //*cpcI = 7623;  

    //TASK 16
    Complex c = {11.23, 45.67};
    Complex* pC(&c);
    //cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl;
    //--> * has a lower precedence than the . 
    //cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

    //TASK 17
    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;

    //TASK 18
    PlainOldClassV2 poc2;
    PlainOldClassV2* ppoc2( &poc2 );
    cout << ppoc2->getX() << endl;
    ppoc2->setX( 2837 );
    cout << ppoc->getX() << endl;

    //TASK 19
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;
    cout << "The " << *pDyn
         << " is stored at address " << pDyn
         << " which is in the heap\n";

    //TASK 20
    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;
    cout << "The 17 might STILL be stored at address " << pDyn << " even though we deleted pDYn\n";
    cout << "But can we dereference pDyn? We can try. This might crash... " << *pDyn << ". Still here?\n";

    //TASK 21
    pDyn = nullptr;
    cout << "Set pDyn to nullptr... " << pDyn << endl;
    double* pDouble = nullptr;

    //TASK 22
    //cout << "Can we dereference nullptr?  " << *pDyn << endl;      
    //cout << "Can we dereference nullptr?  " << *pDouble << endl;

    //TASK 23
    //"this" can point to a nullptr because it is always point to some object

    //TASK 24
    double* pTest = new double(12);      
    delete pTest;      
    pTest = nullptr;      
    delete pTest; // safe

    //TASK 25
    short* pShrt = new short(5);      
    delete pShrt;      
    //delete pShrt;

    //TASK 26
    long jumper = 12238743;      
    //delete jumper;    ----------------> Can only delete from the heap
    long* ptrTolong = &jumper;      
    //delete ptrTolong;        
    Complex cmplx;      
    //delete cmplx;     ----------------> Can only delete from the heap

    //TASK 27
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        tmpPCmplx = new Complex; // create a new Complex object on the heap
        tmpPCmplx->real = ndx;   // set real and img to be the
        tmpPCmplx->img  = ndx;   // value of the current ndx
        complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }      
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {         
        cout << complV[ ndx ]->real << endl;         
        cout << complV[ ndx ]->img  << endl;      
    }      
    // release the heap space pointed at by the pointers in the vector      
    for (size_t ndx = 0; ndx < 3; ++ndx) {         
        delete complV[ndx];
    }      
    // clear the vector      
    complV.clear(); 
   
    //TASK 28
    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;
    Colour* newColour;

    while (cin >> inputName >> inputR >> inputG >> inputB) {
        //colours.push_back(new Colour(inputName, inputR, inputG, inputB));
        newColour = new Colour(inputName, inputR, inputG, inputB);
        colours.push_back(newColour);
    }
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
    }
    delete(newColour);

    //TASK 29
    Amplifier boomBox;
    SpeakerSystem leftRightSpeakers, upDownSpeakers;
    boomBox.attachSpeakers(leftRightSpeakers);    
    boomBox.attachSpeakers(upDownSpeakers);
    boomBox.playMusic();
    boomBox.detachSpeakers();
    boomBox.playMusic();

    //TASK 30
    // write code to model two people in this world       
    Person joeBob("Joe Bob"), billyJane("Billy Jane"), roomba("Roomba the Roomie");       

    // now model these two becoming roommates 
    joeBob.movesInWith(billyJane);
    roomba.movesInWith(joeBob);

    // did this work out?       
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
    //cout << roomba.getName() << " lives with " << roomba.getRoomiesName() << endl;
}