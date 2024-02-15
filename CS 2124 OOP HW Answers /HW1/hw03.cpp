/*
hw03.cpp
Natanya Anderson
Section C, Feb 15, 2024
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
        Weapon(const string& name, int strength) : name(name), strength(strength) {}
        void weaken(int amount) { strength = max(strength - amount, 0); }
        int getStrength() const { return strength; }
        string getName() const { return name; }

        };
    string name;
    Weapon weapon;
public:
    friend ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << "Warrior: " << warrior.name << ", weapon: " << warrior.weapon.getName() << ", " << warrior.weapon.getStrength();
        return os;
    }

    Warrior(const string& name, const string& weaponName, int strength)
            : name(name), weapon(weaponName, strength) {}

    const string& getName() const { return name; }
    int getWeaponStrength() const { return weapon.getStrength(); }
    string getWeaponName() const { return weapon.getName(); }
    // Implement the battle logic within the Warrior class as a method
    void conductBattle(Warrior& opponent) {
        cout << name << " battles " << opponent.name << endl;
        if (weapon.getStrength() == 0 && opponent.weapon.getStrength() == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (weapon.getStrength() == 0) {
            cout << "He's dead, " << name << endl;
        } else if (opponent.weapon.getStrength() == 0) {
            cout << "He's dead, " << opponent.name << endl;
        } else {
            if (weapon.getStrength() == opponent.weapon.getStrength()) {
                cout << "Mutual Annihilation: " << name << " and " << opponent.name << " die at each other's hands" << endl;
                weapon.weaken(weapon.getStrength());
                opponent.weapon.weaken(opponent.weapon.getStrength());
            } else if (weapon.getStrength() > opponent.weapon.getStrength()) {
                cout << name << " defeats " << opponent.name << endl;
                opponent.weapon.weaken(opponent.weapon.getStrength());
                weapon.weaken(opponent.weapon.getStrength());
            } else {
                cout << opponent.name << " defeats " << name << endl;
                weapon.weaken(weapon.getStrength());
                opponent.weapon.weaken(weapon.getStrength());
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
/** function that opens file and prints out error message if file is not found and exits the program immediately.
*
* @param file parameter. file is a reference to an input file stream.
*
* @return void function
*/
void openfile(ifstream& file) {
    file.open("warriors.txt");
    if(!file) {
        cout << "there is no filename warriors.txt\n";
        exit(1);
    }
}

/** function processes lines from a file to manage a collection of warriors and their battles. It reads each line of
* the file and holds them in a variable called lines. It enters a loop that continues as long as there is data to be
* read from the file into lines. Inside the loop it checks the content of lines, If lines equals "Warrior", the function
* reads the next parts of the file to get the warriorName, weaponName, and strength for a warrior.
* It then calls the addWarrior function to add this warrior to the warriors vector. If lines equals "Battle", the
* function is meant to handle a battle scenario. It reads the names of the two warriors who will battle from the file.
* It then uses the findWarrior function to get the index positions of these warriors in the warriors vector. If either
* warrior is not found (indicated by findWarrior returning a value equal to the size of the warriors vector), an error
* message is displayed. Otherwise, it calls the conductBattle function with the two warriors. If Lines equals "Status",
* the function calls the displayStatus function to show the status of the warriors.
*
* @param file,warriors parameter. file is a reference to an input file stream. warriors is a reference to a
* vector of Warrior objects.
*
* @return void function
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

/**  function attempts to add a new "Warrior" object to a vector of "Warrior" objects, ensuring no duplicates are added.
* It initializes a boolean variable warriorExists to false, which is used to check if the warrior already exists in the vector.
* IThe function then enters a loop that iterates over the warriors vector using an index size_t index. Inside the loop,
* it checks if any Warrior object in the vector has the same name as warriorName by calling the getName() method on each
* Warrior object. If a Warrior with the same name is found, warriorExists is set to true, and the loop breaks,
* stopping further iteration. After the loop, the function checks the value of warriorExists: If warriorExists is false,
* meaning no warrior with the same name was found in the vector), it creates a new Warrior object with the provided name,
* weapon, and strength, and adds it to the end of the warriors vector using push_back. If warriorExists is true (meaning
* a warrior with the same name already exists in the vector), it outputs an error message to the standard error stream
* (cerr) indicating that the warrior already exists and does not add a duplicate.
*
* @param warriors,warriorName,weaponName,strength parameter. warriors is a reference to a vector of Warrior objects where
* the new warrior will be added. warriorName is a constant reference to a string containing the name of the warrior to
* be added. weaponName is a constant reference to a string containing the name of the warrior's weapon. strength is an
* integer value representing the warrior's strength.
*
* @return void function
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
        warriors.push_back(Warrior(warriorName, weaponName, strength));
    } else {
        cerr << "Error: Warrior " << warriorName << " already exists." << endl;
    }
}

/** function searches for a Warrior object within a vector of Warrior objects that matches a given name. The function
* iterates over the warriors vector, using a loop that goes from index 0 to index less than the size of the vector.
* During each iteration, the function compares the name of the current Warrior object
* (accessed using warriors[index].getName()) to the name passed as a parameter. If a Warrior with the matching name is
* found, the function immediately returns the current index value, which is the position of the Warrior within the vector.
* If the function completes the loop without finding a match (i.e., no warrior with the given name is found),
* it returns the size of the warriors vector.
*
* @param warriorname,warriorvector parameter. name is a constant reference to a string representing the name of the
* warrior to find. warriors is a constant reference to a vector of Warrior objects.
*
* @return index or size of vector
*/
size_t findWarrior(const string& name, const vector<Warrior>& warriors) {
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].getName() == name) {
            return index;
        }
    }
    return warriors.size(); // return size of vector if not found
}

/** the function facilitate a battle between two Warrior objects. Inside the function, it calls a member
* function conductBattle on the warrior1 object, passing warrior2 as an argument.
*
* @param warrior1,warrior2 parameter. Both parameters are each a reference to the Warrior object.
*
* @return void function
*/
void conductBattle(Warrior& warrior1, Warrior& warrior2) {
    warrior1.conductBattle(warrior2);
}

/** function reports the status of all warriors in a collection. It starts by displaying the total number of warriors
* in the collection. Then the function enters a loop that iterates over each Warrior object in the warriors vector.
* The loop iterates over the entire warriors vector and it prints out the name of the warrior, the weapon name, and the
* weapon strength. These attributes are accessed using the corresponding getName, getWeaponName, and getWeaponStrength
* methods of the Warrior class.
*
* @param warrior parameter. a constant reference to a vector of Warrior objects.
*
* @return void function
*/
void displayStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior& warrior : warriors) {
        cout << "Warrior: " << warrior.getName() << ", weapon: " << warrior.getWeaponName() << ", " << warrior.getWeaponStrength() << endl;
    }
}


