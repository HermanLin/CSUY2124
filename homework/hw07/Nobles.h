/* 
    NOBLES HEADER FILE
    Herman Lin 
*/

#ifndef NOBLES_H
#define NOBLES_H

#include <string>
#include <vector>

namespace WarriorCraft {
    class Protectors;

    //==========================//
    /* NOBLES CLASS DEFINITIONS */
    //==========================//
    class Nobles {
    public:
        Nobles (const std::string&);

        const std::string& getName() const;

        bool isDead() const;
        virtual void dies();

        virtual double getStrength() const = 0;
        virtual void setStrength(const double) = 0;

        void battle(Nobles&);
        void defeats(Nobles&, const double);

        virtual void battleCry() = 0;
    private:
        std::string name;
        bool dead;
    };
    
    //========================//
    /* LORD CLASS DEFINITIONS */
    //========================//
    class Lord : public Nobles {
    public:
        Lord (const std::string&);

        double getStrength() const;
        void setStrength(const double);
        
        bool hires(Protectors&);
        bool fires(Protectors&);
        size_t findProtector(Protectors&);

        void battleCry();
    private:
        std::vector<Protectors*> army;
    };

    //=============================================//
    /* PERSONWITHSTRENGTHTOFIGHT CLASS DEFINITIONS */
    //=============================================//
    class PersonWithStrengthToFight : public Nobles {
    public:
        PersonWithStrengthToFight (const std::string&, const double);

        void dies();

        double getStrength() const;
        void setStrength(const double);

        void battleCry();
    private:
        double strength;
    };
}

#endif