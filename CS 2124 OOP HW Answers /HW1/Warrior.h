//
// hw07
// warrior.h
// Created by Natanya Anderson on 4/1/24.
//

#ifndef HW7_WARRIOR_H
#define HW7_WARRIOR_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Noble;
// Your Noble and Warrior classes should go here.
    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
    private:
        std::string name;
        double strength;
        bool employed = false;
        Noble* noble;
        bool fleeing = false;
    public:
        Warrior(const std::string& name, double strength);

        const std::string& getName() const { return name; }
        double getStrength() const { return strength; }
        void setStrength(double newStrength) { strength = newStrength; }
        bool isHired() const { return employed; }
        void setHired(bool status) { employed = status; }
        void setNoble(Noble* noblePtr = nullptr);
        void runaway();
        void setFleeing(bool status) {fleeing = status;}
        bool isFleeing() const {return fleeing;}
    };
}


#endif //HW7_WARRIOR_H
