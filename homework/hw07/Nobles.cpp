/* 
    NOBLES SOURCE FILE
    Herman Lin
*/

#include "Nobles.h"
#include "Protectors.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {
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
}