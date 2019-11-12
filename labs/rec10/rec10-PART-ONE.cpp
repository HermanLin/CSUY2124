/* 
    rec10-PART-ONE.cpp
    Herman Lin
*/

#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
    Instrument ();

    virtual void makeSound() = 0;
private:
};
/* ================= */
/* BRASS INSTRUMENTS */
/* ================= */
class Brass : public Instrument {
public:
    Brass (unsigned);

    void makeSound();
private:
    unsigned mouthPiece;
};

class Trumpet : public Brass {
public:
    Trumpet (unsigned);
};

class Trombone : public Brass {
public:
    Trombone (unsigned);
};

/* ================== */
/* STRING INSTRUMENTS */
/* ================== */
class String : public Instrument {
public:
    String (unsigned);
    
    void makeSound();
private:
    unsigned stringPitch;
};

class Violin : public String {
public:
    Violin (unsigned);
};

class Cello : public String {
public:
    Cello (unsigned);
};

/* ====================== */
/* PERCUSSION INSTRUMENTS */
/* ====================== */
class Percussion : public Instrument {
public:
    Percussion ();

    void makeSound();
};

class Drum : public Percussion {
public:
    Drum ();
};

class Cymbal : public Percussion {
public:
    Cymbal ();
};

/* ================================== */
/* MUSICAL INSTRUMENT LENDING LIBRARY */
/* ================================== */
class MILL {
public:
    MILL ();

    void dailyTestPlay();
    void receiveInstr (Instrument&);
    Instrument* loanOut();
private:
    vector<Instrument*> inventory;
};

/* ======== */
/* MUSICIAN */
/* ======== */
class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << "have no instr\n";
    }

private:
    Instrument* instr;
};


// PART ONE
int main() {

    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
  
    cout << "Daily test -------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	
    cout << "Giving groucho an instrument..." << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << "Testing groucho's instrument..." << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
    
    cout << "groucho.testPlay()..." << endl;
    groucho.testPlay();	
    cout << "Returning groucho's instrument..." << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "mill.dailyTestPlay()..." << endl;
    mill.dailyTestPlay();
    cout << endl;
    cout << "Giving harpo an instrument..." << endl;
    harpo.acceptInstr(mill.loanOut());
    cout << "Giving groucho an instrument..." << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    cout << "groucho.testPlay()..." << endl;
    groucho.testPlay();
    cout << "harpo.testPlay()..." << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
  
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << endl;
}

/* MUSICAL INSTRUMENT LENDING LIBRARY FUNCTIONALITY */
MILL::MILL () {}

void MILL::dailyTestPlay() {
    for (Instrument* instrument : inventory) {
        if (instrument) instrument->makeSound();
    }
}

void MILL::receiveInstr(Instrument& instr) {
    // for (Instrument* instrument : inventory) {
    //     if (!instrument) {
    //         instrument = &instr;
    //         return;
    //     }
    // }

    // check for first empty spot in inventory
    for (size_t cubby = 0; cubby < inventory.size(); ++cubby) {
        if (inventory[cubby] == nullptr) {
            inventory[cubby] = &instr;
            return;
        }
    }
    // push_back if there are no empty slots
    inventory.push_back(&instr);
}

Instrument* MILL::loanOut() {
    for (size_t cubby = 0; cubby < inventory.size(); ++cubby) {
        if (inventory[cubby]) {
            Instrument* instrAddress = inventory[cubby];
            inventory[cubby] = nullptr;
            return instrAddress;
        }
    }
    return nullptr;
}

/* INSTRUMENT FUNCTIONALITY */
Instrument::Instrument () {}

void Instrument::makeSound() {
    cout << "To make a sound... ";
}

/* BRASS FUNCTIONALITY */
Brass::Brass (unsigned size) : mouthPiece(size) {}

void Brass::makeSound() {
    Instrument::makeSound();
    cout << "blow on a mouthpiece of size "
         << mouthPiece << endl;
}

/* TRUMPET FUNCTIONALITY */
Trumpet::Trumpet (unsigned size) : Brass(size) {}

/* TROMBONE FUNCTIONALITY */
Trombone::Trombone (unsigned size) : Brass(size) {}

/* STRING FUNCTIONALITY */
String::String (unsigned pitch) : stringPitch(pitch) {}

void String::makeSound() {
    Instrument::makeSound();
    cout << "bow a string with pitch "
         << stringPitch << endl;
}

/* VIOLIN FUNCTIONALITY */
Violin::Violin (unsigned pitch) : String(pitch) {}

/* CELLO FUNCTIONALITY */
Cello::Cello (unsigned pitch) : String(pitch) {}

/* PERCUSSION FUNCTIONALITY */
Percussion::Percussion () {}

void Percussion::makeSound() {
    Instrument::makeSound();
    cout << "hit me!" << endl;
}

/* DRUM FUNCTIONALITY */
Drum::Drum () {}

/* CYMBAL FUNCTIONALITY */
Cymbal::Cymbal () {}