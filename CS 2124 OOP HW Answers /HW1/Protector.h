//
// Created by Natanya Anderson on 4/12/24.
//

/*
 * Natanya Anderson
 * Section C, April 13, 2024
 * Protector.h
 * Program that calculates battles and status among nobles and their Protectors.
*/

#ifndef HW08_PROTECTOR_H
#define HW08_PROTECTOR_H

#include <iostream>
#include <string>
#include <vector>

namespace Warriorcraft {
    class Noble;
    class Lord;

    class Protector {
        friend std::ostream& operator<<(std::ostream& os, const Protector& protector);

    public:
        Protector(const std::string& name, int strength);
        void change_hire(const bool change, Lord* noble);
        std::string retrieve_name() const;
        int retrieve_strength() const;
        bool is_hired()const;
        bool is_alive()const;
        bool runaway();
        virtual void set_strength(double ratio) = 0;
    protected:
        std::string get_name()const;
        double get_strength()const;
        std::string get_lordName()const;

    private:
        std::string name;
        double strength = 0;
        bool hired = false;
        bool alive = false;
        Lord* lord;
    };

    class Wizard: public Protector{
    public:
        using Protector::Protector;
        void set_strength(double ratio) override;
    };

    class Warrior: public Protector{
    public:
        using Protector::Protector;
        void set_strength(double ratio) override = 0;
    };

    class Archer : public Warrior {
    public:
        using Warrior::Warrior;
        virtual void set_strength(double ratio);
    };

    class Swordsman : public Warrior {
    public:
        using Warrior::Warrior;
        virtual void set_strength(double ratio);
    };
}


#endif //HW08_PROTECTOR_H
