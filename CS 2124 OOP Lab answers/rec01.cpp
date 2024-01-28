/*
  Natanya Anderson
  rec01_start.cpp
  spring 2024
*/
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>

// Function prototypes for tasks 15-17

// Task 15. Function to display a vector of ints
void passInts(const vector<int> &vect);

// Task 16. Function to modify the vector, using indices
void doubleInts(vector <int> &vect0);

// Task 17. Function to modify the vector, using a ranged for
void doubleInts2(vector <int> &vect1);
//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "Hello World!" << std::endl;


    // Task 2  Printing hello ...  Using "using namespace"
    cout << "Hello World!\n";


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << x << endl;

    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pi = 3.14159;
    cout << sizeof(y) << " " << sizeof(z) << " " << sizeof(pi) << endl;
    // Task 5  Attempt to assign the wrong type of thing to a variable
    //x = "felix"


    //
    // Conditions
    //

    // Task 6  Testing for a range
    if(y >= 10 && y <= 20)
        cout << "y is in between 10 and 20" << endl;

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int x = 10; x <= 20; ++x )
        cout << x << endl;
    // Then with a while loop
    int w = 10;
    while (w <= 20) {
        cout << w << endl;
        ++w;
    }
        // Finally with a do-while loop
    int s = 10;
    do {
    cout << s << endl;
    ++s;
    } while(s <= 20);


    // Task 8  Looping to successfully open a file, asking user for the name
    string filename;
    ifstream file;
    do {
        cout << "Enter the filename? " << endl;
        cin >> filename;
        file.open(filename);
    } while(!file);

    // Task 9  Looping, reading file word by "word".
    string word;
    while (file >> word) {
        cout << word << endl;
    }
    file.close();

    // Task 10 Open a file of integers, read it in, and display the sum.
    string integers;
    ifstream files;
    files.open("integers.txt");
    if(!files) {
        cout << "there is no filename" << endl;
    }
    int sum = 0;
    int num;
    while (files >> num) {
        sum += num;
    }
     cout << sum << endl;
     files.close();



    // Taks 11 Open and read a file of integers and words. Display the sum.
    ifstream mixedfile("mixed.txt");
    if (!mixedfile) {
        cout << "there is no filename" << endl;
    }
    int nums;
    int sum1 = 0;
    string words;
    do {
        sum1 += nums;
        cout << words << " ";
    } while (mixedfile >> nums);
    cout << sum1 << endl;
    mixedfile.close();

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> ints;
    int val = 10;
    while (val < 101) {
        ints.push_back(val);
        val += 2;
    }

    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < ints.size(); i++) {
        cout << ints[i] << " ";
    }
    cout << endl;
    //         b) using a "ranged for"
    for (int n: ints) {
        cout << n << " ";
    }
    cout << endl;
    //         c) using indices again but backwards
    for (size_t k = ints.size(); k > 0; k--) {
        cout << ints[k-1] << " ";
    }
    cout << endl;

    // Task 14. Initialize a vector with the primes less than 20. 
    vector<int> primes{1, 2, 3, 5, 7, 11, 13, 17, 19};
    for (int p: primes) {
        cout << p << " ";
    }
    cout << endl;
    //
    // Function calls
    //

    // Task 15  Function to print a vector
    passInts(primes);

    // Task 16  Function to double the values in a vector
    doubleInts(primes);
    passInts(primes);

    // Task 17  Function to double the values in a vector, using a ranged for 
    doubleInts2(primes);
    passInts(primes);

}

//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints
void passInts(const vector<int> &vect){
    for (int b: vect) {
        cout << b << " ";
    }
    cout << endl;
}


// Task 16. Function to modify the vector, using indices
void doubleInts(vector <int> &vect0){
    for (size_t h = 0; h < vect0.size(); h++){
        vect0[h] *= 2;
    }
    cout << endl;
}


// Task 17. Function to modify the vector, using a ranged for
void doubleInts2(vector <int> &vect1){
    for (int& h : vect1){
        h *= 2;
    }
}

