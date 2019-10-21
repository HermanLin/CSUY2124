/* 
    NOBLE HEADER FILE
    Herman Lin
*/

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    // ======================== //
    // Noble Class Delcarations //
    // ======================== //
    class Warrior;

    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble&);
    public:
        Noble(const std::string&);

        const std::string& getName() const;
        bool isDead() const;

        void dies();
        bool hire(Warrior&);
        bool fire(Warrior&);
        void deserter(Warrior&);
        void battle(Noble&);
    private:
        int getArmyStrength() const;
        void setArmyStrength(const double);
        void defeats(Noble&, const double);
        size_t findWarrior(Warrior&);

        std::string name;
        bool dead;
        std::vector<Warrior*> army;
    };
}

#endif