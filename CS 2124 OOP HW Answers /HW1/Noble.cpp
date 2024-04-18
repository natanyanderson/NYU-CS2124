/*
 * Natanya Anderson
 * Section C, April 13, 2024
 * Noble.cpp
 * Program that calculates battles and status among nobles and their Protectors.
*/

#include "Noble.h"
#include "Protector.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace Warriorcraft {
    Noble::Noble(const string& name, double strength): name(name), strength (strength), alive(true) {}
    string Noble::retrieve_name() const { return get_name(); }
    bool Noble::is_alive() const { return alive; }
    string Noble::get_name() const { return name; }
    double Noble::get_strength()const { return strength; }

/*
* Declaring function implementations
*/

/** output operator for Noble class
*
* @param os, noble
*
* @return os
*/
    ostream& operator<<(ostream& os, const Noble& noble) {
        noble.printDetails(os);
        return os;
    }

/** function that outputs the details of a Noble object to an output stream
*
* @param os parameter. ostream& os is a reference to an ostream object
*
* @return void function
*/
    void Noble::printDetails(ostream &os) const {
        os << name << " has strength: " << strength << endl;
    }

/** function that updates the strength attribute of a Noble object based on the value of newStrength
*
* @param newStrength parameter. New strength value for the Noble object
*
* @return void function
*/
    void Noble::set_strength(double newStrength) {
        if (newStrength <= 0) {
            strength = 0;
            alive = false;
        } else {
            strength = newStrength;
        }
    }

/** function that simulates a combat scenario between two Noble objects. It handles various outcomes based on the relative
* strength of the combatants and their living status.
*
* @param enemy parameter. enemy is a reference to an enemy object
*
* @return void function
*/
    void Noble::battle(Noble &enemy) {
        double enemy_strength = enemy.get_strength();
        cout << name << " battles " << enemy.get_name() << endl;
        if (alive && enemy.is_alive()) {
            //If both nobles are alive
            if (strength > enemy_strength) {
                //The noble is stronger
                change_strength(enemy_strength);
                enemy.change_strength(strength);
                cout << name << " defeats " << enemy.get_name() << endl;
            } else if (strength < enemy_strength) {
                //The enemy if stronger
                change_strength(enemy_strength);
                enemy.change_strength(strength);
                cout << enemy.get_name() << " defeats " << name << endl;
            } else {
                //Draw
                change_strength(enemy_strength);
                enemy.change_strength(strength);
                cout << "Mutual Annihilation: " << name << " and "
                     << enemy.get_name() << " die at each other's hands" << endl;
            }
        } else {
            //At least one noble is dead
            if (alive) {
                //The noble is alive
                change_strength(0);
                cout << "He's dead, " << name << endl;
            } else if (enemy.is_alive()) {
                //The enemy is alive
                enemy.change_strength(0);
                cout << "He's dead, " << enemy.get_name() << endl;
            } else {
                //Both nobles are dead
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
        }
    }

    Lord::Lord(const string& name):  Noble(name,0) {}

/** function that outputs the detailed information about a Lord object, specifically its name, the size of its army, and
* detailed attributes of each member of its army.
*
* @param os parameter. ostream& os is a reference to an ostream object
*
* @return void function
*/
    void Lord::printDetails(ostream& os) const {
        os << get_name() << " has an army of size: " << army.size() << endl;
        for (const Protector* protector : army) {
            os << "\t" << protector->retrieve_name() << " has strength " << protector->retrieve_strength() << endl;
        }
    }

/** function that modifies the strength of the Lord and uniformly adjusts the strength of each member of the Lord's army
* (represented by Protector objects) based on a specified change in the Lord's overall strength.
*
* @param change parameter. double change represents the amount by which the Lord's strength should be reduced or altered.
*
* @return void function
*/
    void Lord::change_strength(double change) {
        double ratio = 0;
        if (change < get_strength()){
            ratio = 1 - (change/get_strength());
        } else {
            if (change >= get_strength()) {
                set_strength(0);
                ratio = 0;
            }
        }
        for (Protector* protector: army){
            protector->set_strength(ratio);
        }
    }

/** function that attempts the recruitment of a Protector to the Lord's army. It serves as a method to add protectors to
* the lord’s army if specific conditions are met. Returns a bool if successful recruitment or not.
*
* @param protector parameter. protector is a reference to a Protector object
*
* @return bool function
*/
    bool Lord::hires(Protector &protector) {
        if (!protector.is_hired() && this->is_alive()) {
            protector.change_hire(true, this);
            army.push_back(&protector);
            set_strength(get_strength() + protector.retrieve_strength());
            return true;
        }
        cout << get_name() << " failed to hire " << protector.retrieve_name() << endl;
        return false;
    }

/** function that removes a specified Protector from the lord's army. This function is used to manage and update the
* composition of the army by removing members when necessary. Returns a bool if successfully fired or not.
*
* @param protector parameter. protector is a reference to a Protector object
*
* @return bool function
*/
    bool Lord::fires(Protector &protector) {
        if (protector.is_hired() && is_alive()) {
            size_t protector_index = find_protector_index(protector);
            if (protector_index != army.size()) {
                cout << protector.retrieve_name() << ", you don't work for me anymore "
                     << "! -- " << get_name() << "." << endl;
                protector.change_hire(false, this);
                remove_protector(protector);
                return true;
            }
        }
        return false;
    }

/** function that finds and returns the index (position) of a specific Protector within the lord's army.
*
* @param protector parameter. protector is a reference to a Protector object
*
* @return size_t function
*/
    size_t Lord::find_protector_index(const Protector &protector) {
        for (size_t index = 0; index < army.size(); ++index) {
            if (army[index] == &protector) {
                return index;
            }
        }
        return army.size();
    }

/** function removes a specified protector from a Lord's army. If the protector is found, the functions shifts each
* protector down the list then removes the last element to avoid duplication.
*
* @param protector parameter. protector is a reference to a Protector object
*
* @return void function
*/
    void Lord::remove_protector(const Protector& protector){
        size_t protector_index = find_protector_index(protector);
        if (protector_index < army.size()) {
            for (size_t index = protector_index; index < army.size() - 1; ++index) {
                army[index] = army[index + 1];
            }
            army.pop_back();
        }
    }

/** function that is defined in the PersonWithStrengthToFight class is designed to adjust the strength of a
* PersonWithStrengthToFight object by reducing it by a specified amount.
*
* @param change parameter. change is a double that has a value that represents the value that will be subtracted from
* the current strength of the person
*
* @return void function
*/
    void PersonWithStrengthToFight::change_strength(double change) {
        set_strength(get_strength() - change);
        cout << "Ugh!" << endl;
    }

}