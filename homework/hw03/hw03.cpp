/*======================================================
hw03.cpp
Herman Lin

This file is a variation of the warrior battle simulator
in the previous homework. This time, each warrior will
be born with a weapon that has a strength attribute.
When a warrior battles another warrior, the winner of
the fight will be the warrior with the stronger weapon.
The winner's weapon will lose strength based on the
strength of their opponent's weapon and the loser's
weapon will break, meaning the warrior dies.
Warriors that fight with the same strength weapon will
both break their weapons and die.
======================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*====================================
Warrior Class, Weapon Private Subclass
- Contains the name of a Warrior and the weapon of a warrior
- Has a battle method for fighting between warriors
====================================*/
class Warrior {
private:
    class Weapon {
    private:
        string _name;
        int _strength;
        
    public:
        Weapon (const string& weaponName, int weaponStrength)
            : _name(weaponName), _strength(weaponStrength)
        {}

        friend ostream& operator<<(ostream& os, const Weapon& weapon) {
            os << "weapon: " << weapon._name << ", " << weapon._strength;
            return os;
        }

        const string& getName () const { return _name; }
        int getStrength () const { return _strength; }
        
        void setStrength (int newStrength) { _strength = newStrength; }
        void subStrength (int strength) { _strength -= strength; }
    };
    
    string _name;
    Weapon _stabber;

public:
    Warrior (const string& warriorName, const string& weaponName, int weaponStrength)
        : _name(warriorName), _stabber(weaponName, weaponStrength)
    {}

    friend ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << "Warrior: " << warrior._name << ", " << warrior._stabber;
        return os;
    }

    const string& getName () const { return _name; }
    Weapon& getWeapon () { return _stabber; }
    
    /*==============================================================
    Battle Method
    - Simulates a fight between this warrior and an opponent warrior
    - Sets their weaponStrengths accordingly
    ==============================================================*/
    void battles (Warrior& opponent) {
        cout << _name << " battles " << opponent.getName() << endl;
        if (_stabber.getStrength() ==0 || opponent.getWeapon().getStrength() == 0){
            //if both warriors have a weapon strength of 0...
            if (_stabber.getStrength() == 0 && opponent.getWeapon().getStrength() == 0) {
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
            //if one warrior has a weapon strength of 0...
            else if (_stabber.getStrength() == 0) {
                cout << "He's dead, " << opponent.getName() << endl;
            }
            else if (opponent.getWeapon().getStrength() == 0) {
                cout << "He's dead, " << _name << endl;
            }
        }
        //if this warrior has a stronger weapon...
        else if (_stabber.getStrength() > opponent.getWeapon().getStrength()) {
            cout << _name << " defeats " << opponent.getName() << endl;
            _stabber.subStrength(opponent.getWeapon().getStrength());
            opponent.getWeapon().setStrength(0);
        }
        //if the opponent has a stronger weapon...
        else if (_stabber.getStrength() < opponent.getWeapon().getStrength()) {
            cout << opponent.getName() << " defeats " << _name << endl;;
            opponent.getWeapon().subStrength(_stabber.getStrength());
            _stabber.setStrength(0);
        }
        //if both warriors have the same weapon strength...
        else if (_stabber.getStrength() == opponent.getWeapon().getStrength()) {
            cout << "Mutual Annihilation: "
            << _name << " and " << opponent.getName() << " die at each other's hands" << endl;
            _stabber.setStrength(0);
            opponent.getWeapon().setStrength(0);
        }
    }
};

void openBattleLog(ifstream& stream);
size_t findWarrior(const vector<Warrior>& Warriors, const string& name);
void status(const vector<Warrior>& Warriors);

int main() {
    ifstream battleLog;
    vector<Warrior> Warriors;
    openBattleLog(battleLog);

    /*=================================================================
    Parse through "warriors.txt" by command
    Warrior = create a new warrior with the following name and strength
    Status = display all warriors present
    Battle = simulate a fight between the following two warriors
    =================================================================*/
    string command, warriorName, weaponName, warriorName1, warriorName2;
    int weaponStrength;
    size_t indexOfWarrior1, indexOfWarrior2;
    while (battleLog >> command) {
        if (command == "Warrior") {
            battleLog >> warriorName >> weaponName >> weaponStrength;
            Warriors.emplace_back(warriorName, weaponName, weaponStrength);
        }
        else if (command == "Status") {
            status(Warriors);
        }
        else if (command == "Battle") {
            battleLog >> warriorName1 >> warriorName2;
            indexOfWarrior1 = findWarrior(Warriors, warriorName1);
            indexOfWarrior2 = findWarrior(Warriors, warriorName2);
            Warriors[indexOfWarrior1].battles(Warriors[indexOfWarrior2]);
        }
    }
    battleLog.close();
}

/*==================
File Opener Function
- Read for a 'warriors.txt' to open from the ifstream 
==================*/
void openBattleLog(ifstream& stream) {
    stream.open("warriors.txt");
    if(!stream) {
        cerr << "Could not find 'warriors.txt'" << endl;
        exit(1);
    }
}

/*=====================
Warrior Search Function
- Finds and returns the index of the Warrior
=====================*/
size_t findWarrior(const vector<Warrior>& Warriors, const string& name) {
    //Loop through the Warrior vector till the name is found
    for (size_t i = 0; i < Warriors.size(); i++) {
        if (Warriors[i].getName() == name) {
            return i;
            break;
        }
    }
}

/*=====================
Warrior Status Function
- Displays all warriors in the battle and their strength
=====================*/
void status(const vector<Warrior>& Warriors) {
    cout << "There are " << Warriors.size() << " warriors" << endl;
    for (const Warrior& warrior : Warriors) {
        cout << warrior << endl;
    }
}