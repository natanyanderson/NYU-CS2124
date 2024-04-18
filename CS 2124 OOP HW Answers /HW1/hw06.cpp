/*
  hw06.cpp
  Natanya Anderson
  Operator overloading the BigUnsigned class
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BigUnsigned {
public:
    //Function prototype for member functions
    void removeLeadingZeros();
    BigUnsigned(int val = 0);
    friend ostream &operator<<(ostream &os, const BigUnsigned &number);
    BigUnsigned(const string &str);
    // Plus-equals operator
    BigUnsigned& operator+=(const BigUnsigned &rhs);
    // Pre-increment operator
    BigUnsigned& operator++();
    // Post-increment operator
    BigUnsigned operator++(int);
    explicit operator bool() const;
    // Comparison operators
    friend bool operator==(const BigUnsigned& rhs, const BigUnsigned& lhs);
    friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);
private:
    vector<int> digits;
};

//Function prototypes for non-members
bool operator==(const BigUnsigned& rhs, const BigUnsigned& lhs);
BigUnsigned operator+(BigUnsigned lhs, const BigUnsigned& rhs);
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs);
// Put your class and all function definitions here.

int main() {
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;

    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b
        << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
        << "zero == one: " << (zero == one) << endl
        << "a == a: " << (a == a) << endl
        << "a == d: " << (a == d) << endl
        << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
        << "(one == 0): " << (one == 0) << endl
        << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
        << "x == a: " << (x == a) << endl
        << "a == x: " << (a == x) << endl
        << "a < x: " << (a < x) << endl
        << "a > x: " << (a > x) << endl;

    cout << "x > a: " << (x > a) << endl
        << "x >= a: " << (x >= a) << endl
        << "x <= a: " << (x <= a) << endl
        << "x != a: " << (x != a) << endl;


    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
        << "big2: " << big2 << endl
        << "big3: " << big3 << endl
        << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
        << "(big5 + big6): " << (big5 + big6) << endl
        << "(big6 + big5): " << (big6 + big5) << endl;


    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
};

//Function implementations

/** This function is an overload of stream insertion operator (<<) for the ostream class and enables objects of
* of BigUnsigned to be output to standard output streams. It iterates over digits in reverse and outputs each digit.
*
* @param os, number. os reference and const reference number
*
* @return ostream&
*/
ostream &operator<<(ostream &os, const BigUnsigned &number) {
    for (int index = number.digits.size() - 1; index >= 0; --index) {
        os << number.digits[index];
    }
    return os;
}

/** This function compares two BigUnsigned numbers and determine if the left-hand side (lhs) is less than the right-hand
* side (rhs).
*
* @param lhs, rhs. const reference lhs and const reference rhs
*
* @return bool
*/
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    if (lhs.digits.size() != rhs.digits.size()) {
        return lhs.digits.size() < rhs.digits.size();
    }
    if (lhs.digits.empty()) {
        for (size_t index = lhs.digits.size(); index-- > 0;) {
            if (lhs.digits[index] != rhs.digits[index]) {
                return lhs.digits[index] < rhs.digits[index];
            }
        }
    }
    return false; // Equal numbers
}

/** This function compares two BigUnsigned numbers and determine if the left-hand side (lhs) and right-hand
* side (rhs) do not equal each other.
*
* @param lhs, rhs. const reference lhs and const reference rhs
*
* @return bool
*/
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return !(lhs == rhs);
}

/** This function adds two BigUnsigned numbers (lhs and rhs) and returns lhs
*
* @param lhs, rhs. lhs and const reference rhs
*
* @return BigUnsigned
*/
BigUnsigned operator+(BigUnsigned lhs, const BigUnsigned &rhs) {
   lhs += rhs;
   return lhs;
}

/** This function increments the value of a BigUnsigned object by 1 and then returns the incremented object itself.
*
* @param None
*
* @return BigUnsigned reference
*/
BigUnsigned& BigUnsigned::operator++() {
    *this += 1;
    return *this;
}

/** This function increases the value of the BigUnsigned object by 1, but unlike the pre-increment operator, it returns
* the value of the object before the increment.
*
* @param int
*
* @return BigUnsigned
*/
BigUnsigned BigUnsigned::operator++(int) {
    BigUnsigned temp = *this;
    ++(*this);
    return temp;
}

/** This member function is a type conversion operator that allows instances of BigUnsigned to be contextually converted
* to a boolean value. This function provides a way to evaluate the truthiness of a BigUnsigned object.
*
* @param None
*
* @return BigUnsigned
*/
BigUnsigned::operator bool() const {  return !(digits.size() == 1 && digits[0] == 0); }

/** The constructor BigUnsigned::BigUnsigned(int val) for the BigUnsigned class initializes a new instance of BigUnsigned
* with the integer value provided by val
*
* @param val
*
* @return BigUnsigned
*/
BigUnsigned::BigUnsigned(int val) {
    if (val == 0) {
        digits.push_back(val);
    } else {
        while (val > 0) {
            digits.push_back(val % 10);
            val /= 10;
        }
    }
}

/** This member function of the BigUnsigned class is designed to clean up the representation of a BigUnsigned number by
* removing any extraneous zeros from the most significant end of the number.
*
* @param None
*
* @return void
*/
void BigUnsigned::removeLeadingZeros() {
    while (digits.size() > 1 && digits[digits.size() - 1] == 0) {
        digits.pop_back();
    }
}

/** The operator+= member function for the BigUnsigned class implements the addition assignment operator. It adds
* another BigUnsigned number (rhs, for right-hand side) to the current BigUnsigned object (*this) and updates the
* current object with the result.
*
* @param rhs. const reference rhs
*
* @return BigUnsigned reference
*/
BigUnsigned& BigUnsigned::operator+=(const BigUnsigned &rhs) {
    size_t maxLength = max(digits.size(), rhs.digits.size());
    int carry = 0;

    digits.resize(maxLength, 0); // Ensure number is big enough to hold the result

    for (size_t i = 0; i < maxLength || carry; ++i) {
        if (i == digits.size()) {
            digits.push_back(0); // Safely extend the vector if needed due to carry
        }
        int sum = carry + digits[i] + (i < rhs.digits.size() ? rhs.digits[i] : 0);
        carry = sum / 10;
        digits[i] = sum % 10;
    }

    return *this;
}

/** The operator== function for BigUnsigned objects is designed to compare two BigUnsigned numbers (rhs for the right-hand
* side and lhs for the left-hand side) for equality. It checks if the sequence of digits representing the numbers in
* both BigUnsigned objects are exactly the same
*
* @param rhs, lhs. const reference rhs, const reference lhs
*
* @return bool
*/
bool operator==(const BigUnsigned& rhs, const BigUnsigned& lhs) {
    return rhs.digits == lhs.digits;
}

/** The constructor BigUnsigned::BigUnsigned(const string &str) initializes a BigUnsigned object using a string
* representation of a number. It processes the string str to convert it into the numeric representation that BigUnsigned
* uses internally (a vector of digits).
*
* @param str. const string reference str
*
* @return BigUnsigned
*/
BigUnsigned::BigUnsigned(const string &str) {
    bool nonZeroFound = false;
    for (int i = str.length() - 1; i >= 0; --i) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (str[i] != '0' || nonZeroFound) {
                digits.push_back(str[i] - '0');
                nonZeroFound = true;
            }
        } else if (nonZeroFound) {
            break; // Stop at the first non-digit character after finding a digit
        }
    }
    if (digits.empty()) {
        digits.push_back(0); // If no digits found, represent the number as 0
    } else {
        removeLeadingZeros(); // Remove leading zeros if any
    }
}

/** The operator<= function for BigUnsigned objects is designed to compare two BigUnsigned numbers, lhs (left-hand side)
* and rhs (right-hand side), and determine if lhs is less than or equal to rhs. It achieves this by using the logical
* OR operator (||) to combine the results of lhs < rhs and lhs == rhs.
*
* @param lhs, rhs. const reference lhs, const reference rhs
*
* @return bool
*/
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return lhs < rhs || lhs == rhs;
}

/** The operator> function for BigUnsigned objects is designed to compare two BigUnsigned numbers, lhs (left-hand side) and
* rhs (right-hand side), and determine if lhs is strictly greater than rhs. It operates by negating the result of a
* logical OR operation between lhs < rhs and lhs == rhs
*
* @param lhs, rhs. const reference lhs, const reference rhs
*
* @return bool
*/
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return !(lhs < rhs || lhs == rhs);
}

/** The operator>= function for BigUnsigned objects checks whether the left-hand side (lhs) is greater than or equal to
* the right-hand side (rhs). It simplifies this comparison by using the negation of the < operator.
*
* @param lhs, rhs. const reference lhs, const reference rhs
*
* @return bool
*/
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return !(lhs < rhs);
}