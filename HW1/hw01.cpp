/*
hw01.cpp
Natanya Anderson
Section C, Feb 1, 2024
Decrypts text that has been encrypted with classic Caesar cypher algorithm
*/
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>

/*
* Declaring function definitons
*/
bool isUpperandNotNegative(char, int);
bool isUpperandNegative(int, char);
char wrapAround(char);
char decrypt_char(char&, int);
void decrypt_string(string&, int);


int main() {
    string line;
    vector<string> lines;
    int num;
    ifstream encrypted_file;
    encrypted_file.open("encrypted.txt"); //open file and check if exists
    if (!encrypted_file) {
        cerr << "encrypted.txt file does not exist.\n";
        exit(1);
    }
    encrypted_file >> num; // take first int into num

    while (getline(encrypted_file, line)) { //reading lines into vector
        lines.push_back(line);

    }
    encrypted_file.close();

    for (size_t index = 0; index < lines.size(); index++) { // passing in line by line starting from bottom and printing out the decrypted text
        string current_line = lines[lines.size() - index - 1];
        decrypt_string(current_line, num);
        cout << current_line << endl;
    }
}

/*
* Declaring function implementations
*/
/** Helper function that is passed in a character + integer and checks if integer is greater than or equal to 0 and
* if character is within the range of uppercase letters A-Z.
*
* @param currchar,offset parameters. currchar holds a single character and offset holds an integer.
*
* @return returns true if these conditions are met and false if not.
*/
bool isUpperandNotNegative(char currchar, int offset) {
    if (offset >= 0 && currchar >= 'A' && currchar <= 'Z') {
        return true;
    } else {
        return false;
    }
}

/** Helper function that is passed in a character + integer and checks if integer is less than 0 and
* if character is within the range of uppercase letters A-Z.
*
* @param currchar,offset parameters. currchar holds a single character and offset holds an integer.
*
* @return returns true if these conditions are met and false if not.
*/
bool isUpperandNegative(int offset, char currchar) {
    if (offset < 0 && currchar >= 'A' && currchar <= 'Z') {
        return true;
    } else {
        return false;
    }
}

/** Helper function that is passed in a character and checks to see if it is less than A, if so, it wraps around the end
* of the alphabet by adding 26 to it. Otherwise, if character is greater than Z, it wraps around the beginning of the
* alphabet by adding 26 to it. If character is already within the range of A-Z, return character as it is.
*
* @param currchar parameter holds a single character that is being checked if it is less than A or greater than Z
* otherwise, return it.
*
* @return returns true if these conditions are met and false if not.
*/
char wrapAround(char currchar) {
    if(currchar < 'A') {
        currchar += 26;
        return currchar;
    } else if(currchar > 'Z'){
        currchar -= 26;
        return currchar;
    } else {
        return currchar;
    }
}

/** Function that is passed in a reference of character and passed in a integer which represents the rotation distance.
* It calls a helper functions that checks if the character is uppercase and the rotation distance is non-negative. If the
* condition is met, it subtracts the integer from the character, reversing the encryption. It then calls another helper
* function that ensures the character stays within the range of uppercase letters after decryption. Otherwise, if the
* character is uppercase but the rotation distance is negative, it again subtracts the integer from the character and
* calls another function to see if wrap around is necessary. If neither condtions are met, it returns the character unchanged.
*
* @param current,num parameters. currchar holds a single character that needs to be checked + decrypted and offset holds
* an integer that represents the rotation distance which needs to be checked and used to decrypt the character.
*
* @return returns the new decrypted character.
*/
char decrypt_char(char& current, int num) {
    if (isUpperandNotNegative(current, num)) {
        current -= num;
        char newcharacter = wrapAround(current);
        return newcharacter;
    }
    else if(isUpperandNegative(num, current)) {
        current -= num;
        char newcharacter = wrapAround(current);
        return newcharacter;
    } else {
        return current;
    }
}

/** Function that is passed in a reference to a string and integer that represents the rotation distance. It iterates
* over each character in the string. For each character, it calls a function that decrypts the character using the
* provided rotation distance. The decrypted character is then assigned back to the original character position in the string.
*
* @param str,num parameters. str holds a refernce to a string that needs to be decrypted and and num holds an integer that
* represents the rotation distance.
*
* @return returns nothing
*/
void decrypt_string(string& str, int num) {
    for (char& chr : str) {
        chr = decrypt_char(chr, num);
    }
}