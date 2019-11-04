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
    Nobles (const string&);

    const string& getName() const;

    bool isDead() const;
    virtual void dies();

    virtual double getStrength() const = 0;
    virtual void setStrength(const double) = 0;

    unsigned getNobleType();
    void setNobleType(unsigned);

    void battle(Nobles&);
    void defeats(Nobles&, const double);

    virtual void battleCry() = 0;
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

    double getStrength() const;
    void setStrength(const double);
    
    bool hires(Protectors&);
    bool fires(Protectors&);
    size_t findProtector(Protectors&);

    void battleCry();
private:
    vector<Protectors*> army;
};

//=============================================//
/* PERSONWITHSTRENGTHTOFIGHT CLASS DEFINITIONS */
//=============================================//
class PersonWithStrengthToFight : public Nobles {
public:
    PersonWithStrengthToFight (const string&, const double);

    void dies();

    double getStrength() const;
    void setStrength(const double);

    void battleCry();
private:
    double strength;
};

//==============================//
/* PROTECTORS CLASS DEFINITIONS */
//==============================//
class Protectors {
public:
    Protectors (const string&, const double);

    const string& getName() const;

    Nobles* getBoss() const;
    void setBoss(Nobles*);

    double getStrength() const;
    void setStrength(const double);

    virtual void battleCry() = 0;
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

    void battleCry();
};

//============================//
/* WARRIORS CLASS DEFINITIONS */
//============================//
class Warriors : public Protectors {
public:
    Warriors (const string&, const double);
};

//==========================//
/* ARCHER CLASS DEFINITIONS */
//==========================//
class Archer : public Warriors {
public:
    Archer (const string&, const double);

    void battleCry();
};

//=============================//
/* SWORDSMAN CLASS DEFINITIONS */
//=============================//
class Swordsman : public Warriors {
public:
    Swordsman (const string&, const double);

    void battleCry();
};

//=============//
/* TESTER CODE */
//=============//
int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);

    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	

    joe.battle(randy);	
    joe.battle(sam);	

    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	

    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    janet.battle(barclay);	
    janet.hires(samantha);	

    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);

    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    
    janet.battle(barclay);	
    sam.battle(barclay);	
    joe.battle(barclay);
}

//============================//
/* NOBLES CLASS FUNCTIONALITY */
//============================//
Nobles::Nobles (const string& name)
    : name(name), dead(false)
{}

const string& Nobles::getName() const { return name; }

bool Nobles::isDead() const { return dead; }

void Nobles::dies() { dead = true; }

void Nobles::battle(Nobles& opponent) {
    cout << name << " battles " << opponent.getName() << endl;
    
    // if either Noble is dead...
    if (dead || opponent.isDead()) {
        // if both Nobles are dead...
        if (dead && opponent.isDead()) {
            cout << "Oh NO! They're both dead! Yuck!" << endl;
        }
        // if this Noble is dead...
        else if (dead) {
            cout << "He's dead, " << opponent.getName() << endl;
        }
        // if opponent is dead...
        else {
            cout << "He's dead, " << name << endl;
        }
    }
    else {
        // print out respective battlecries...
        battleCry();
        opponent.battleCry();

        // get the strength of each Noble (army or self)
        double thisStrength = getStrength();
        double opponentStrength = opponent.getStrength();
        // and set the default ratio to 1
        double ratio = 1;

        // if the strengths are equal...
        if (thisStrength == opponentStrength) {
            cout << "Mutual Annihilation: "
                 << name << " and " << opponent.getName()
                 << " die at each other's hands" << endl;
            dies();
            opponent.dies();
            setStrength(ratio);
            opponent.setStrength(ratio);
        }
        // if this Noble is stronger...
        else if (thisStrength > opponentStrength) {
            ratio = opponentStrength / thisStrength;
            defeats(opponent, ratio);
        }
        // if the opponent is stronger...
        else {
            ratio = thisStrength / opponentStrength;
            opponent.defeats(*this, ratio);
        }
    }
}

void Nobles::defeats(Nobles& opponent, const double ratio) {
    cout << name << " defeats " << opponent.getName() << endl;
    setStrength(ratio);
    opponent.dies();
    opponent.setStrength(1);
}

//==========================//
/* LORD CLASS FUNCTIONALITY */
//==========================//
Lord::Lord (const string& name)
    : Nobles(name)
{}

double Lord::getStrength() const {
    double totalStr = 0;
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

bool Lord::hires(Protectors& mercenary) {
    // if the Lord is dead...
    if (isDead()) { return false; }
    // if the Protector already has a boss...
    else if (mercenary.getBoss()) { return false; }
    // if the Protector is dead...
    else if (!mercenary.getStrength()) { return false; }
    else {
        mercenary.setBoss(this);
        army.push_back(&mercenary);
        return true;
    }
}

bool Lord::fires(Protectors& layoff) {
    // if the Lord is dead...
    if (isDead()) { return false; }
    // if the Lord is not the Protector's Lord...
    else if (layoff.getBoss() != this) { 
        cout << layoff.getName() << " does not belong to " << getName() << endl;
        return false;
    }
    else {
        size_t protectorIndex = findProtector(layoff);
        cout << "You don't work for me anymore " << layoff.getName()
             << " -- " << getName() << "." << endl;
        layoff.setBoss(nullptr);
        // need to maintain the order of the army...
        for (size_t index = protectorIndex; index < army.size(); ++index) {
            army[index] = army[index + 1];
        }
        army.pop_back();
        return true;
    }
}

size_t Lord::findProtector(Protectors& protector) {
    for (size_t index = 0; index < army.size(); ++index) {
        if (army[index] == &protector) {
            return index;
        }
    }
    return army.size();
}

void Lord::battleCry() {
    for (Protectors* protector : army) {
        protector->battleCry();
    }
}

//===============================================//
/* PERSONWITHSTRENGTHTOFIGHT CLASS FUNCTIONALITY */
//===============================================//
PersonWithStrengthToFight::PersonWithStrengthToFight (const string& name, const double strength)
    : Nobles(name), strength(strength)
{}

void PersonWithStrengthToFight::dies() {
    Nobles::dies();
    setStrength(1);
}

double PersonWithStrengthToFight::getStrength() const { return strength; }

void PersonWithStrengthToFight::setStrength(const double ratio) {
    strength *= (1 - ratio);
}

void PersonWithStrengthToFight::battleCry() {
    cout << "UGH!!!" << endl;
}

//================================//
/* PROTECTORS CLASS FUNCTIONALITY */
//================================//
Protectors::Protectors (const string& name, const double strength)
    : name(name), strength(strength), boss(nullptr)
{}

const string& Protectors::getName() const { return name; }

Nobles* Protectors::getBoss() const { return boss; }

void Protectors::setBoss(Nobles* newBoss) { boss = newBoss; }

double Protectors::getStrength() const { return strength; }

void Protectors::setStrength(const double ratio) {
    strength *= (1 - ratio);
}

//============================//
/* WIZARD CLASS FUNCTIONALITY */
//============================//
Wizard::Wizard (const string& name, const double strength)
    : Protectors(name, strength)
{}

void Wizard::battleCry() {
    cout << "POOF" << endl;
}

//==============================//
/* WARRIORS CLASS FUNCTIONALITY */
//==============================//
Warriors::Warriors (const string& name, const double strength)
    : Protectors(name, strength)
{}

//============================//
/* ARCHER CLASS FUNCTIONALITY */
//============================//
Archer::Archer (const string& name, const double strength)
    : Warriors(name, strength)
{}

void Archer::battleCry() {
    cout << "TWANG! " << getName()
         << " says: Take that in the name of my lord, "
         << getBoss()->getName() << endl;
}

//===============================//
/* SWORDSMAN CLASS FUNCTIONALITY */
//===============================//
Swordsman::Swordsman (const string& name, const double strength)
    : Warriors(name, strength)
{}

void Swordsman::battleCry() {
    cout << "CLANG! " << getName()
         << " says: Take that in the name of my lord, "
         << getBoss()->getName() << endl;
}