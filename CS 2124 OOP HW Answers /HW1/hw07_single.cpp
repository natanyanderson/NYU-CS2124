/*
  hw07_single.cpp
  Natanya Anderson
  Section C, April 1, 2024
  This program simulates medieval battles between nobles, who can hire, fire, and battle with warriors,
  adjusting the strength of their armies based on the outcomes of these battles.
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Noble;
// Your Noble and Warrior classes should go here.
class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
    string name;
    double strength;
    bool employed = false;
    Noble* noble;
    bool fleeing = false;
public:
    Warrior(const string& name, double strength)
            : name(name), strength(strength){}

    const string& getName() const { return name; }
    double getStrength() const { return strength; }
    void setStrength(double newStrength) { strength = newStrength; }
    bool isHired() const { return employed; }
    void setHired(bool status) { employed = status; }
    void setNoble(Noble* noblePtr = nullptr);
    void runaway();
    void setFleeing(bool status) {fleeing = status;}
    bool isFleeing() const {return fleeing;}
};

//Noble class
class Noble {
    friend ostream& operator<< (ostream& os, const Noble& noble);
private:
    string name;
    vector<Warrior *> army;
    bool alive = true;

public:
    Noble(const string &name) : name(name) {}
    const string& getName() const { return name; }
    /*
     * Declaring function prototypes
    */
    bool hire(Warrior &warrior);
    bool fire(Warrior &warrior);
    void battle(Noble &opponent);
    void loseBattle(double ratio);
};

int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}


/*
* Declaring function implementations
*/

/** This function is the output operator for the Warrior class
*
* @param os, warrior parameter
*
* @return ostream&
*/
ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << "\t" << warrior.name << ": " << warrior.strength << endl;
    return os;
}

/** This function is the output operator for the Noble class
*
* @param os, noble parameter
*
* @return ostream&
*/
ostream& operator<< (ostream& os, const Noble& noble){
    os << noble.name << " has an army of " << noble.army.size() << endl;
    for (const Warrior* warrior: noble.army){
        os << *warrior;
    }
    return os;
}

/** This function attempts to hire a warrior for a noble, ensuring the noble is alive and the warrior is not already
* employed before successfully adding the warrior to the noble's army and marking the hiring process as successful.
*
* @param warrior parameter. warrior is a reference to Warrior object
*
* @return bool
*/
bool Noble::hire(Warrior &warrior)  {
    if (!alive) {
        cout << name << " cannot hire warriors because they are dead." << endl;
        return false;
    }
    if (warrior.isHired()) {
        cout << name << " failed to hire " << warrior.getName() << endl;
        return false;
    }
    warrior.setNoble(this);
    warrior.setHired(true);
    army.push_back(&warrior);
    return true;
}

/** This function attempts to remove a specified warrior from a noble's army, ensuring the noble is alive and the warrior
* is apart of the noble's army before successfully removing them and indicating whether the operation was successful.
* Upon finding the warrior in the army (when army[index] matches the address of the warrior parameter), it prints a
* message indicating that the warrior is no longer employed by the noble. To remove the warrior from the army,
* it shifts all warriors in the array one position to the left to overwrite the position of the fired warrior.
* This moves all warriors after the fired warrior one position up in the vector to fill the gap left by the fired warrior.
*
* @param warrior parameter. warrior is a reference to Warrior object
*
* @return bool
*/
bool Noble::fire(Warrior &warrior) {
    if (!alive) {
        cout << name << " is dead and cannot fire warriors." << endl;
        return false;
    }
    for (size_t index = 0; index < army.size(); ++index) {
        if (army[index] == &warrior) {
            if(!warrior.isFleeing()) {
                cout << warrior.getName() << ", you don't work for me any more! -- "<< name << "." << endl;
            }
            warrior.setHired(false);
            // Shift all warriors one place to the left to overwrite the fired warrior
            for (size_t index2 = index; index2 < army.size() - 1; ++index2) {
                army[index2] = army[index2 + 1];
            }
            army.pop_back(); // Remove the last warrior, now a duplicate
            warrior.setNoble(nullptr);
            return true;
        }
    }
    cout << name << " failed to fire " << warrior.getName() << endl;
    return false;
}

/** This function simulates a battle between two nobles, checking for dead nobles and considering their armies'
* strengths to determine the outcome and applying consequences based on the battle results, including the potential
* death of a noble and the weakening of their army.
*
* @param opponent parameter. opponent is a reference to another Noble object
*
* @return void function
*/
void Noble::battle(Noble &opponent) {
    cout << name << " battles " << opponent.getName() << endl;

    if (!alive && !opponent.alive) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    } else if (!alive) {
        cout << "He's dead, " << opponent.getName() << endl;
        return;
    } else if (!opponent.alive) {
        cout << "He's dead, " << name << endl;
        return;
    }

    double myStrength = 0;
    double opponentStrength = 0;

    for (const Warrior *warrior : army) {
        myStrength += warrior->getStrength();
    }
    for (const Warrior *warrior : opponent.army) {
        opponentStrength += warrior->getStrength();
    }

    if (myStrength == opponentStrength) {
        cout << "Mutual Annihilation: " << name << " and " << opponent.getName() << " die at each other's hands" << endl;
        alive = false;
        opponent.alive = false;
        loseBattle(1);
        opponent.loseBattle(1);
    } else if (myStrength > opponentStrength) {
        cout << name << " defeats " << opponent.getName() << endl;
        opponent.alive = false;
        opponent.loseBattle(1);
        loseBattle(opponentStrength / myStrength);
    } else {
        cout << opponent.getName() << " defeats " << name << endl;
        alive = false;
        loseBattle(1);
        opponent.loseBattle(myStrength / opponentStrength);
    }
}

/** This function modifies the strength of each warrior in a noble's army after losing a battle, based on a given ratio,
* simulating the weakening of the army as a consequence of losing a battle.
*
* @param ratio parameter. Ratio represents the proportion of strength that each warrior in the
* noble's army loses as a result of losing a battle.
*
* @return void function
*/
void Noble::loseBattle(double ratio) {
    for (Warrior *warrior: army) {
        warrior->setStrength(warrior->getStrength() * (1 - ratio));
    }
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

