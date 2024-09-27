/*
hw03.cpp
Natanya Anderson
Sep 26, 2024
This program reads the input file "warriors.txt" to calculate battles and status amongst the warriors
using their weapon information. This program includes a Warrior class that contains a nested Weapon class inside it to ensure
that no other code uses the Weapon class except for Warrior class itself therefore making it private.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior {
private:
    class Weapon {
    private:
        string name;
        int strength;
    public:
        Weapon(const string &weaponName, int initialStrength) : name(weaponName), strength(initialStrength) {}
        void weaken(int amount) { strength = max(strength - amount, 0); }
        int getStrength() const { return strength; }
        const string& getName() const { return name; }
    };
    string name;
    Weapon weapon;
public:
    Warrior(const string &warriorName, const string &weaponName, int strength)
            : name(warriorName), weapon(weaponName, strength) {}
    friend ostream &operator<<(ostream &os, const Warrior &warrior);
    const string& getName() const { return name; }
    void conductBattle(Warrior &opponent) {
        cout << name << " battles " << opponent.name << endl;
        if (weapon.getStrength() == 0 && opponent.weapon.getStrength() == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (weapon.getStrength() == 0) {
            cout << "He's dead, " << name << endl;
        } else if (opponent.weapon.getStrength() == 0) {
            cout << "He's dead, " << name << endl;
        } else {
            int originalStrength = weapon.getStrength();
            int opponentOriginalStrength = opponent.weapon.getStrength();
            if (originalStrength == opponentOriginalStrength) {
                cout << "Mutual Annihilation: " << name << " and " << opponent.name << " die at each other's hands" << endl;
                weapon.weaken(originalStrength);
                opponent.weapon.weaken(opponentOriginalStrength);
            } else if (originalStrength > opponentOriginalStrength) {
                cout << name << " defeats " << opponent.name << endl;
                opponent.weapon.weaken(opponentOriginalStrength);
                weapon.weaken(opponentOriginalStrength);
            } else {
                cout << opponent.name << " defeats " << name << endl;
                weapon.weaken(originalStrength);
                opponent.weapon.weaken(originalStrength);
            }
        }
    }
};

/*
* Declaring function definitons
*/
void openfile(ifstream& file);
void readfile(ifstream& file, vector<Warrior>& warriors);
void addWarrior(vector<Warrior>& warriors, const string& warriorName, const string& weaponName, int strength);
size_t findWarrior(const string& name, const vector<Warrior>& warriors);
void conductBattle(Warrior& warrior1, Warrior& warrior2);
void displayStatus(const vector<Warrior>& warriors);

int main() {
    vector<Warrior> warriors;
    ifstream file;
    openfile(file);
    readfile(file, warriors);
    file.close();
}

/*
* Declaring function implementations
*/

/*
* Function to open the input file.
* Opens "warriors.txt" and terminates the program with an error if the file cannot be found.
* @param file Reference to an ifstream object for file operations.
*/
void openfile(ifstream& file) {
    file.open("warriors.txt");
    if(!file) {
        cerr << "there is no filename warriors.txt\n";
        exit(1);
    }
}

/*
* Function to read data from the file and populate a vector of Warrior objects.
* Reads line by line to process commands like "Warrior", "Battle", and "Status".
*
* @param file Reference to ifstream, warriors Reference to vector of Warrior objects to be populated.
*/
void readfile(ifstream& file, vector<Warrior>& warriors) {
    string lines;
    while(file >> lines) {
        if (lines == "Warrior") {
            string warriorName;
            string weaponName;
            int strength;
            file >> warriorName >> weaponName >> strength;
            addWarrior(warriors, warriorName, weaponName, strength);
        } else if (lines == "Battle") {
            string name1;
            string name2;
            file >> name1 >> name2;
            size_t warrior1 = findWarrior(name1, warriors);
            size_t warrior2 = findWarrior(name2, warriors);
            if (warrior1 == warriors.size() || warrior2 == warriors.size()) {
                cerr << "Error: One or both warriors not found for the battle.\n";
            } else {
                conductBattle(warriors[warrior1], warriors[warrior2]);
            }
        } else if (lines == "Status"){
            displayStatus(warriors);
        }
    }
}

/*
* Function to add a new warrior to the collection if not already present.
* Checks for duplicates before adding to prevent multiple entries of the same warrior.
*
* @param warriors Reference to vector of Warriors, warriorName Name of the warrior to add
* @param weaponName Name of the warrior's weapon, strength of the weapon.
*/
void addWarrior(vector<Warrior>& warriors, const string& warriorName, const string& weaponName, int strength) {
    bool warriorExists = false;
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].getName() == warriorName) {
            warriorExists = true;
            break;
        }
    }
    if (!warriorExists) {
        warriors.emplace_back(Warrior(warriorName, weaponName, strength));
    } else {
        cerr << "Error: Warrior " << warriorName << " already exists." << endl;
    }
}

/*
* Function to find a warrior in the collection by name.
* Returns the index of the warrior if found, otherwise returns the size of the vector.
*
* @param name of the warrior to find, warriors Reference to vector of Warriors.
*
* @return Index of the found warrior or the size of the vector.
*/
size_t findWarrior(const string& name, const vector<Warrior>& warriors) {
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].getName() == name) {
            return index;
        }
    }
    return warriors.size(); // return size of vector if not found
}

/*
* Function to simulate a battle between two warriors.
* Uses the conductBattle member function of the Warrior class.
*
* @param warrior1 Reference to the first Warrior, warrior2 Reference to the second Warrior.
*/
void conductBattle(Warrior& warrior1, Warrior& warrior2) {
    warrior1.conductBattle(warrior2);
}

/*
* Function to display the status of all warriors in the collection.
* Outputs the number of warriors followed by details of each warrior.
*
* @param warriors Constant reference to vector of Warriors.
*/
void displayStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors\n";
    for (const Warrior& warrior : warriors) {
        cout << warrior << endl;
    }
}

/*
* Overloads the output stream operator to display details of a Warrior object.
* Formats and sends the warrior's name, weapon name, and weapon strength to the output stream.
*
* @param os Reference to ostream object, warrior const reference to a Warrior
*
* @return Reference to the ostream object
*/
ostream& operator<<(ostream &os, const Warrior &warrior) {
    os << "Warrior: " << warrior.name << ", weapon: " << warrior.weapon.getName()
       << ", " << warrior.weapon.getStrength();
    return os;
}
