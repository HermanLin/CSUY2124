/* 
    WARRIOR HEADER FILE
    Herman Lin
*/

#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>

namespace WarriorCraft {
    class Noble;

    // ========================== //
    // Warrior Class Declarations //
    // ========================== //
    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, const Warrior&);
    public:
        Warrior(const std::string&, const double);

        const std::string& getName() const;
        double getStrength() const;
        Noble* getBoss() const;
        bool isHired() const;

        void setStrength(const double);
        void setBoss(Noble*);

        void runaway();
    private:
        std::string name;
        double strength;
        Noble* boss;
    };
}

#endif