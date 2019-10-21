/*==================================================================
hw04.cpp
Herman Lin

This file simulates battles between Nobles and their armies
A Noble can hire or fire Warriors and battle against other Nobles
with their respective armies.
In order for Nobles to battle other Nobles, the total strength of
all the Warriors in their armies is compared against each other.
The winner of the battle is the one with the greater total strength.
The winning Noble has each of his Warriors' strength decreased by a
ratio of the loser's total strength to the winner's total strength.
The loser of the battle dies
==================================================================*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Noble;

/*======================================
Warrior Class
- _name: the name of the Warrior
- _strength: the strength of the Warrior
- _boss: pointer to a Noble
======================================*/
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& warrior) {
		os << "\t" << warrior._name << ": " << warrior._strength << endl;
		return os;
	}
private:
	string _name;
	double _strength;
	Noble* _boss;

public:
	//Initialize a Warrior with a name, strength, and no boss
	Warrior (const string& name, double strength)
		: _name(name), _strength(strength), _boss(nullptr)
	{}

	const string& getName() const { return _name; }
	double getStrength() const { return _strength; }
	Noble* getBoss() const { return _boss; }
	bool isHired() const { return _boss != nullptr; }

	void setStrength(const double ratio) { 
		_strength *= (1 - ratio);
	}
	void setBoss(Noble* newBoss) { _boss = newBoss; }
};

/*=================================
Noble Class
- _name: name of the Noble
- _army: vector of Warrior pointers
- _isDead: if the Noble is "dead"
=================================*/
class Noble {
	friend ostream& operator<<(ostream& os, const Noble& noble) {
		os << noble._name << " has an army of " << noble._army.size() << endl;
		for (Warrior* warrior : noble._army) {
			os << *warrior;
		}
		return os;
	}
private:
	string _name;
	vector<Warrior*> _army;
	bool _isDead;

public:
	//initialize a Noble with a name and alive
	Noble (const string& name)
		: _name(name)
	{ _isDead = false; }

	const string& getName() const { return _name; }
	bool isDead() const { return _isDead; }
	void dies() { _isDead = true; }

	int getArmyStrength() {
		int totalStr = 0;
		for (Warrior* warrior : _army) {
			totalStr += warrior->getStrength();
		}
		return totalStr;
	}
	void setArmyStrength(const double ratio) {
		for (Warrior* warrior : _army) {
			warrior->setStrength(ratio);
		}
	}

	bool hire(Warrior& mercenary) {
		//if the Noble is dead, don't hire anyone
		if (_isDead) { 
			return false; 
		}
		//if the Warrior has a boss, don't hire him
		else if (mercenary.isHired()) { 
			return false; 
		}
		else {
			//set the Warrior's boss to this and add a reference to the Warrior in _army
			mercenary.setBoss(this);
			_army.push_back(&mercenary);
			return true;
		}
	}

	bool fire(Warrior& layoff) {
		//check if the Noble is dead
		if (_isDead) {
			return false;
		}
		//check if layoff has this as its boss	
		else if (layoff.getBoss() != this) {
			return false;
		}
		else {
			//loop until the layoff Warrior is found
			size_t warriorIndex;
			for (size_t i = 0; i < _army.size(); i++) {
				if (_army[i] == &layoff) {
					cout << "You don't work for me anymore " << layoff.getName()
						 << " -- " << _name << "." << endl;
					//set Warrior's _boss to nullptr
					layoff.setBoss(nullptr);

					//loop through the _army starting from the fired Warrior
					//shift Warriors to the left
					warriorIndex = i;
					for (size_t j = i; j < _army.size() - 1; j++) {
						_army[j] = _army[j + 1];
					}
					//remove last element
					_army.pop_back();
					return true;
				}
			}
		}
	}

	void defeats(Noble& opponent, const double ratio) {
		cout << _name << " defeats " << opponent.getName() << endl;
		setArmyStrength(ratio);
		opponent.dies();
		opponent.setArmyStrength(1);
	}

	void battle(Noble& opponent) {
		cout << _name << " battles " << opponent.getName() << endl;
		//if either is dead...
		if (_isDead || opponent.isDead()) {
			//if both are dead...
			if (_isDead && opponent.isDead()) {
				cout << "Oh NO! They're both dead! Yuck!" << endl;
			}
			//if this is dead...
			else if (_isDead) {
				cout << "He's dead, " << opponent.getName() << endl;
			}
			//if the opponent is dead...
			else {
				cout << "He's dead, " << _name << endl;
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
					 << _name << " and " << opponent.getName() 
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
};

int main() {

	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");
	
	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);
	
	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);
	
    cout << "==========\n"
         << "Status before all battles, etc.\n";
	cout << jim << endl;
    cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
    cout << "==========\n";
	
	art.fire(cheetah);
	cout << art << endl;
	
	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
	cout << jim << endl;
    cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
    cout << "==========\n";

	cout << "Test if Tarzan can be hired again\n";
	jim.hire(cheetah);
	cout << jim << endl;
}
