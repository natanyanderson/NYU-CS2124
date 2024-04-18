/*
  rec07.cpp
  Natanya Anderson
  CS2124
  Implement the class Rational, so that the following program works.
*/

#include <iostream>
using namespace std;

// Put your Rational class here.
class Rational {
private:
    int numerator;
    int denominator;

public:
    Rational(int num = 0, int denom = 1);
    friend ostream& operator<<(ostream& os, const Rational& rational);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    friend istream& operator>>(istream& is, Rational& rational);

    Rational& operator+=(const Rational rhs);

    Rational& operator++();

    Rational operator++(int);

    explicit operator bool() const;

    void normalize();
};
// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.

int greatestCommonDivisor(int x, int y);
Rational operator+(Rational lhs, const Rational& rhs);
bool operator<=(const Rational lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& rhs);
Rational operator--(Rational& rhs, int);

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;

    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why shouldn't it compile?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
        << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
        << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
        << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
        << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
        << (minusFive >= threeHalves) << endl;
}

// Any functions that are not members and not friends should have
// their definitions here...

Rational::Rational(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
    normalize();
}
ostream& operator<<(ostream& os, const Rational& rational) {
    os << rational.numerator << '/' << rational.denominator;
    return os;
}

istream& operator>>(istream& is, Rational& rational) {
    char slash;
    is >> rational.numerator >> slash >> rational.denominator;
    rational.normalize();
    return is;
}

Rational& Rational::operator+=(const Rational rhs) {
    numerator = numerator * rhs.denominator + rhs.numerator * denominator;
    denominator *= rhs.denominator;
    normalize();
    return *this;
}

Rational& Rational::operator++() {
    numerator += denominator;
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp = *this;
    ++(*this);
    return temp;
}

Rational::operator bool() const { return numerator != 0; }
void Rational::normalize() {
    int gcd = greatestCommonDivisor(abs(numerator), abs(denominator));
    numerator /= gcd;
    denominator /= gcd;
    if (denominator < 0) {
        denominator = -denominator;
        numerator = -numerator;
    }
}

int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

Rational operator+(Rational lhs, const Rational& rhs) {
    lhs += rhs;
    return lhs;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Rational lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

Rational operator--(Rational& rhs, int) {
    Rational rational(rhs);
    rhs += -1;
    return rational;
}

Rational& operator--(Rational& rhs) {
    rhs += -1;
    return rhs;
}