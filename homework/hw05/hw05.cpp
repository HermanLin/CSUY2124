/*==========================================================
rec05.cpp
Herman Lin

This file simulates battling between Nobles and their armies
where every Noble and Warrior is made on the heap.
==========================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Noble;
class Warrior;
void openFile(ifstream& ifs);
Noble* nobleExist(const string& checkNoble, vector<Noble*> allNobles);
Warrior* warriorExist(const string& checkWarrior, vector<Warrior*> allWarriors);

/*======================================
Warrior Class
- name: the name of the Warrior
- strength: the strength of the Warrior
- boss: pointer to a Noble
======================================*/
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& warrior) {
		os << warrior.name << ": " << warrior.strength << endl;
		return os;
	}
private:
    string name;
    double strength;
    Noble* boss;
public:
    //constructor
    Warrior (const string& name, double strength) 
        : name(name), strength(strength), boss(nullptr)
    {}

    //getters and mutators
    const string& getName() const { return name; }
	double getStrength() const { return strength; }
	Noble* getBoss() const { return boss; }
	bool isHired() const { return boss != nullptr; }

	void setStrength(const double ratio) { 
		strength *= (1 - ratio);
	}
	void setBoss(Noble* newBoss) { boss = newBoss; }
};

class Noble {
    friend ostream& operator<<(ostream& os, const Noble& noble) {
		os << noble.name << " has an army of " << noble.army.size() << endl;
		for (Warrior* warrior : noble.army) {
			os << "\t" << *warrior;
		}
		return os;
	}
private:
    string name;
    vector<Warrior*> army;
    bool dead;
public:
    //constructor
    Noble(const string& name) 
        : name(name)
    { dead = false; }

    //getters and mutators
    const string& getName() const { return name; }
    bool isDead() const { return dead; }

    void dies() { dead = true; }
    int getArmyStrength() const {
        double totalStr = 0;
        for (Warrior* warrior : army) {
            totalStr += warrior->getStrength();
        }
        return totalStr;
    }
    void setArmyStrength(const double ratio) {
        for (Warrior* warrior : army) {
            warrior->setStrength(ratio);
        }
    }

    //hire Warriors and add to the army
    bool hire(Warrior* mercenary) {
        if (dead) { return false; }
        //if the mercenary has a boss...
        else if (mercenary->isHired()) { return false; } 
        else {
            mercenary->setBoss(this);
            army.push_back(mercenary);
            return true;
        }
    }

    //fire a Warrior and remove from the army
    bool fire(Warrior* layoff) {
        if (dead) { return false; }
        //check if layoff is a part of this army...
        else if (layoff->getBoss() != this) { 
            cout << layoff->getName() << " does not belong to " << this->getName() << endl;
            return false; 
        }
        else {
            for (size_t i = 0; i < army.size(); i++) {
                if (army[i] == layoff) {
                    cout << "You don't work for me anymore " << layoff->getName()
                         << " -- " << name << "." << endl;
                    layoff->setBoss(nullptr);

                    for (size_t j = i; j < army.size() - 1; j++) {
                        army[j] = army[j + 1];
                    }
                    army.pop_back();
                    return true;
                }
            }
            return false;
        }
    }

    //battle helper function for defeating other Nobles
    void defeats(Noble* opponent, const double ratio) {
        cout << name << " defeats " << opponent->getName() << endl;
        setArmyStrength(ratio);
        opponent->dies();
        opponent->setArmyStrength(1);
    }

    //battle other Nobles
    void battle(Noble* opponent) {
        cout << name << " battles " << opponent->getName() << endl;
		//if either is dead...
		if (dead || opponent->isDead()) {
			//if both are dead...
			if (dead && opponent->isDead()) {
				cout << "Oh NO! They're both dead! Yuck!" << endl;
			}
			//if this is dead...
			else if (dead) {
				cout << "He's dead, " << opponent->getName() << endl;
			}
			//if the opponent is dead...
			else {
				cout << "He's dead, " << name << endl;
			}
		}
		else {
			//get the strengths of each army and set the default ratio to 1
			double thisStrength = getArmyStrength();
			double opponentStrength = opponent->getArmyStrength();
			double ratio = 1;
			
			//if the strengths are equal...
			if (thisStrength == opponentStrength) {
				cout << "Mutual Annihilation: " 
					 << name << " and " << opponent->getName() 
					 << " die at each other's hands" << endl;
				dies();
				opponent->dies();
				setArmyStrength(ratio);
				opponent->setArmyStrength(ratio);
			}
			//if this is stronger...
			else if (thisStrength > opponentStrength) {
				ratio = opponentStrength / thisStrength;
				defeats(opponent, ratio);
			}
			//if the opponent is stronger...
			else {
				ratio = thisStrength / opponentStrength;
				opponent->defeats(this, ratio);
			}
		}
    }
};

int main() {
    ifstream stream;
    vector<Warrior*> allWarriors;
    vector<Warrior*> unemployed;
    vector<Noble*> allNobles;

    openFile(stream);
    string command, newNoble, newWarrior, noble1, noble2;
    double newStrength;
    
    //Read in a new command
    while (stream >> command) {
        //create a new Noble
        if (command == "Noble") {
            stream >> newNoble;
            allNobles.push_back(new Noble(newNoble));
        }
        //create a new Warrior
        else if (command == "Warrior") {
            stream >> newWarrior >> newStrength;
            allWarriors.push_back(new Warrior(newWarrior, newStrength));
        }
        //hire a Warrior for a Noble
        else if (command == "Hire") {
            stream >> noble1 >> newWarrior;
            Noble* noble = nobleExist(noble1, allNobles);
            Warrior* warrior = warriorExist(newWarrior, allWarriors);
            //check if either the Noble and/or the Warrior exists
            if (noble) {
                if (warrior) {
                    noble->hire(warrior);
                }
                else {
                    cout << "The Warrior '" << newWarrior << "' does not exist" << endl; 
                }
            }
            else {
                cout << "The Noble '" << noble1 << "' does not exist" << endl;
            }
        }
        //fire a Warrior from a Noble's army
        else if (command == "Fire") {
            stream >> noble1 >> newWarrior;
            Noble* noble = nobleExist(noble1, allNobles);
            Warrior* warrior = warriorExist(newWarrior, allWarriors);
            //check if either the Noble and/or the Warrior exists
            if (noble) {
                if (warrior) {
                    noble->fire(warrior);
                }
                else {
                    cout << "The Warrior '" << newWarrior << "' does not exist" << endl; 
                }
            }
            else {
                cout << "The Noble '" << noble1 << "' does not exist" << endl;
            }
        }
        //print the status of the Nobles and their armies
        //print any unemployed Warriors
        else if (command == "Status") {
            cout << "\n==========\n";
            cout << "Nobles:\n";
            //if no Nobles exist...
            if (!allNobles.size()) { cout << "NONE\n"; }
            else {
                for (Noble* noble : allNobles) {
                    cout << *noble;
                }
            }
            cout << "Unemployed Warriors:\n";
            //if no Warriors exist...
            if (!allWarriors.size()) { cout << "NONE\n"; }
            else {                
                //find all unemployed Warriors and add them to the unemployed vector
                for (Warrior* warrior : allWarriors) {
                    if (!warrior->isHired()) {
                        unemployed.push_back(warrior);
                    }
                }
                //if unemployed is empty...
                if (!unemployed.size()) { cout << "NONE\n"; }
                else {
                    //print all unemployed Warriors
                    for (Warrior* warrior : unemployed) {
                        cout << *warrior;
                    }
                }
                //clear the unemployed vector
                unemployed.clear();
            }
            cout << "==========\n";
        }
        //delete all Nobles and Warriors from their respective vectors
        else if (command == "Clear") {
            for (Warrior* warrior : allWarriors) {
                delete(warrior);
            } 
            allWarriors.clear();
            for (Noble* noble : allNobles) {
                delete(noble);
            }
            allNobles.clear();
        }
    }
    stream.close();
}

/*===================================
Open File Function 
- open the "nobleWarriors.txt"
- if it doesn't exist, raise an error
===================================*/
void openFile(ifstream& ifs) {
    ifs.clear();
    ifs.open("nobleWarriors.txt");
    if (!ifs) {
        cerr << "Could not find file 'nobleWarriors.txt'" << endl;
        exit(1);
    }
}

/*===========================================
nobleExist Function
- returns the address of a Noble if it exists
- if it doesn't exist, return nullptr
===========================================*/
Noble* nobleExist(const string& checkNoble, vector<Noble*> allNobles) {
    for (Noble* noble : allNobles) {
        if (noble->getName() == checkNoble) {
            return noble;
        }
    }
    return nullptr;
}

/*=============================================
warriorExist Function
- returns the address of a Warrior if it exists
- if it doesn't exist, return nullptr
=============================================*/
Warrior* warriorExist(const string& checkWarrior, vector<Warrior*> allWarriors) {
    for (Warrior* warrior : allWarriors) {
        if (warrior->getName() == checkWarrior) {
            return warrior;
        }
    }
    return nullptr;
}