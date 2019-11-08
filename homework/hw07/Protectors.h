/* 
    PROTECTORS HEADER FILE
    Herman Lin
*/

#ifndef PROTECTORS_H
#define PROTECTORS_H

#include <string>

namespace WarriorCraft {
    class Nobles;

    //==============================//
    /* PROTECTORS CLASS DEFINITIONS */
    //==============================//
    class Protectors {
    public:
        Protectors (const std::string&, const double);

        const std::string& getName() const;

        Nobles* getBoss() const;
        void setBoss(Nobles*);

        double getStrength() const;
        void setStrength(const double);

        virtual void battleCry() = 0;
    private:
        std::string name;
        double strength;
        Nobles* boss;
    };

    //==========================//
    /* WIZARD CLASS DEFINITIONS */
    //==========================//
    class Wizard : public Protectors {
    public:
        Wizard (const std::string&, const double);

        void battleCry();
    };

    //============================//
    /* WARRIORS CLASS DEFINITIONS */
    //============================//
    class Warriors : public Protectors {
    public:
        Warriors (const std::string&, const double);
    };

    //==========================//
    /* ARCHER CLASS DEFINITIONS */
    //==========================//
    class Archer : public Warriors {
    public:
        Archer (const std::string&, const double);

        void battleCry();
    };

    //=============================//
    /* SWORDSMAN CLASS DEFINITIONS */
    //=============================//
    class Swordsman : public Warriors {
    public:
        Swordsman (const std::string&, const double);

        void battleCry();
    };
}

#endif