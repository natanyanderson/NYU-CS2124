/*
  hw045.cpp
  Natanya Anderson
  Section C, Feb 29, 2024
  This program simulates medieval battles between nobles, who can hire, fire, and battle with warriors,
  adjusting the strength of their armies based on the outcomes of these battles.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


// Your Noble and Warrior classes should go here.
class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
    string name;
    double strength;
    bool employed = false;
public:
    Warrior(const string& name, double strength);

    const string& getName() const { return name; }
    double getStrength() const { return strength; }
    void setStrength(double newStrength) { strength = newStrength; }
    bool isEmployed() const { return employed; }
    void setEmployed(bool status) { employed = status; }
};


//Noble class
class Noble {
    friend ostream& operator<< (ostream& os, const Noble& noble);
private:
    string name;
    vector<Warrior *> army;
    bool alive = true;
public:
    Noble(const string &name);
    const string& getName() const {return name; }
    double getStrength(const vector<Warrior*> warriors);
    bool is_alive()const {return alive;}
    /*
     * Declaring function prototypes
    */
    bool hire(Warrior &warrior);
    bool fire(Warrior &warrior);
    void battle(Noble &opponent);
    void loseBattle();
};

/*
* Declaring function prototypes
*/
Warrior* findWarrior(const vector<Warrior*>& warriors, const string& name);
Noble* findNoble(const vector<Noble*>& nobles, const string& name);
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors);
void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors);
void createWarrior(vector<Warrior*>& warriors, double strength, const string& name);
void createNoble(vector<Noble*>& nobles, const string& name);
void helperHire(const string& nameNoble, const string& nameWarrior, const vector<Noble*>& nobles, vector<Warrior*>& warriors);
void helperFire(const string& nameNoble, const string& nameWarrior, const vector<Noble*>& nobles, vector<Warrior*>& warriors);
void helperBattle(const string& nameNoble1, const string& nameNoble2, const vector<Noble*>& nobles);


int main() {
    vector<Warrior*> warriors;
    vector<Noble*> nobles;

    ifstream file("nobleWarriors.txt");
    if (!file) {
        cerr << "file named nobleWarriors.txt not found" << endl;
        exit(1);
    }
    //Read input file
    string word,nameNoble,nameWarrior;
    while (file >> word){
        if (word == "Noble"){
            file >> nameNoble;
            createNoble(nobles, nameNoble);
        } else if (word == "Warrior"){
            double strength;
            file >> nameNoble >> strength;
            createWarrior(warriors, strength, nameNoble);
        } else if (word == "Hire"){
            file >> nameNoble >> nameWarrior;
            helperHire(nameNoble, nameWarrior, nobles, warriors);
        } else if (word == "Fire"){
            file >> nameNoble >> nameWarrior;
            //check if Noble or Warrior exist
            helperFire(nameNoble, nameWarrior, nobles, warriors);
        } else if (word == "Status"){
            //Check status
            status(nobles,warriors);
        } else if (word == "Battle"){
            //Start battle
            string nameNoble1, nameNoble2;
            file >> nameNoble1 >> nameNoble2;
            //Battle
            helperBattle(nameNoble1, nameNoble2, nobles);
        } else {
            clear(nobles,warriors);
        }
    }
    file.close();
}

//Warrior class constructor
Warrior::Warrior(const string& name, double strength) : name(name), strength(strength){}
//output operator for Warrior class
ostream& operator<<(ostream&os, const Warrior& warrior) {
    os << "    " << warrior.name << ": " << warrior.strength << endl;
    return os;
}
//Noble class constructor
Noble::Noble(const string &name) : name(name), alive(true) {}
//output operator for Noble class
ostream& operator<<(ostream&os, const Noble& noble) {
    size_t armySize = noble.army.size();
    os << noble.name << " has an army size of " << armySize << endl;
    for(const Warrior* warrior: noble.army) {
        os << *warrior;
    }
    return os;
}

/*
* Declaring function implementations
*/

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
    if(warrior.isEmployed() == true) {
        cout << name << " has already been hired." << endl;
        return false;
    }
    warrior.setEmployed(true);
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
        cout << name << " cannot fire warrior because they are dead." << endl;
        return false;
    }

    for (size_t index = 0; index < army.size(); ++index) {
        if (army[index] == &warrior) {
            cout << warrior.getName() << ", you don't work for me any more! -- "<< name << "." << endl;
            warrior.setEmployed(false);
            // Shift all warriors one place to the left to overwrite the fired warrior
            for (size_t index2 = index; index2 < army.size() - 1; ++index2) {
                army[index2] = army[index + 1];
            }
            army.erase(army.begin() + index); // Remove the last warrior, now a duplicate
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
void Noble::battle(Noble& opponent) {
    cout << name << " battles " << opponent.name << endl;

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
    double myStrength = getStrength(army);
    double opponentStrength = opponent.getStrength(opponent.army);

    if (myStrength == opponentStrength) {
        cout << "Mutual Annihilation: " << name << " and " << opponent.getName() << " die at each other's hands" << endl;
        alive = false;
        opponent.alive = false;
        loseBattle();
        opponent.loseBattle();
    } else if (myStrength > opponentStrength) {
        cout << name << " defeats " << opponent.getName() << endl;
        double ratio = opponentStrength/myStrength;
        for (Warrior* warrior : army) {
            double newStrength = warrior->getStrength() * (1 - ratio);
            warrior->setStrength(newStrength);
        }
        opponent.alive = false;
        opponent.loseBattle();
    } else {
        cout << opponent.getName() << " defeats " << name << endl;
        double ratio = myStrength/opponentStrength;
        for (Warrior* warrior : army) {
            double newStrength = warrior->getStrength() * (1 - ratio);
            warrior->setStrength(newStrength);
        }
        alive = false;
        loseBattle();
    }
}

/** This function modifies the strength of each warrior to 0 in a noble's army after losing a battle and
* setting the employment status to false as well as the alive vairable.
*
* @param none
*
* @return void function
*/
void Noble::loseBattle() {
    for (Warrior *warrior: army) {
        warrior->setStrength(0); // Set each warrior's strength to 0
        warrior->setEmployed(false); // Mark warriors as unemployed
    }
    alive = false; // Mark the noble as dead
}

/** This function calculates and returns the total strength of a group of warriors. It takes a vector of pointers to
* Warrior objects.
*
* @param warriors , vector of pointers to Warrior objects
*
* @return double
*/
double Noble::getStrength(const vector<Warrior*> warriors) {
    double strength = 0;
    for(const Warrior* warrior : warriors) {
        strength += warrior -> getStrength();
    }
    return strength;
}

/** The createWarrior function is designed to add a new Warrior object to a vector of Warrior pointers, but only if
* there is no existing warrior with the same name in the vector.
*
* @param warriors, strength, name
*
* @return void
*/
void createWarrior(vector<Warrior*>& warriors, double strength, const string& name) {
    bool existing = false;
    for (const Warrior* warrior : warriors) {
        if (warrior->getName() == name) {
            existing = true;
            cout << "Warrior " << name << " is already inside." << endl;
            break;
        }
    } if (!existing) {
        warriors.push_back(new Warrior(name, strength));
    }
}
/** The createNoble function is designed to add a new Noble object to a vector of Noble pointers, but only if
* there is no existing warrior with the same name in the vector.
*
* @param nobles, name
*
* @return void
*/
void createNoble(vector<Noble*>& nobles, const string& name) {
    bool existing = false;
    for(const Noble* noble : nobles) {
        if(noble->getName() == name) {
            existing = true;
            cout << "Noble " << name << " is already inside." << endl;
            break;
        }
    } if(!existing) {
        nobles.push_back(new Noble(name));
    }
}

/** this helper function searches through a vector of pointers to Warrior objects to find a warrior with a specific name.
*
* @param warriors, name
*
* @return noble or nullptr if not found.
*/
Warrior* findWarrior(const vector<Warrior*>& warriors, const string& name) {
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index]->getName() == name) {
            return warriors[index]; // Noble found, return noble
        }
    }
    return nullptr; // Noble not found, return indicator
}

/** this helper function searches through a vector of pointers to Noble objects to find a Noble with a specific name.
*
* @param nobles, name
*
* @return noble or nullptr if not found.
*/
Noble* findNoble(const vector<Noble*>& nobles, const string& name) {
    for (size_t index = 0; index < nobles.size(); ++index) {
        if (nobles[index]->getName() == name) {
            return nobles[index]; // Noble found, return noble
        }
    }
    return nullptr;
}

/** this helper function It looks up a noble and a warrior by their names in respective vectors of Noble* and Warrior*.
* If both are found, it proceeds with the hiring by invoking the hire method on the noble object with the warrior object
* as an argument. If the warrior does not exist, it notifies the user that an attempt was made to hire an unknown warrior.
* Conversely, if the noble does not exist, it informs the user that the hiring failed because the specified noble does not
* exist.
*
* @param nameNoble, nameWarrior, nobles, warriors
*
* @return void
*/
void helperHire(const string& nameNoble, const string& nameWarrior, const vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    Noble* noble = findNoble(nobles, nameNoble);
    Warrior* warrior = findWarrior(warriors, nameWarrior);
    if(noble && warrior) {
        noble->hire(*warrior);
    } else if (noble && (warrior == nullptr)) {
        cout << "Attempting to hire using unknown warrior: " << nameWarrior << endl;
    } else if ((noble == nullptr) && warrior) {
        cout << "Hire failed, Noble " << nameNoble << " does not exist." << endl;
    }
}

/** this helper function first locates both the noble and warrior by name. If the noble is not found, it outputs a message indicating the
* noble does not exist, preventing any action. If the noble is found but the warrior is not, it similarly reports that
* the warrior does not exist. Only if both the noble and warrior are found does it proceed to fire the warrior by
* invoking the noble's fire method.
*
* @param nameNoble, nameWarrior, nobles, warriors
*
* @return void
*/
void helperFire(const string& nameNoble, const string& nameWarrior, const vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    Noble* noble = findNoble(nobles, nameNoble);
    Warrior* warrior = findWarrior(warriors, nameWarrior);
    if(noble == nullptr) {
        cout << "Noble doesn't exist, can't fire Noble.\n";
    } else if (warrior == nullptr) {
        cout << "Warrior doesn't exist, can't fire Warrior.\n";
    } else {
        noble->fire(*warrior);
    }
}

/** this helper function first locates both nobles and if they are both not found an error message will output. If both,
* nobles exist, it proceeds to initiate a battle between them by calling the battle method on noble1, passing noble2 as the argument.
*
* @param nameNoble1, nameNoble2, nobles
*
* @return void
*/
void helperBattle(const string& nameNoble1, const string& nameNoble2, const vector<Noble*>& nobles) {
    Noble* noble1 = findNoble(nobles, nameNoble1);
    Noble* noble2 = findNoble(nobles, nameNoble2);
    if (noble1 == nullptr || noble2 == nullptr) {
        cout << "One or more nobles does not exist." << endl;
    } else {
        noble1->battle(*noble2);
    }
}

/** this function reports the current status of nobles and warriors, detailing which nobles exist and
* highlighting unemployed warriors
*
* @param nobles, warriors
*
* @return void
*/
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors){
    cout << "Status\n" << "======\n" << "Nobles:" << endl;
    if (nobles.size() != 0) {
        for (Noble* noble: nobles){
            cout << *noble << endl;
        }
    } else {
        cout << "NONE\n" << endl;
    }
    cout << "Unemployed Warriors:" << endl;
    bool unEmployedWarrior = false;

    for (const Warrior* warrior: warriors){
        if (warrior->isEmployed()){
            cout << *warrior << endl;
            unEmployedWarrior = true;
        }
    }
    if (!unEmployedWarrior){
        cout << "NONE";
    }
}

/**  designed to thoroughly clean up all dynamically allocated objects held within two vectors: one containing pointers
* to Noble objects and the other containing pointers to Warrior objects. This function ensures that memory allocated for
* both nobles and warriors is properly released, and then it clears the vectors to remove all pointers.
*
* @param nobles, warriors
*
* @return void
*/
void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    for (size_t index = 0; index < nobles.size(); ++index) {
        delete nobles[index];
    }
    nobles.clear();
    for (size_t index = 0; index < warriors.size(); ++index) {
        delete warriors[index];
    }
    warriors.clear();
}
