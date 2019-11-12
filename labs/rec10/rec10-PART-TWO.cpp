/* 
    rec10-PART-TWO.cpp
    Herman Lin
*/

#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
    Instrument ();

    virtual void makeSound() const = 0;
    virtual void play() const = 0;
private:
};
/* ================= */
/* BRASS INSTRUMENTS */
/* ================= */
class Brass : public Instrument {
public:
    Brass (unsigned);

    void makeSound() const;
private:
    unsigned mouthPiece;
};

class Trumpet : public Brass {
public:
    Trumpet (unsigned);

    void play() const;
};

class Trombone : public Brass {
public:
    Trombone (unsigned);
    
    void play() const;
};

/* ================== */
/* STRING INSTRUMENTS */
/* ================== */
class String : public Instrument {
public:
    String (unsigned);
    
    void makeSound() const;
private:
    unsigned stringPitch;
};

class Violin : public String {
public:
    Violin (unsigned);

    void play() const;
};

class Cello : public String {
public:
    Cello (unsigned);

    void play() const;
};

/* ====================== */
/* PERCUSSION INSTRUMENTS */
/* ====================== */
class Percussion : public Instrument {
public:
    Percussion ();

    void makeSound() const;
};

class Drum : public Percussion {
public:
    Drum ();

    void play() const;
};

class Cymbal : public Percussion {
public:
    Cymbal ();

    void play() const;
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

    void orchPlay() const {
        if (instr) instr->play();
    }
private:
    Instrument* instr;
};

/* ========= */
/* ORCHESTRA */
/* ========= */
class Orch {
public:
    Orch ();

    void play() const;
    void addPlayer(Musician&);
private:
    vector<Musician*> orchestra;
};

// PART TWO
int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

} // main

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

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}

/* BRASS FUNCTIONALITY */
Brass::Brass (unsigned size) : mouthPiece(size) {}

void Brass::makeSound() const {
    Instrument::makeSound();
    cout << "blow on a mouthpiece of size "
         << mouthPiece << endl;
}

/* TRUMPET FUNCTIONALITY */
Trumpet::Trumpet (unsigned size) : Brass(size) {}

void Trumpet::play() const { cout << "Toot"; }

/* TROMBONE FUNCTIONALITY */
Trombone::Trombone (unsigned size) : Brass(size) {}

void Trombone::play() const { cout << "Blat"; }

/* STRING FUNCTIONALITY */
String::String (unsigned pitch) : stringPitch(pitch) {}

void String::makeSound() const {
    Instrument::makeSound();
    cout << "bow a string with pitch "
         << stringPitch << endl;
}

/* VIOLIN FUNCTIONALITY */
Violin::Violin (unsigned pitch) : String(pitch) {}

void Violin::play() const { cout << "Screech"; }

/* CELLO FUNCTIONALITY */
Cello::Cello (unsigned pitch) : String(pitch) {}

void Cello::play() const { cout << "Squawk"; }

/* PERCUSSION FUNCTIONALITY */
Percussion::Percussion () {}

void Percussion::makeSound() const {
    Instrument::makeSound();
    cout << "hit me!" << endl;
}

/* DRUM FUNCTIONALITY */
Drum::Drum () {}

void Drum::play() const { cout << "Boom"; }

/* CYMBAL FUNCTIONALITY */
Cymbal::Cymbal () {}

void Cymbal::play() const { cout << "Crash"; }

/* ORCHESTRA FUNCTIONALITY */
Orch::Orch () {}

void Orch::play() const {
    for (Musician* performer : orchestra) {
        performer->orchPlay();
    }
    cout << endl;
}

void Orch::addPlayer(Musician& performer) {
    orchestra.push_back(&performer);
}