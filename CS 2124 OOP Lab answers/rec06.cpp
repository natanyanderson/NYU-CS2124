/*
  rec06_begin.cpp
  CS2124
  Natanya Anderson
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

// 
// Position class
// 
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs)
    {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    } // Position op<<
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position


// 
// Directory class
// 
class Directory {
    friend ostream& operator<<(ostream& os, const Directory& directory) {
        os << "Directory: " << directory.company << endl;
        for (size_t index = 0; index < directory.size; ++index){
            os << *(directory.entries[index]) << endl;
        }
        return os;
    }
//
// nested Entry class
//
    class Entry {
        friend ostream& operator<<(ostream& os, const Entry& rhs)
            {
            os << rhs.name << ' ' << rhs.room
                << ' ' << rhs.phone << ", " << *rhs.pos;
            return os;
        } // Entry op<<
    public:
        Entry(const string& name, unsigned room, unsigned phone, Position& position)
            : name(name), room(room), phone(phone), pos(&position) {
        }
        const string& getName() const { return name; }
        unsigned getPhone() const { return phone; }
        private:
        string name;
        unsigned room;
        unsigned phone;
        Position* pos;
        }; // class Entry


public:
// Of course the first function you need to write for this (or
// any) class is...
// ???
// ...
    Directory(const string& companyName = "Unknown")
        : size(0), capacity(8), company(companyName), entries(new Entry*[8]) {}

    Directory(const Directory& rhs)     // copy constructor
        : size(rhs.size),
            capacity(rhs.capacity),
            entries(new Entry*[rhs.capacity]) {
        cout << "Copy Constructor..." << endl;
        for (size_t i = 0; i < size; i++) {
            entries[i] = new Entry(*rhs.entries[i]); } // deep copy
        }

        // assigment operator
    Directory& operator=(const Directory& rhs) {
        cout << "Assigment Operator..." << endl;
            // check for self assignment
       if (&rhs != this) {
           // free up our resources
           for (size_t i = 0; i < size; i++) {
               delete entries[i];
           }
            delete[] entries;
            // allocate new resources
            entries = new Entry*[rhs.capacity];
            // copy over any information
            size = rhs.size;
            capacity = rhs.capacity;
            for (size_t i = 0; i < size; i++) {
                entries[i] = new Entry(*rhs.entries[i]);
            }
        }
        return *this;
    }
    // Default constructor
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)    {
            // something is missing!!!  Add it!
            capacity *= 2; // Double the capacity
            Entry** newEntries = new Entry*[capacity]; // Allocate new array with updated capacity

            for (size_t index = 0; index < size; ++index) {
            newEntries[index] = entries[index]; // Copy pointers to the new array
            }

            delete[] entries; // Delete old array
            entries = newEntries; // Update entries to point to the new array}
        }
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    }

    unsigned operator[](const string& name) const {
        for (size_t index = 0; index < size; index++) {
        // check if entry with the name provided exists
            if (entries[index]->getName() == name) {
                return entries[index]->getPhone();
            }
        }
        return 99999;  // avoid failing silently
    }// add
    // destructor
    ~Directory() {
    cout << "Destructor..." << endl;
        // free up space on heap
        for (size_t i = 0; i < size; i++) {
        delete entries[i];
        }
        delete[] entries;
    }
//
// === Copy Control ===
//
// (get checked out on everything else before starting this)


private:
    Entry** entries; // Notice the type!!! Pointer to Entry pointers.
    size_t size;
    size_t capacity;
    string company;

}; // class Directory

void doNothing(Directory dir) {


    // You need to overload the Directory output operator before
    // uncommenting the next line.

      cout << dir << endl;
}   // doNothing

int main() {

// Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);


        // Create a Directory
    Directory d("HAL");
    // Add someone
    d.add("Marilyn", 123, 4567, boss);
    // print the directory
    cout << d << endl;
    // Use the square bracket operator, aka the Index operator,
    // to access someone's phone extension.
    cout << "d[\"Marilyn\"]: " << d["Marilyn"] << endl;
    cout << "======\n\n";

    // Everything working so far? Get checked out!!!

    Directory d2 = d;    // What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << "Directory d:\n" << d << endl;
    cout << "Directory d2:\n" << d2 << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    // Should display 1592
    cout << d2["Carmack"] << endl;

    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);


    d2 = d3;
    // Should display 5813
    cout << d2["Ritchie"] << endl;

    cout << d2 << endl;
}
// main