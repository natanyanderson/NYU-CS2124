/*
 * Natanya Anderson
 * Sterling Lab 1
 * rec02.cpp
 * Given a file of hydrocarbons, maintain one entry for each molecular formula with the formula names
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <string>
using namespace std;


struct Hydrocarbons {
    int carbonAtoms;
    int hydrogenAtoms;
    vector<string> formulaNames;
};

/*
 * Declaring function prototypes
*/
void openfile(ifstream& file);
size_t getLocation(const vector<Hydrocarbons>& myhydros, int carbonNum, int hydrogenNum);
void insertFormulas(vector<Hydrocarbons>& myhydros, int hydrogen, int carbon, const string& formNames);
void fillVector(ifstream& molecules, vector<Hydrocarbons>& myhydros);
void displayFormulas(const Hydrocarbons& Molecule);
void unsortedFormulas(const vector<Hydrocarbons>& myhydros);
void sortedFormulas(vector<Hydrocarbons>& myhydros);

int main() {
    vector<Hydrocarbons> myhydros;
    ifstream file;
    openfile(file);
    cout<<endl;
    fillVector(file, myhydros);
    unsortedFormulas(myhydros);
    cout<<endl;
    sortedFormulas(myhydros);
    file.close();
}

/*
 * Declaring function implementations
 */
void openfile(ifstream& file) {
    string filename;
    do {
       cout << "Enter filename: " << endl;
       cin >> filename;
       file.open(filename);
    } while(!file);
}

size_t getLocation(const vector<Hydrocarbons>& myhydros, int carbonNum, int hydrogenNum){
    for (size_t index = 0; index < myhydros.size(); index++){
        if(myhydros[index].carbonAtoms == carbonNum && myhydros[index].hydrogenAtoms == hydrogenNum){
            return index;
        }
    } return myhydros.size();
}

void insertFormulas(vector<Hydrocarbons>& myhydros, int hydrogen, int carbon, const string& formNames) {
    size_t formulaMatch = getLocation(myhydros, carbon, hydrogen);
    if (formulaMatch == myhydros.size()) {
        vector<string> formulaNames;
        formulaNames.push_back(formNames);
        Hydrocarbons Molecule{carbon, hydrogen, formulaNames};
        myhydros.push_back(Molecule);
    } else {
        myhydros[formulaMatch].formulaNames.push_back(formNames);
    }
}

void fillVector(ifstream& molecules, vector<Hydrocarbons>& myhydros){
    int carbon;
    int hydrogen;
    char carbs;
    char hydros;
    string name;

    while(molecules>>name>>carbs>>carbon>>hydros>>hydrogen){
        insertFormulas(myhydros, hydrogen,carbon,name);
    }
}

void displayFormulas(const Hydrocarbons& Molecule) {
    cout << "C" << Molecule.carbonAtoms << "H" << Molecule.hydrogenAtoms << ' ';
    for (const string& names: Molecule.formulaNames) {
        cout << names << " ";
    }
    cout << endl;
}

void unsortedFormulas(const vector<Hydrocarbons>& myhydros) {
    cout << "Unsorted:" << endl;
    for (const Hydrocarbons& molecule : myhydros){
        displayFormulas(molecule);
    }
}

void sortedFormulas(vector<Hydrocarbons>& myhydros) {
    cout << "Sorted:" << endl;
    for (size_t index = 0; index < myhydros.size() - 1; index++) {
        size_t index1 = index;
        for (size_t num = index + 1; num < myhydros.size(); num++) {
            if (myhydros[num].carbonAtoms < myhydros[index1].carbonAtoms || myhydros[num].carbonAtoms
            == myhydros[index1].carbonAtoms && myhydros[num].hydrogenAtoms < myhydros[index1].hydrogenAtoms) {
                index1 = num;
            }
        }
        swap(myhydros[index], myhydros[index1]);
    }
    for (const Hydrocarbons& molecule : myhydros) {
        displayFormulas(molecule);
    }
}