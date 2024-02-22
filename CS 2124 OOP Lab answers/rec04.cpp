// Task 1
// Who are you? What is this program called?
/*
Natanya Anderson
rec04.cpp
Task based recitation
*/

// I have stopped using cerr in your started code because CLion makes
// a mess with it.

#include <iostream>   // needed for task 2
#include <vector> // needed for task 27
using namespace std;  // needed for task 2

// Task 16 Complex definition
struct Complex {
    double real;
    double img;
};


// Task 17 PlainOldClass definition
class PlainOldClass {
public:
    PlainOldClass() : x(-72) {}
    int getX() const { return x; } //constant member function, calling this function will not modify any member variables of the object
    void setX( int val )  { x = val; }
private:
    int x;
};

// Task 18 PlainOldClass2 definition
class PlainOldClassV2 {
public:
    PlainOldClassV2() : x(-72) {}
    int getX() const { return x; }
    //void setX( int x )  { x = x; } // HMMMM??? //assigning parameter x to itself, not class member "x". parameter "x" shadows the "x" leading
    //compiler to interpret both "x" refrences as the parameter.
    void setX( int x )  { this->x = x; } //accesses the member variable "x" of the expression.
private:
    int x;
};

// Task 28 Colour definition
class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b) //function does not modify string arugment
        : name(name), r(r), g(g), b(b) {} //initializer list to directly initialize the class's member variables with the values provided as arguments.
void display() const {
    cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
}
private:
string name;      // what we call this colour
unsigned r, g, b; // red/green/blue values for displaying
};

// Task 29 SpeakerSystem definition
class SpeakerSystem {
public:
    void vibrateSpeakerCones(unsigned signal) const {
        cout << "Playing: " << signal << "Hz sound..." << endl;
        cout << "Buzz, buzzy, buzzer, bzap!!!\n";
    }
};

// Task 29 Amplifier definition
class Amplifier {
public:
    void attachSpeakers(const SpeakerSystem& spkrs) {
        if(attachedSpeakers)
            cout << "already have speakers attached!\n";
        else
            attachedSpeakers = &spkrs;
    }

    void detachSpeakers() {
        if (!attachedSpeakers)
            cout << "No speakers to detach.\n";
        else
            attachedSpeakers = nullptr;
    }

    void playMusic() const {
        if (attachedSpeakers)
            attachedSpeakers->vibrateSpeakerCones(440);
        else
            cout << "No speakers attached\n";
    }

private:
    const SpeakerSystem* attachedSpeakers = nullptr;
};

// Task 30 Person Definition
class Person {
public:
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        roomie = &newRoomate;        // now I have a new roomie
        newRoomate.roomie = this;    // and now they do too
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie;
    string name;
};


int main() {
    cout << "Task 1\n";

    // Task 2
    cout << "Task 2\n";
    // Add code here
    int x; //before execution of next line, x = 1. 1 is "garbage value".
    x = 10;
    cout << "x = " << x << endl;


    // Task 3
    cout << "Task 3\n";
    // Using the debugger, set a breakpoint in main and run to
    // it. Observe the value of x.
    // [No new code]

    // Task 4
    cout << "Task 4\n";
    // Using the debugger, step forward observing the value of x
    // [No new code]
    // Task 5
    cout << "Task 5\n";
    // Watch window. Xcode equivalent? Gdb equivalent?
    // Activity: see x's value
    // [No new code]
    // When you declare a variable int x; in c+, the complier reserves a space in the computer's memory to store the value of "x".
    // Upon assignment, the value "10" is stored in the memory location that was reserved for "x".
    // Task 6
    cout << "Task 6\n";
    // Watch window to see the address of x
    // [No new code]
    // memory address of x is 0x00007ffee07eeb0c
    // Task 7
    cout << "Task 7\n";
    // Watch window to see the value stored at the address of x
    // [No new code]

    // Task 8
    cout << "Task 8\n";
    // Add code. here
    int* p;
    p = &x;
    cout << "p = " << p << endl;
    // same address as x, p is a pointer to an int and is set to the address location of x.
    //all pointers must be pointers to some other type.
    // Task 9
    cout << "Task 9\n";
    // Using the value you observe in &x, write a line of code to
    // directly assign that value to p. E.g. p = 0x0012fed4;
    // What happens? Should have a compiler error.
    //p = 0x7ffeed866b0c;
    //p = 10000000000000;

    // Task 10
    cout << "Task 10\n";
    // Run earlier print statement for "p = ". Observe the watch
    // window.
    // Then add code here:
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;
    // Task 11
    cout << "Task 11\n";
    // Add code here
    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;
    //cout << "x now contains " << &x << endl;
    //cout << "p now contains " << &p << endl;
    //this happened because p is a pointer to x which contains x's address so changing one will change the other. p and x
    //contains the same memory location.
    // Task 12
    cout << "Task 12\n";
    // Add code
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;

    // Task 13
    cout << "Task 13\n";
    // Add code here
    int* q;
    q = p; // q and p point to the same place as y
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;


    // Task 14
    cout << "Task 14\n";
    // Add code here
    double d(33.44);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p  = *pD;
    *q  = *p;
    //pD  = p; //compliation error
    //p   = pD; //compliation error
    //double* cannot be cast to an int* and viceversa
    // Task 15
    cout << "Task 15!!!\n"; // Yes, this is a VERY IMPORTANT task!
    // Const and pointers.
    // Add code here
//    int joe = 24;
//    const int sal = 19;
//    int*  pI;
//    pI = &joe;
//    *pI = 234;
//    pI = &sal; //compilation error : trying to assign a pointer to an int to a constant int. Two different types.
//    *pI = 7623;
//    const int* pcI;
//    pcI = &joe;
//    *pcI = 234; //trying to assign a const int pointer to a defined value
//    pcI = &sal;
//    *pcI = 7623; //trying to assign a const int pointer to a defined value
//
//    int* const cpI; //trying to define as a constant pointer to an int. once cpI is initalized, it cannot point to a different int value.
//    //constant pointer must be initialized at point of declaration. have to specify what it points to at time of declaration.
//    int* const cpI(&joe); //redefinition of cpI. have to initalize at first declaration.
//    int* const cpI(&sal); //redefinition of cpI. have to initalize at first declaration.
//    cpI = &joe; //cpI is a consant pointer to an int. cant do this.
//    *cpI = 234;
//    cpI = &sal; //cpI is a consant pointer to an int. cant do this.
//    *cpI = 7623;
//    const int* const cpcI; //have to delclare initalization here//constant pointer to constant int
//    const int* const cpcI(&joe); //have to declare initialization at start
//    const int* const cpcI(&sal); //have to declare initialization at start
//    cpcI = &joe; //can't assign constant pointer to be changed to a different value after initalization
//    *cpcI = 234; //can't reassign constant pointer to constant int
//    cpcI = &sal; //can't assign constant pointer to be changed to a different value after initalization
//    *cpcI = 7623; //can't reassign constant pointer to constant int
//
    // Task 16
    cout << "Task 16\n";
    // Pointers to user-defined types.  Add the type for struct Complex above.
    // Add code here
    Complex c = {11.23,45.67};
    Complex* pC(&c);
    //cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl; //precedence of operator is gicving problem. * has Lower precedence than the operator.
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl; //dereference operator for pointer to a struct or class.
    // Task 17
    cout << "Task 17\n";
    // Add code here
    // What is this code doing?
    PlainOldClass poc; //creating an object named "poc" of type "PlainOldClass"
    PlainOldClass* ppoc( &poc ); //A pointer named "ppoc" is created and initialized to point to address of "poc".
    cout << ppoc->getX() << endl; //getting access to getX() member function through the pointer ppoc. This returns -72.
    ppoc->setX( 2837 ); //calling setX() member function in class that ppoc points to which sets x to 2837.
    cout << ppoc->getX() << endl; //getting access to getX() member function through the pointer ppoc. This returns 2837.

    // Task 18
    cout << "Task 18\n";
    // Test the changes to PlainOldClass
    //this pointer is a pointer to a current instance of the class, which allows you to distinguish between class members
    // and parameters or local variables with the same name.
    PlainOldClassV2 poc2; //creating an object named "poc" of type "PlainOldClass"
    PlainOldClassV2* ppoc2( &poc2 ); //A pointer named "ppoc" is created and initialized to point to address of "poc".
    cout << ppoc2->getX() << endl; //getting access to getX() member function through the pointer ppoc. This returns -72.
    ppoc2->setX( 2837 ); //calling setX() member function in class that ppoc points to which sets x to 2837.
    cout << ppoc2->getX() << endl;
    // Task 19
    cout << "Task 19\n";
    // creating and modifying an item on the heap. Use the debugger to
    // observe.
    // Add code here
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;
    cout << "The " << *pDyn
         << " is stored at address " << pDyn
         << " which is in the heap\n";
    // Task 20
    cout << "Task 20\n";
    // What happens to pDyn in the following? With most compilers it
    // is unchanged.  Visual Studio actually changes it. (I should
    // check if that is just in debug mode.)
    // Add code here
    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;
    cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";

    // Task 21
    cout << "Task 21\n";
    // Add code here
    pDyn = nullptr;
    double* pDouble = nullptr;

    // Task 22
    cout << "Task 22\n";
    // Add code here
    //cout << "Can we dereference nullptr?  " << *pDyn << endl;
    //cout << "Can we dereference nullptr?  " << *pDouble << endl;

    // Task 23
    cout << "Task 23\n";
    // Question. Can <code>this</code> be nullptr?
    //"this" pointer can be nullptr because it's the address of the object that a method is evoked on. It has to point to something.

    // Task 24
    cout << "Task 24\n";
    // Add code here
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest; // safe

    // Task 25
    cout << "Task 25\n";
    // Add code here
    short* pShrt = new short(5);
    //delete pShrt;
    delete pShrt;

    // Task 26
    cout << "Task 26\n";
    // Add code here
    long jumper = 12238743;
    //delete jumper; //delete dellocates memory that was previously allocated with new. Since jumper is not pointer and not allocated with new you cant do this.
    long* ptrTolong = &jumper;
    //delete ptrTolong;  // Not allocated with new so can't do this
    Complex cmplx;
    //delete cmplx;      // Complex is stack allocated and not allocated with new so can't do this.


    // Task 27
    cout << "Task 27\n";
    // Add code here
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        tmpPCmplx = new Complex; // create a new Complex object on the heap
        tmpPCmplx->real = ndx;   // set real and img to be the
        tmpPCmplx->img  = ndx;   // value of the current ndx
        complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
    // release the heap space pointed at by the pointers in the vector// no dangling pointers
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx]; //⚠︎important
    }
    // clear the vector
    complV.clear();
    //.clear() does NOT delete on the things inside the vector
    //programmer must delete each object stored on the heap by deleting pointer value stored in the vector

    // Task 28 Use the Colour class
    cout << "Task 28\n";
    // Add Colour class above main
    // Add code here
    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    }

    // display all the Colours in the vector:
   //free up memeories on heap
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
        delete colours[ndx];
    }

    // Task 29 Use SpeakerSystem and Amplifier classes

    cout << "Task 29\n";
    // Add SpeakerSystem and Amplifier classes above main
    SpeakerSystem spk1, spk2;
    Amplifier amp1;
    cout << "Speaker initialize" << endl;
    spk1.vibrateSpeakerCones(1);
    spk2.vibrateSpeakerCones(99);

    cout << "\nAmplifier attach and play test" << endl;
    amp1.attachSpeakers(spk1);
    amp1.attachSpeakers(spk2); // This will print "already have speakers attached!"
    amp1.playMusic(); // Plays music through spk1

    cout << "\nAmplifier detach and playMusic error test" << endl;
    amp1.detachSpeakers();
    amp1.playMusic(); // No speakers attached

    // Task 30 Use the Person class

    cout << "Task 30\n";
    // Add Person class above main
    // Add code here
    Person joeBob("Joe Bob"), billyJane("Billy Jane");

    // now model these two becoming roommates
    joeBob.movesInWith(billyJane);

    // did this work out?
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
}



