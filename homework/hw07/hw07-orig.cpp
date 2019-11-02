/* 
    hw07-orig.cpp
    Herman Lin 
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Nobles {
public:
    // virtual bool hire(Protectors& mercenary) = 0;
private:
    string name;
    bool dead;
};

class Lord : public Nobles {
public:
private:
    vector<Protectors*> army;
};

class PersonWithStrengthToFight : public Nobles {
public:
private:
    double strength;
};

class Protectors {
public:
private:
    double strength;
    Nobles* boss;
};

class Wizards : public Protectors {
public:
private:
};

class Warriors : public Protectors {
public:
private:
};

class Archer : public Warriors {
public:
private:
};

class Swordsman : public Warriors {
public:
private:
};

int main() {
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