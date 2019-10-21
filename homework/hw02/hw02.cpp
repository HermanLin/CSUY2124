/*===============================================================
hw02.cpp
Herman Lin

This file will simulate warriors battling each other.
Each warrior will have a name and a strength value.
When a warrior battles another, the winner will be the warrior
with a higher strength value. Then, the strength of the loser's
will be subtracted from the strength of the winner's. The 
loser will also lose all of their strength.
When warriors with the same strength battle, they will both lose.
===============================================================*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

/*============
Warrior Struct
- gladiator: name of the warrior
- strength: strength of the warrior 
============*/
struct Warrior {
    string gladiator;
    int strength;
};

//Prototypes
void openBattleLog(ifstream& stream);
void addWarrior(vector<Warrior>& Warriors, const string& warriorName, int warriorStrength);
size_t findWarrior(const vector<Warrior>& Warriors, const string& name);
void battle(Warrior& warrior1, Warrior& warrior2);
void status(const vector<Warrior>& Warriors);

int main(){
    //Create an ifstream variable for reading the file
    ifstream battleLog;
    //Vector containing all warriors
    vector<Warrior> Warriors;
    
    //Attempt to read the stream for "warriors.txt"
    openBattleLog(battleLog);
    
    /*
    Parse through "warriors.txt" by command
    Warrior = create a new warrior with the following name and strength
    Status = display all warriors present
    Battle = simulate a fight between the following two warriors
    */
    size_t indexOfWarrior1, indexOfWarrior2;
    string command, warriorName1, warriorName2;
    int strengthValue;
    while (battleLog >> command) {
        if (command == "Warrior") {
            battleLog >> warriorName1 >> strengthValue;
            addWarrior(Warriors, warriorName1, strengthValue);
        }
        else if (command == "Status") {
            status(Warriors);
        }
        else if (command == "Battle") {
            battleLog >> warriorName1 >> warriorName2;
            indexOfWarrior1 = findWarrior(Warriors, warriorName1);
            indexOfWarrior2 = findWarrior(Warriors, warriorName2);
            battle(Warriors[indexOfWarrior1], Warriors[indexOfWarrior2]);
        }
    }
}

/*==================
File Opener Function
- Read for a specific file to open from the ifstream 
==================*/
void openBattleLog(ifstream& stream) {
    stream.open("warriors.txt");
    if(!stream) {
        cerr << "Could not find 'warriors.txt'" << endl;
        exit(1);
    }
}

/*============================
Warrior Vector Filler Function
- Adds a warrior to a vector of warriors
============================*/
void addWarrior(vector<Warrior>& Warriors, const string& warriorName, int warriorStrength) {
    //Create a new Warrior with the name and strength provided and push it to the Warrior vector
    Warrior newWarrior{warriorName, warriorStrength};
    Warriors.push_back(newWarrior);
}

/*=====================
Warrior Search Function
- Finds and returns the index of the Warrior
=====================*/
size_t findWarrior(const vector<Warrior>& Warriors, const string& name) {
    //Loop through the Warrior vector till the name is found
    for (size_t i = 0; i < Warriors.size(); i++) {
        if (Warriors[i].gladiator == name) {
            return i;
            break;
        }
    }
    return -1;
}

/*=======================
Battle Simulator Function
- Simulates a fight between two Warriors and displays a result
=======================*/
void battle(Warrior& warrior1, Warrior& warrior2) {
    cout << warrior1.gladiator << " battles " << warrior2.gladiator << endl;
    if (warrior1.strength == 0 || warrior2.strength == 0) {
        //if both warriors have a strength of 0...
        if (warrior1.strength == 0 && warrior2.strength == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        //if one warrior has a strength of 0...
        else if (warrior1.strength == 0) {
            cout << "He's dead, " << warrior2.gladiator << endl;
        }
        else if (warrior2.strength == 0) {
            cout << "He's dead, " << warrior1.gladiator << endl;
        }
    }
    //if warrior1 is stronger than warrior2...
    else if (warrior1.strength > warrior2.strength) {
        cout << warrior1.gladiator << " defeats " << warrior2.gladiator << endl;
        warrior1.strength -= warrior2.strength;
        warrior2.strength = 0;
    }
    //if warrior2 is stronger than warrior1...
    else if (warrior1.strength < warrior2.strength) {
        cout << warrior2.gladiator << " defeats " << warrior1.gladiator << endl;
        warrior2.strength -= warrior1.strength;
        warrior1.strength = 0;
    }
    //if both warriors have the same strength...
    else if (warrior1.strength == warrior2.strength){
        cout << "Mutual Annihilation: " 
        << warrior1.gladiator << " and " << warrior2.gladiator << " die at each other's hands" << endl;
        warrior1.strength = warrior2.strength = 0;
    }
}

/*=====================
Warrior Status Function
- Displays all warriors in the battle and their strength
=====================*/
void status(const vector<Warrior>& Warriors) {
    cout << "There are " << Warriors.size() << " warriors" << endl;
    for (const Warrior& warrior : Warriors) {
        cout << "Warrior: " << warrior.gladiator << ", strength: " << warrior.strength << endl;
    }
}