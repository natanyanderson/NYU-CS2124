/*
 * Natanya Anderson
 * Section C, April 13, 2024
 * hw08_single.cpp
 * Program that calculates battles and status among nobles and their Protectors.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Lord;
class Protector;
class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble);
public:
    Noble(const string& name, double strength);
    virtual void printDetails(ostream& os) const;
    string retrieve_name() const { return get_name(); }
    virtual void change_strength(double change) = 0;
    void set_strength(double newStrength);
    void battle(Noble& enemy);
private:
    string name;
    double strength;
    bool alive = true;
protected:
    double get_strength()const {return strength;}
    bool is_alive()const {return alive;}
    string get_name()const {return name;}

};

class Lord: public Noble{
public:
    void printDetails(ostream& os) const override;
    Lord (const string& name);
    bool hires(Protector& protector);
    bool fires(Protector& protector);
    void remove_protector(const Protector& protector);
    void change_strength(double change) override;

private:
    vector<Protector*> army;
    size_t find_protector_index(const Protector& protector);
};

class PersonWithStrengthToFight: public Noble{
public:
    using Noble::Noble;
    void change_strength(double change) override;
};

class Protector{
    friend ostream& operator<<(ostream& os, const Protector& protector);

public:
    Protector(const string& name, int strength);
    void change_hire(const bool change, Lord* noble);
    string retrieve_name() const { return get_name(); }
    int retrieve_strength() const { return get_strength(); }
    bool is_hired()const {return hired;}
    bool is_alive()const {return alive;}
    bool runaway();
    virtual void set_strength(double num) = 0;
protected:
    string get_name()const {return name;}
    double get_strength()const {return strength;}
    string get_lordName() const {return lord->retrieve_name();};

private:
    string name;
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

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "==========\n";
}
/*
 * Declaring function implementations
 */

//Constructor for Noble
Noble::Noble(const string& name, double strength): name(name), strength (strength), alive(true) {}
//Constructor for Lord
Lord::Lord(const string& name):  Noble(name,0) {}
//Constructor for Protector
Protector::Protector(const string& name, int strength): name(name), strength(strength), hired(false), lord(nullptr) {}

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

/** function that outputs the details of a Noble object to an output stream
*
* @param os parameter. ostream& os is a reference to an ostream object
*
* @return void function
*/
void Noble::printDetails(ostream& os) const {
    os << name << " has strength: " << strength << endl;
}

/** function that updates the strength attribute of a Noble object based on the value of newStrength
*
* @param newStrength parameter. New strength value for the Noble object
*
* @return void function
*/
void Noble::set_strength(double newStrength){
    if (newStrength <= 0){
        strength = 0;
        alive = false;
    }else{
        strength = newStrength;
    }
}

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

/** function that simulates a combat scenario between two Noble objects. It handles various outcomes based on the relative
* strength of the combatants and their living status.
*
* @param enemy parameter. enemy is a reference to an enemy object
*
* @return void function
*/
void Noble::battle(Noble& enemy){
    cout << name << " battles " << enemy.get_name() << endl;
    double enemy_strength = enemy.get_strength();

    if (alive && enemy.is_alive()){
        //If both nobles are alive
        if (strength > enemy_strength){
            //The noble is stronger
            change_strength(enemy_strength);
            enemy.change_strength(strength);
            cout << name << " defeats " << enemy.get_name() << endl;
        } else if (strength < enemy_strength){
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
        } else if (enemy.is_alive()){
            //The enemy is alive
            enemy.change_strength(0);
            cout << "He's dead, " << enemy.get_name() << endl;
        } else {
            //Both nobles are dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    }
}

/** function that attempts the recruitment of a Protector to the Lord's army. It serves as a method to add protectors to
* the lord’s army if specific conditions are met. Returns a bool if successful recruitment or not.
*
* @param protector parameter. protector is a reference to a Protector object
*
* @return bool function
*/
bool Lord::hires(Protector& protector){
    if (!protector.is_hired() && this->is_alive()){
        protector.change_hire(true,this);
        army.push_back(&protector);
        set_strength(get_strength()+protector.retrieve_strength());
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
bool Lord::fires(Protector& protector){
    if (protector.is_hired() && is_alive()){
        size_t protector_index = find_protector_index(protector);
        if (protector_index != army.size()){
            cout << protector.retrieve_name() << ", you don't work for me anymore "
                 << "! -- " << get_name() << "." << endl;
            protector.change_hire(false, this);
            remove_protector(protector);
            return true;
        }
    }
    return false;
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

/** function that finds and returns the index (position) of a specific Protector within the lord's army.
*
* @param protector parameter. protector is a reference to a Protector object
*
* @return size_t function
*/
size_t Lord::find_protector_index(const Protector& protector){
    for (size_t index = 0; index < army.size(); ++index) {
        if (army[index] == &protector) {
            return index;
        }
    }
    return army.size();
}

/** function that is defined in the PersonWithStrengthToFight class is designed to adjust the strength of a
* PersonWithStrengthToFight object by reducing it by a specified amount.
*
* @param change parameter. change is a double that has a value that represents the value that will be subtracted from
* the current strength of the person
*
* @return void function
*/
void PersonWithStrengthToFight::change_strength(double change){
    set_strength(get_strength()-change);
    cout << "Ugh!" << endl;
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
void Warrior::set_strength(double ratio){
    cout << get_name() << " says: Take that in the name of my lord, " << get_lordName() << endl;
    Protector::set_strength(ratio);
}

/** function that sets strength of the Archer
*
* @param num
*
* @return void function
*/
void Archer::set_strength(double ratio){
    cout << "TWANG! ";
    Warrior::set_strength(ratio);
}

/** function that sets strength of the Swordsman
*
* @param num
*
* @return void function
*/
void Swordsman::set_strength(double ratio){
    cout << "CLANG! ";
    Warrior::set_strength(ratio);
}
