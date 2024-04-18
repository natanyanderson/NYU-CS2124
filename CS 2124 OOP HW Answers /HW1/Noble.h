//
// Created by Natanya Anderson on 4/11/24.
//

/*
 * Natanya Anderson
 * Section C, April 13, 2024
 * Noble.h
 * Program that calculates battles and status among nobles and their Protectors.
*/

#ifndef HW08_NOBLE_H
#define HW08_NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace Warriorcraft {
    class Protector;
    class Noble{
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public:
        Noble (const std::string& name, double strength);
        virtual void printDetails(std::ostream& os) const;
        std::string retrieve_name() const;
        virtual void change_strength(double change);
        void set_strength(double newStrength);
        void battle(Noble& enemy);
    private:
        std::string name;
        double strength;
        bool alive;
    protected:
        double get_strength()const;
        bool is_alive()const;
        std::string get_name()const;
    };
    class Lord: public Noble{
    public:
        void printDetails(std::ostream& os) const override;
        Lord (const std::string& name);
        bool hires(Protector& protector);
        bool fires(Protector& protector);
        void remove_protector(const Protector& protector);
        void change_strength(double change) override;

    private:
        std::vector<Protector*> army;
        size_t find_protector_index(const Protector& protector);
    };

    class PersonWithStrengthToFight: public Noble{
    public:
        using Noble::Noble;
        void change_strength(double change) override;
    };
}

#endif //HW08_NOBLE_H
