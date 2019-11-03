/* 
    hw07.cpp
    Herman Lin
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pre-declared Classes //
class Protectors;

//==========================//
/* NOBLES CLASS DEFINITIONS */
//==========================//
class Nobles {
public:
    Nobles (const string& name)
        : name(name)
    {}
protected: //Protectors do not need to have access to these methods
    bool isDead() const;
private:
    string name;
    bool dead;
};

//========================//
/* LORD CLASS DEFINITIONS */
//========================//
class Lord : public Nobles {
public:
    Lord (const string&);

    bool hires(Protectors&);
private:
    vector<Protectors*> army;
};

//=============================================//
/* PERSONWITHSTRENGTHTOFIGHT CLASS DEFINITIONS */
//=============================================//
class PersonWithStrengthToFight : public Nobles {
public:
    PersonWithStrengthToFight (const string&, const double);
private:
    double strength;
};

//==============================//
/* PROTECTORS CLASS DEFINITIONS */
//==============================//
class Protectors {
public:
    Protectors (const string&, const double);

    Nobles* getBoss() const;
    void setBoss(Nobles*);
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
    Wizard (const string&, const double);
private:
};

//============================//
/* WARRIORS CLASS DEFINITIONS */
//============================//
class Warriors : public Protectors {
public:
    Warriors (const string&, const double);
private:
};

//==========================//
/* ARCHER CLASS DEFINITIONS */
//==========================//
class Archer : public Warriors {
public:
    Archer (const string&, const double);
private:
};

//=============================//
/* SWORDSMAN CLASS DEFINITIONS */
//=============================//
class Swordsman : public Warriors {
public:
    Swordsman (const string&, const double);
private:
};

//=============//
/* TESTER CODE */
//=============//
int main() {
    cout << "testing" << endl;
    // Lord sam("Sam");
    // Archer samantha("Samantha", 200);
    // sam.hires(samantha);

    // Lord joe("Joe");
    // PersonWithStrengthToFight randy("Randolf the Elder", 250); 	

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