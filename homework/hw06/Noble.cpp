/* 
    NOBLE SOURCE FILE
    Herman Lin
*/

#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {

    // ========================= //
    // Noble Class Functionality //
    // ========================= //
    ostream& operator<<(ostream& os, const Noble& rhs) {
        os << rhs.name << " has an army of " << rhs.army.size() << endl;
        for (Warrior* warror : rhs.army) {
            os << "\t" << *warror;
        }
        return os;
    }

    Noble::Noble(const string& name) 
        : name(name) 
    { dead = false; }

    const string& Noble::getName() const { return name; }

    bool Noble::isDead() const { return dead; }

    void Noble::dies() { dead = true; }

    bool Noble::hire(Warrior& mercenary) {
        if (dead) { return false; }
        else if (mercenary.isHired()) { return false; }
        else {
            mercenary.setBoss(this);
            army.push_back(&mercenary);
            return true;
        }
    }

    bool Noble::fire(Warrior& layoff) {
        if (dead) { return false; }
        else if (layoff.getBoss() != this) {
            cout << layoff.getName() << " does not belong to " << name << endl;
            return false;
        }
        else {
            size_t warriorIndex = findWarrior(layoff);
            cout << "You don't work for me anymore " << layoff.getName()
                << " -- " << name << "." << endl;
            layoff.setBoss(nullptr);
            for (size_t index = warriorIndex; index < army.size(); ++index) {
                army[index] = army[index + 1];
            }
            army.pop_back();
            return true;
        }
    }

    void Noble::deserter(Warrior& escapee) {
        size_t warriorIndex = findWarrior(escapee);
        for (size_t index = warriorIndex; index < army.size(); ++index) {
            army[index] = army[index + 1];
        }
        army.pop_back();
    }

    void Noble::battle(Noble& opponent) {
        cout << name << " battles " << opponent.getName() << endl;
        //if either is dead...
        if (dead || opponent.isDead()) {
            //if both are dead...
            if (dead && opponent.isDead()) {
                cout << "Oh NO! They're both dead! Yuck!" << endl;
            }
            //if this is dead...
            else if (dead) {
                cout << "He's dead, " << opponent.getName() << endl;
            }
            //if the opponent is dead...
            else {
                cout << "He's dead, " << name << endl;
            }
        }
        else {
            //get the strengths of each army and set the default ratio to 1
            double thisStrength = getArmyStrength();
            double opponentStrength = opponent.getArmyStrength();
            double ratio = 1;

            //if the strengths are equal...
            if (thisStrength == opponentStrength) {
                cout << "Mutual Annihilation: "
                     << name << " and " << opponent.getName()
                     << " die at each other's hands" << endl;
                dies();
                opponent.dies();
                setArmyStrength(ratio);
                opponent.setArmyStrength(ratio);
            }
            //if this is stronger...
            else if (thisStrength > opponentStrength) {
                ratio = opponentStrength / thisStrength;
                defeats(opponent, ratio);
            }
            //if the opponent is stronger...
            else {
                ratio = thisStrength / opponentStrength;
                opponent.defeats(*this, ratio);
            }
        }

    }

    int Noble::getArmyStrength() const {
        double totalStr = 0;
        for (Warrior* warrior : army) {
            totalStr += warrior->getStrength();
        }
        return totalStr;
    }

    void Noble::setArmyStrength(const double ratio) {
        for (Warrior* warrior : army) {
            warrior->setStrength(ratio);
        }
    }

    void Noble::defeats(Noble& opponent, const double ratio) {
        cout << name << " defeats " << opponent.getName() << endl;
        setArmyStrength(ratio);
        opponent.dies();
        opponent.setArmyStrength(1);
    }

    size_t Noble::findWarrior(Warrior& warrior) {
        for (size_t index = 0; index < army.size(); ++index) {
            if (army[index] == &warrior) {
                return index;
            }
        }
        return army.size();
    }
    
}