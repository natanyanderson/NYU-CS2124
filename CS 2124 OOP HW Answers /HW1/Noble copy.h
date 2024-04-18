//
// hw07
// noble.h
// Created by Natanya Anderson on 4/1/24.
//

#ifndef HW7_NOBLE_H
#define HW7_NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Warrior;

    class Noble {
        friend std::ostream& operator<< (std::ostream& os, const Noble& noble);
    private:
        std::string name;
        std::vector<Warrior *> army;
        bool alive = true;

    public:
        Noble(const std::string &name);
        const std::string &getName() const;
        /*
         * Declaring function prototypes
        */
        bool hire(Warrior &warrior);
        bool fire(Warrior &warrior);
        void battle(Noble &opponent);
        void loseBattle(double ratio);
    };
}
#endif //HW7_NOBLE_H
