/*
hw02.cpp
Natanya Anderson
Section C, Feb 8, 2024
This program reads the input file "warriors.txt" to calculate battles and status amongst the warriors.
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Warriorsinfo {
    string Warriorname;
    int strength;
};

/*
* Declaring function definitons
*/
void openfile(ifstream& file);
void readfile(ifstream& file, vector<Warriorsinfo>& warriors);
void addWarrior(vector<Warriorsinfo>& warriors,string& warriorName, int& strength);
size_t findWarrior(string& name, vector<Warriorsinfo>& warriors);
void conductBattle(Warriorsinfo& warrior1, Warriorsinfo& warrior2);
void displayStatus(vector<Warriorsinfo>& warriors);

int main() {
    vector<Warriorsinfo> warriors;
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
* @param file parameter.
*
* @return void function
*/
void openfile(ifstream& file) {
    file.open("warriors.txt");
    if(!file) {
        cout << "there is filename warriors.txt\n";
        exit(1);
    }
}

/** function processes commands from a file to manage a collection of warriors and their battles. It reads each line of
* the type of command: creating warriors, initiating battles, or displaying the status of all warriors.
* If the line starts with "Warrior", the function reads the following name and strength of the warrior and calls
* addWarrior to add the warrior to the collection. If the line starts with "Battle", the function reads the names of the
* two warriors who will battle. It locates these warriors using findWarrior, then calls conductBattle with the found
* warriors. If the line does not start with "Warrior" or "Battle", it calls displayStatus of all warriors.
*
* @param file,warriorvector parameter
*
* @return void function
*/
void readfile(ifstream& file, vector<Warriorsinfo>& warriors) {
    string lines;
    while(file >> lines) {
        if (lines == "Warrior") {
            string name;
            int strength;
            file >> name >> strength;
            addWarrior(warriors, name, strength);
        } else if (lines == "Battle") {
            string name1;
            string name2;
            file >> name1 >> name2;
            size_t warrior1 = findWarrior(name1, warriors);
            size_t warrior2 = findWarrior(name2, warriors);
            conductBattle(warriors[warrior1], warriors[warrior2]);
        } else {
            displayStatus(warriors);
        }
    }
}

/**  function attempts to add a new warrior with a given name and strength to a collection of warriors. The function
* first checks if a warrior with the provided name already exists in the collection using the findWarrior function.
* If the warrior does not exist  (indicated by findWarrior returning -1), the new warrior is added to the collection
* with the specified name and strength. If a warrior with the same name already exists, the function outputs an error
* message to the standard error stream (cerr) and does not add the duplicate warrior to the collection.
*
* @param warriorvector,warriorName,strength parameter
*
* @return void function
*/
void addWarrior(vector<Warriorsinfo>& warriors,string& warriorName, int& strength) {
    if (findWarrior(warriorName, warriors) == -1) {
        warriors.push_back({warriorName, strength});
    } else {
        cerr << "Error: Warrior " << warriorName << "already exists." << endl;
    }
}

/**  function searches for a warrior by name within a collection of warriors and returns the index of the warrior if found.
* It iterates through each warrior in the given vector of Warriorsinfo, comparing the Warriorname of each warrior with
* the target name. If a warrior with the matching name is found, the function immediately returns the index of this
* warrior in the vector. If no warrior with the given name is found after checking the entire vector, the function
* returns -1 as an indicator of this.
*
* @param warriorname,warriorvector parameter
*
* @return index or -1
*/
size_t findWarrior(string& name, vector<Warriorsinfo>& warriors){
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].Warriorname == name) {
            return index;
        }
    }
    return -1; // return -1 if not found
}

/** function simulates a battle between two warriors and updates their strengths based on the outcome. It starts by
* announcing the battle between the two warriors, displaying their names. If both warriors have a strength of 0, it
* declares that they are both already dead. If one of the warriors already has a strength of 0, it declares that the dead
* warrior cannot fight. If both warriors have equal strength and are both alive, the function declares that
* they annihilate each other in battle, setting both of their strengths to 0. If one warrior has more strength
* han the other, the function declares the stronger warrior as the winner. The winning warrior's strength is decreased
* by the strength of the losing warrior  (who then has their strength set to 0), simulating the winner's victory but at a cost.
*
* @param warrior1,warrior2 parameter
*
* @return void function
*/
void conductBattle(Warriorsinfo& warrior1, Warriorsinfo& warrior2) {
    cout << warrior1.Warriorname << " battles " << warrior2.Warriorname << endl;
    if (warrior1.strength == 0 && warrior2.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << std::endl;
    } else if (warrior1.strength == 0) {
        cout << "He's dead, " << warrior1.Warriorname << std::endl;
    } else if (warrior2.strength == 0) {
        cout << "He's dead, " << warrior2.Warriorname << std::endl;
    } else if (warrior1.strength == warrior2.strength) {
        cout << "Mutual Annihilation: " << warrior1.Warriorname << " and " << warrior2.Warriorname << " die at each other's hands" << std::endl;
        warrior1.strength = warrior2.strength = 0;
    } else if (warrior1.strength > warrior2.strength) {
        cout << warrior1.Warriorname << " defeats " << warrior2.Warriorname << std::endl;
        warrior1.strength -= warrior2.strength;
        warrior2.strength = 0;
    } else {
        cout << warrior2.Warriorname << " defeats " << warrior1.Warriorname << std::endl;
        warrior2.strength -= warrior1.strength;
        warrior1.strength = 0;
    }
}

/** function reports the status of all warriors in a collection. It starts by displaying the total number of warriors
* in the collection. For every warrior in the collection, it lists the warrior's name along with their current strength.
*
* @param warriorvector parameter
*
* @return void function
*/
void displayStatus(vector<Warriorsinfo>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warriorsinfo& warrior: warriors) {
        cout << "Warrior: " << warrior.Warriorname << ", strength: " << warrior.strength << endl;
    }
}