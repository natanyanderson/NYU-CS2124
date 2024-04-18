/*
 * hw07
 * warrior.cpp
 * Created by Natanya Anderson on 4/1/24.
*/

#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
    Warrior::Warrior(const string& name, double strength)
            : name(name), strength(strength){}

    ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << "\t" << warrior.name << ": " << warrior.strength << endl;
        return os;
    }

    /** This function assigns the provided noble pointer (noblePtr) to the Warrior object's noble member variable.
    * This effectively sets or updates the Warrior's associated noble to the one passed in the argument. If noblePtr is
    * nullptr, it would dissociate the warrior from any noble, making the warrior free or not associated with any noble. If
    * noblePtr points to a Noble object, the warrior is then associated with that noble.
    *
    * @param noblePtr parameter. noblePtr is a pointer.
    *
    * @return void function
    */
    void Warrior::setNoble(Noble *noblePtr) {
        {
            noble = noblePtr;
        }
    }

    /** This function enables a warrior to flee from their currently associated noble. It temporarily sets fleeing as true
    * and calls the fire method to remove the warrior from the noble's roster. It then dissociates the warriornfrom the noble
    * and sets the pointer to nullptr. It then resets the fleeing status.
    *
    * @param None
    *
    * @return void function
    */
    void Warrior::runaway() {
        if (noble) {
            cout << name << " flees in terror, abandoning his lord, "
                 << noble->getName() << endl;
            setFleeing(true);
            noble->fire(*this); // Noble handles removal
            noble = nullptr;
            setFleeing(false); // Reset fleeing status
        }
    }
}