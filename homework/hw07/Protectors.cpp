/* 
    PROTECTORS SOURCE FILE
    Herman Lin
*/

#include "Protectors.h"
#include "Nobles.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
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
}