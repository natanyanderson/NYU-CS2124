/*
 * Natanya Anderson
 * Section C, April 13, 2024
 * Protector.cpp
 * Program that calculates battles and status among nobles and their Protectors.
*/

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace Warriorcraft {
    Protector::Protector(const string& name, int strength): name(name), strength(strength), hired(false), lord(nullptr) {}
    string Protector::retrieve_name() const { return get_name(); }
    int Protector::retrieve_strength() const { return get_strength(); }
    bool Protector::is_hired()const {return hired;}
    bool Protector::is_alive()const {return alive;}
    string Protector::get_name()const {return name;}
    double Protector::get_strength()const {return strength;}
    string Protector::get_lordName() const {return lord->retrieve_name();}


/** output operator for Protector class
*
* @param os, protector
*
* @return os
*/
    ostream& operator<<(ostream& os, const Protector& protector) {
        os << protector.name << ": " << protector.strength;
        return os;
    }

/** function that is a method within the Protector class that allows a protector to attempt to flee
* (or run away) from their lord. If protector is alive, it removes itself from the army.
*
* @param None
*
* @return bool
*/
    bool Protector::runaway(){
        if (is_alive()){
            cout << name << " flees in terror, abandoning his lord, "
                 << lord->retrieve_name() << endl;
            lord->remove_protector(*this);
            lord = nullptr;
            return true;
        }
        return false;
    }

/** function that updates the employment status of a Protector object by either hiring or firing them from service under a Lord.
*
* @param change, noble
*
* @return void function
*/
    void Protector::change_hire(const bool change, Lord* noble){
        hired = change;
        if (change){
            lord = noble;
        } else {
            lord = nullptr;
        }
    }

/** function that sets the strength of a protector to a specified new value and updates their status of being
* alive based on the new strength.
*
* @param newStrength
*
* @return void function
*/
    void Protector::set_strength(double newStrength) {
        strength = newStrength;
        alive = strength > 0;
    }

/** function that sets the strength of a protector to a specified new value and updates their status of being
* alive based on the new strength.
*
* @param newStrength
*
* @return void function
*/
    void Wizard::set_strength(double ratio){
        cout << "POOF!" << endl;
        Protector::set_strength(ratio);
    }

/** function that sets strength of the Warrior
*
* @param num
*
* @return void function
*/
    void Warrior::set_strength(double num){
        cout << get_name() << " says: Take that in the name of my lord, " << get_lordName() << endl;
        Protector::set_strength(num);
    }

/** function that sets strength of the Archer
*
* @param num
*
* @return void function
*/
    void Archer::set_strength(double num){
        cout << "TWANG! ";
        Warrior::set_strength(num);
    }

/** function that sets strength of the Swordsman
*
* @param num
*
* @return void function
*/
    void Swordsman::set_strength(double num){
        cout << "CLANG! ";
        Warrior::set_strength(num);
    }


}