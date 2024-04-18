#include <iostream>
using namespace std;

class Base {
public:
    // Base class constructor
    Base() {
        cout << "Base class constructed" << endl;
    }
};

class Derived : public Base {
public:
    // Derived class constructor
    Derived() {
        cout << "Derived class constructed" << endl;
    }
};

int main() {
    // Variables holding instances of each class
    Base baseInstance;
    Derived derivedInstance;

    // Pointer variables initialized to null
    Base* basePtr = nullptr;
    Derived* derivedPtr = nullptr;

    baseInstance = derivedInstance;

    // Trying to assign Base variable to Derived variable (doesn't work, requires explicit downcasting, potentially unsafe)
    // derivedInstance = baseInstance; // Uncommenting this line will cause a compilation error

    // Assigning Derived pointer variable to Base pointer variable
    basePtr = derivedPtr;

    // Trying to assign Base pointer variable to Derived pointer variable (doesn't work without an explicit cast)
    // derivedPtr = basePtr; // Uncommenting this line will cause a compilation error

    // Assigning addresses of each of the objects to the pointer variables
    basePtr = &baseInstance;       // Works, same type
    derivedPtr = &derivedInstance; // Works, same type
    basePtr = &derivedInstance;    // Works, Derived* is implicitly converted to Base*
    // derivedPtr = &baseInstance; // Doesn't work, requires explicit cast to Derived*

};