/* 
    WARRIOR SOURCE FILE
    Herman Lin
*/

#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {

    // =========================== //
    // Warrior Class Functionality //
    // =========================== //
    ostream& operator<<(ostream& os, const Warrior& rhs) {
        os << rhs.name << ": " << rhs.strength << endl;
        return os;
    }

    Warrior::Warrior(const string& name, const double strength)
        : name(name), strength(strength), boss(nullptr)
    {}

    const string& Warrior::getName() const { return name; }

    double Warrior::getStrength() const { return strength; }

    Noble* Warrior::getBoss() const { return boss; }

    bool Warrior::isHired() const { return boss != nullptr; }

    void Warrior::setStrength(const double ratio) {
        strength *= (1 - ratio);
    }
    void Warrior::setBoss(Noble* newBoss) { boss = newBoss; }

    void Warrior::runaway() {
        if (boss) {
            cout << name << " flees in terror, abandoning his lord, "
                << boss->getName() << endl;
            boss->deserter(*this);
            boss = nullptr;
        }
    }

}