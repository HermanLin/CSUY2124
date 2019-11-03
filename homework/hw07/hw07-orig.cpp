/* 
    hw07-orig.cpp
    Herman Lin 
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pre-declared classses //
class Protectors;

//==========================//
/* NOBLES CLASS DEFINITIONS */
//==========================//
class Nobles {
public:
    Nobles (const string&);
    
    const string& getName() const;
    void battle(Nobles&);
protected:
    virtual double getStrength() const = 0;
    virtual void setStrength(const double) = 0;
    virtual void dies();
    //virtual const vector<Protectors*>& getArmy() const;

    unsigned getNobleType() const;
    void setNobleType(unsigned);

    bool isDead() const;
    void defeats(Nobles&, const double);
private:
    // nobleType
    //  = 0, has no army
    //  = 1, has an army
    unsigned nobleType;
    string name;
    bool dead;
};

//========================//
/* LORD CLASS DEFINITIONS */
//========================//
class Lord : public Nobles {
public:
    Lord (const string&);

    void dies(); 
    double getStrength() const;
    void setStrength(const double);
    bool hires(Protectors&);
    const vector<Protectors*>& getArmy() const;
private:
    vector<Protectors*> army;
};

//=============================================//
/* PERSONWITHSTRENGTHTOFIGHT CLASS DEFINITIONS */
//=============================================//
class PersonWithStrengthToFight : public Nobles {
public:
    PersonWithStrengthToFight (const string&, double);

    void dies();
    double getStrength() const;
    void setStrength(const double);
private:
    double strength;
};

//==============================//
/* PROTECTORS CLASS DEFINITIONS */
//==============================//
class Protectors {
public:
    Protectors (const string&, double);
    virtual void exclaim() = 0;
    
    const string& getName() const;
    Nobles* getBoss() const;
    void setBoss(Nobles*);
    double getStrength() const;
    void setStrength(const double);
private:
    string name;
    double strength;
    Nobles* boss;
};

//==========================//
/* WIZARD CLASS DEFINITIONS */
//==========================//
class Wizard : public Protectors {
public:
    Wizard (const string&, double);

    void exclaim();
private:
};

//============================//
/* WARRIORS CLASS DEFINITIONS */
//============================//
class Warriors : public Protectors {
public:
    Warriors (const string&, double);
private:
};

//==========================//
/* ARCHER CLASS DEFINITIONS */
//==========================//
class Archer : public Warriors {
public:
    Archer (const string&, double);

    void exclaim();
private:
};

//=============================//
/* SWORDSMAN CLASS DEFINITIONS */
//=============================//
class Swordsman : public Warriors {
public:
    Swordsman (const string&, double);

    void exclaim();
private:
};

//=============//
/* TESTER CODE */
//=============//
int main() {
    cout << "tester code..." << endl;
    // Lord sam("Sam");
    // Archer samantha("Samantha", 200);
    // sam.hires(samantha);

    // Lord joe("Joe");
    // PersonWithStrengthToFight randy("Randolf the Elder", 250); 	

    // cout << "battles..." << endl;
    // joe.battle(randy);	
    // joe.battle(sam);	

    // Lord janet("Janet");	
    // Swordsman hardy("TuckTuckTheHardy", 100);
    // Swordsman stout("TuckTuckTheStout", 80);
    // janet.hires(hardy);	
    // janet.hires(stout);	

    // PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    // janet.battle(barclay);	
    // janet.hires(samantha);	

    // Archer pethora("Pethora", 50);	
    // Archer thora("Thorapleth", 60);
    // Wizard merlin("Merlin", 150);

    // janet.hires(pethora);
    // janet.hires(thora);
    // sam.hires(merlin);

    // janet.battle(barclay);	
    // sam.battle(barclay);	
    // joe.battle(barclay);
}


//======================//
/* NOBLES FUNCTIONALITY */
//======================//
Nobles::Nobles (const string& name)
    : name(name)
{ dead = false; }

const string& Nobles::getName() const { return name; }

unsigned Nobles::getNobleType() const { return nobleType; }

void Nobles::setNobleType(unsigned type) { nobleType = type; }

bool Nobles::isDead() const { return dead; }

void Nobles::dies() { dead = true; }

// const vector<Protectors*>& Nobles::getArmy() const {}

// void Nobles::battle(Nobles& opponent) {
//     cout << name << " battles " << opponent.getName() << endl;
//     // determine if a Noble is a lord and print their army's exclamations...
//     if (getNobleType()) {
//         vector<Protectors*> army = getArmy();
//         for (Protectors* protector : army) {
//             protector->exclaim();
//         }
//     }
//     if (opponent.getNobleType()) {
//         vector<Protectors*> army = getArmy();
//         for (Protectors* protector : army) {
//             protector->exclaim();
//         }
//     }

//     // if either Noble is dead...
//     if (dead || opponent.isDead()) {
//         // if both Nobles are dead...
//         if (dead && opponent.isDead()) {
//             cout << "Oh NO! They're both dead! Yuck!" << endl;
//         }
//         // if this Noble is dead...
//         else if (dead) {
//             cout << "He's dead, " << opponent.getName() << endl;
//         }
//         // if opponent is dead...
//         else {
//             cout << "He's dead, " << name << endl;
//         }
//     }
//     else {
//         // get the strength of each Noble (army or self)
//         double thisStrength = getStrength();
//         double opponentStrength = opponent.getStrength();
//         // and set the default ratio to 1
//         double ratio = 1;

//         // if the strengths are equal...
//         if (thisStrength == opponentStrength) {
//             cout << "Mutual Annihilation: "
//                  << name << " and " << opponent.getName()
//                  << " die at each other's hands" << endl;
//             dies();
//             opponent.dies();
//             setStrength(ratio);
//             opponent.setStrength(ratio);
//         }
//         // if this Noble is stronger...
//         else if (thisStrength > opponentStrength) {
//             ratio = opponentStrength / thisStrength;
//             defeats(opponent, ratio);
//         }
//         // if the opponent is stronger...
//         else {
//             ratio = thisStrength / opponentStrength;
//             opponent.defeats(*this, ratio);
//         }
//     }
// }

// void Nobles::defeats(Nobles& opponent, const double ratio) {
//     cout << name << " defeats " << opponent.getName() << endl;
//     setStrength(ratio);
//     opponent.dies();
//     opponent.setStrength(1);
// }

//====================//
/* LORD FUNCTIONALITY */
//====================//
Lord::Lord (const string& name) 
    : Nobles(name) 
{ setNobleType(1); }

void Lord::dies() { Nobles::dies(); }

double Lord::getStrength() const {
    double totalStr;
    for (Protectors* protector : army) {
        totalStr += protector->getStrength();
    }
    return totalStr;
}

void Lord::setStrength(const double ratio) {
    for (Protectors* protector : army) {
        protector->setStrength(ratio);
    }
}

bool Lord::hires (Protectors& mercenary) {
    // if the Lord is dead...
    if (isDead()) { return false; }
    // if the Protector already has a boss...
    else if (mercenary.getBoss()) { return false; }
    else {
        mercenary.setBoss(this);
        army.push_back(&mercenary);
        return true;
    }
}

const vector<Protectors*>& Lord::getArmy() const { return army; }

//=========================================//
/* PERSONWITHSTRENGTHTOFIGHT FUNCTIONALITY */
//=========================================//
PersonWithStrengthToFight::PersonWithStrengthToFight (const string& name, double strength)
    : Nobles(name), strength(strength)
{ setNobleType(0); }

double PersonWithStrengthToFight::getStrength() const { return strength; }

void PersonWithStrengthToFight::setStrength(const double ratio) {
    strength *= (1 - ratio);
}

void PersonWithStrengthToFight::dies() {
    Nobles::dies();
    setStrength(1);
}

//==========================//
/* PROTECTORS FUNCTIONALITY */
//==========================//
Protectors::Protectors (const string& name, double strength)
    : name(name), strength(strength)
{}

const string& Protectors::getName() const { return name; }

Nobles* Protectors::getBoss() const { return boss; }

void Protectors::setBoss(Nobles* newBoss) { boss = newBoss; }

double Protectors::getStrength() const { return strength; }

void Protectors::setStrength(const double ratio) {
    strength *= (1 - ratio);
}

//======================//
/* WIZARD FUNCTIONALITY */
//======================//
Wizard::Wizard (const string& name, double strength)
    : Protectors(name, strength)
{}

void Wizard::exclaim() {
    cout << "POOF" << endl;
}

//========================//
/* WARRIORS FUNCTIONALITY */
//========================//
Warriors::Warriors (const string& name, double strength)
    : Protectors(name, strength)
{}

//======================//
/* ARCHER FUNCTIONALITY */
//======================//
Archer::Archer (const string& name, double strength)
    : Warriors(name, strength)
{}

void Archer::exclaim() {
    cout << "TWANG! " << getName()
         << "says: Take that in the name of my lord, "
         << getBoss()->getName() << endl;
}

//=========================//
/* SWORDSMAN FUNCTIONALITY */
//=========================//
Swordsman::Swordsman (const string& name, double strength)
    : Warriors(name, strength)
{}

void Swordsman::exclaim() {
    cout << "CLANG! " << getName()
         << "says: Take that in the name of my lord, "
         << getBoss()->getName() << endl;
}