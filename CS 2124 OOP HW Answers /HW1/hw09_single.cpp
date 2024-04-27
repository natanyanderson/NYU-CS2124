/*
 * Natanya Anderson
 * hw09_single.cpp
 * Section C, April 27, 2024
 * Program defines a Polynomial class that models mathematical polynomials using a linked list for storing coefficients.
 * It enables basic polynomial operations such as addition, equality checking, and evaluation at specific points.
 * The class supports initialization from a list of coefficients or by copying another polynomial and provides
 * functionality to output polynomials in standard mathematical notation. This allows for efficient manipulation
 * and evaluation of polynomials in various mathematical computations.
*/

#include <iostream>
#include <vector>
using namespace std;

class Polynomial {
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
private:
    struct Node {
        int coeff;
        Node* next;
        Node(int coeff, Node* next = nullptr) : coeff(coeff), next(next) {}
    };
    Node* head_ptr;
    int degree;
public:
    /*
     * Declaring function prototypes
     */
    // Default constructor
    Polynomial();
    // Constructor with coefficients
    Polynomial(const vector<int>& coeffs);
    //Big 3
    // Destructor
    ~Polynomial();
    //Big 3
    // Copy constructor
    Polynomial(const Polynomial& other);
    //Big 3
    // Assignment operator
    Polynomial& operator=(Polynomial other);
    // Evaluation method
    int evaluate(int x) const;
    // Equality operator
    bool operator==(const Polynomial& rhs) const;
    //Plus-equal operator
    Polynomial operator+=(const Polynomial& rhs);
    // Inequality operator
    bool operator!=(const Polynomial& rhs) const;
    // Addition operator
    Polynomial operator+(const Polynomial& rhs) const;
};

void doNothing(Polynomial temp) {}

int main() {

    //test constructor
    Polynomial p0;                       // 0
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    // Polynomial temp(p4);
    // cout << "temp: " << temp << endl;

    cout << "displaying polynomials\n"
         << "p0: " << p0 << endl
         << "p1: " << p1 << endl
         << "p2: " << p2 << endl
         << "p3: " << p3 << endl
         << "p4: " << p4 << endl
         << "has_a_zero: " << has_a_zero << endl;

    // Polynomial temp;
    // temp = p2 + p3;
    // cout << "temp: " << temp << endl;

    cout << "p2 + p3: " << (p2+p3) << endl
         << "p2 + p4: " << (p2+p4) << endl
         << "p4 + p2: " << (p4+p2) << endl;

    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;
    cout << "p5: " << p5 << endl;


    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;

    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    Polynomial p8({ 1, 1 });
    Polynomial p9({ -1, 1 });
    Polynomial p10({ 0, 0, 2 });
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()

    cout << "p8: " << p8 << endl
         << "p9: " << p9 << endl
         << "p10: " << p10 << endl;

    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;
}

/*
 * Declaring function implementations
*/
// Default constructor
/**
* This constructor initializes a Polynomial object with a default state where it represents the zero polynomial.
* It sets up a new polynomial with a single node containing a coefficient of zero and assigns the degree of the
* polynomial to zero.
*
* @param none
*
* @return A Polynomial object representing the zero polynomial.
*/
Polynomial::Polynomial() : head_ptr(new Node(0)), degree(0) {}

// Constructor with coefficients
/**
* This constructor creates a Polynomial object from a vector of integers representing the coefficients.
* It initializes the polynomial to have a linked list structure where each node corresponds to a coefficient
* from the input vector, with the first coefficient in the vector being the highest degree. The constructor
* sets the degree of the polynomial to be one less than the size of the input vector (since degree is zero-based).
* If the input vector is empty, the polynomial is initialized to zero (a single node with coefficient 0 and degree 0).
*
* @param coeffs A vector of integers where each element represents a coefficient for the polynomial.
*
* @return A Polynomial object constructed with the specified coefficients.
*/
Polynomial::Polynomial(const vector<int>& coeffs) : head_ptr(nullptr), degree(coeffs.size() - 1) {
    if (coeffs.empty()) {
        head_ptr = new Node(0);
        degree = 0;
        return;
    }

    Node** curr = &head_ptr;
    for (int coeff : coeffs) {
        *curr = new Node(coeff);
        curr = &((*curr)->next);
    }
}

//Output operator
/**
* This function provides a string representation of a Polynomial object for output purposes. It handles the formatting
* of the polynomial by iterating through its coefficients linked list from the highest degree to the lowest.
* The function starts by checking if the polynomial is zero (only contains the coefficient zero with no other nodes),
* in which case it outputs "0". For non-zero polynomials, it constructs the polynomial string by appending each
* non-zero coefficient and its corresponding variable and power, formatted correctly with signs and powers.
* It manages the proper placement of plus and minus signs, handles special cases for the coefficients 1 and -1,
* and ensures that the first term does not start with a plus sign.
*
* @param os The output stream to which the string representation is sent.
* @param poly The polynomial object to be outputted.
*
* @return ostream& The modified output stream containing the polynomial representation.
*/

ostream& operator<<(ostream& os, const Polynomial& poly) {
    if (!poly.head_ptr->next && poly.head_ptr->coeff == 0) {
        os << "0";
        return os;
    }
    Polynomial::Node* node = poly.head_ptr;
    bool first = true;
    int exp = poly.degree;
    while (node) {
        if (node->coeff != 0) { // Skip zero coefficients
            if (!first && node->coeff > 0) {
                os << "+";
            }
            if (exp == 0 || abs(node->coeff) != 1) {
                os << node->coeff;
            } else if (node->coeff == -1) {
                os << "-";
            }
            if (exp > 0) {
                os << "x";
                if (exp > 1) {
                    os << "^" << exp;
                }
            }
            first = false;
        }
        node = node->next;
        exp--;
    }
    return os;
}

// Destructor
/**
* This destructor cleans up a Polynomial object by deallocating all the memory used for its nodes. It iterates
* through the linked list of nodes starting from the head pointer, and for each node, it saves the pointer to the
* next node, deletes the current node, and moves to the next node. This process continues until all nodes have
* been deleted, ensuring that no memory leaks occur when a Polynomial object goes out of scope or is deleted.
*
* @param none
*
* @return void function
*/
Polynomial::~Polynomial() {
    Node* current = head_ptr;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

//Copy constructor
/**
* This copy constructor creates a deep copy of an existing Polynomial object. It initializes a new Polynomial with
* the same degree as the original and copies each coefficient by traversing the linked list of the source Polynomial.
* New nodes are created for each coefficient in the copied Polynomial, ensuring that the new Polynomial is a
* separate object with its own memory allocation. This allows for safe copying of Polynomial objects, preserving
* the integrity of the original while providing an exact copy for independent use.
*
* @param other The Polynomial object from which to copy.
*
* @return A Polynomial object that is a deep copy of the given Polynomial.
*/
Polynomial::Polynomial(const Polynomial& other) : head_ptr(nullptr), degree(other.degree) {
    Node** curr = &head_ptr;
    Node* node = other.head_ptr;
    while (node != nullptr) {
        *curr = new Node(node->coeff);
        curr = &((*curr)->next);
        node = node->next;
    }
}

// Assignment operator
/**
* This assignment operator overloads the '=' operator to allow one Polynomial object to be assigned to another.
* It employs the copy-and-swap idiom, utilizing a copy constructor to handle the incoming object by value,
* which simplifies memory management and exception safety. The function swaps the internal data of the current
* object with the temporary copy, effectively transferring the ownership of the data. This method ensures that
* the current object takes on the state of the right-hand side operand while the old data is destructed
* when the temporary copy goes out of scope.
*
* @param other A temporary Polynomial object created by copy construction from the target of the assignment.
*
* @return Polynomial& A reference to the current object after assignment.
*/
Polynomial& Polynomial::operator=(Polynomial other) {
    swap(head_ptr, other.head_ptr);
    swap(degree, other.degree);
    return *this;
}

// Evaluation method
/**
* This method evaluates the polynomial at a given value of x. It implements the Horner's method. Starting with the
* highest degree coefficient, the method accumulates the result by multiplying the current result with x and
* adding the next coefficient from the polynomial. This process is repeated for all coefficients in the polynomial
* linked list, resulting in the polynomial's value at the specified point.
*
* @param x The value at which to evaluate the polynomial.
*
* @return int The result of the polynomial evaluation at the given x.
*/
int Polynomial::evaluate(int x) const {
    int result = 0;
    Node* node = head_ptr;
    while (node != nullptr) {
        result = result * x + node->coeff;
        node = node->next;
    }
    return result;
}

//Equality operator
/**
* This equality operator checks if two Polynomial objects are equal. It compares each coefficient of the two
* polynomials, skipping over any zero coefficients that do not affect the polynomial's value. The degrees of the
* polynomials are adjusted as zero coefficients are skipped to ensure only significant terms are considered.
* The comparison continues until either all coefficients are matched or a discrepancy is found. After passing
* through all coefficients, the method further checks for any trailing zeros, adjusting degrees accordingly.
* Equality is determined not only by matching coefficients but also by ensuring that both polynomials have the
* same effective degree (no remaining non-zero coefficients).
*
* @param rhs The right-hand side Polynomial to compare with the current object.
*
* @return bool True if the polynomials are equal, false otherwise.
*/
bool Polynomial::operator==(const Polynomial& rhs) const {
    Node* curr1 = head_ptr;
    Node* curr2 = rhs.head_ptr;
    int exp1 = degree, exp2 = rhs.degree;

    while (curr1 && curr2) {
        // Skip zero coefficients
        while (curr1 && curr1->coeff == 0) {
            curr1 = curr1->next;
            exp1--;
        }
        while (curr2 && curr2->coeff == 0) {
            curr2 = curr2->next;
            exp2--;
        }
        if ((curr1 && !curr2) || (!curr1 && curr2) || (exp1 != exp2)) {
            return false;
        }
        // If coefficients do not match
        if (curr1 && curr2 && curr1->coeff != curr2->coeff) {
            return false;
        }
        if (curr1 && curr2) {
            curr1 = curr1->next;
            curr2 = curr2->next;
            exp1--;
            exp2--;
        }
    }
    // Handle cases where trailing zeros may still exist
    while (curr1 && curr1->coeff == 0) {
        curr1 = curr1->next;
        exp1--;
    }
    while (curr2 && curr2->coeff == 0) {
        curr2 = curr2->next;
        exp2--;
    }
    return exp1 == -1 && exp2 == -1; // Both should end at invalid degrees if truly equal
}

//Plus-equal operator
/**
* This compound assignment operator overloads the '+=' operator to add the right-hand side (rhs) Polynomial to the
* current Polynomial object. It uses the addition operator (`operator+`) to perform the polynomial addition and then
* assigns the result back to the current object. This operation modifies the current Polynomial by adding the terms
* of the rhs Polynomial, effectively updating its coefficients and possibly its degree if the rhs has a higher degree.
*
* @param rhs The Polynomial to be added to the current object.
*
* @return Polynomial& A reference to the current Polynomial after the addition has been applied.
*/
Polynomial Polynomial::operator+=(const Polynomial& rhs) {
    *this = *this + rhs;
    return *this;
}

// Inequality operator
/**
* This inequality operator overloads the '!=' operator to determine if two Polynomial objects are not equal.
* It utilizes the equality operator (`operator==`) to check if the polynomials are equal and returns the
* logical negation of that result. If the polynomials have different coefficients or degrees, this method
* will return true, indicating that they are not the same polynomial.
*
* @param rhs The right-hand side Polynomial to compare with the current object.
*
* @return bool True if the polynomials are not equal, false if they are equal.
*/
bool Polynomial::operator!=(const Polynomial& rhs) const {
    return !(*this == rhs);
}

// Addition operator
/**
* This addition operator overloads the '+' operator to allow for the addition of two Polynomial objects.
* It creates a new Polynomial result by iterating over the nodes of both operand polynomials simultaneously.
* During iteration, it compares the degrees of the current nodes of both polynomials and adds the coefficients
* of the terms with the same degree. This operation is done efficiently to handle polynomials of different lengths
* and to skip any zero coefficients to avoid unnecessary calculations. The result is a new Polynomial with each
* coefficient correctly calculated and placed in order from the highest to the lowest degree. The method also
* ensures that if the resulting polynomial is zero (all coefficients cancel out), it initializes a correct zero
* polynomial state.
*
* @param rhs The right-hand side Polynomial to add to the current object.
*
* @return Polynomial A new Polynomial that is the result of the addition.
*/
Polynomial Polynomial::operator+(const Polynomial& rhs) const {
    Polynomial result;
    Node *node1 = head_ptr, *node2 = rhs.head_ptr;
    Node **curr = &(result.head_ptr);
    int exp1 = degree, exp2 = rhs.degree;
    int resultDegree = -1; // Start with an invalid degree

    while (node1 != nullptr || node2 != nullptr) {
        int coeff = 0;
        if (node1 && exp1 > exp2) {
            coeff = node1->coeff;
            node1 = node1->next;
            exp1--;
        } else if (node2 && exp2 > exp1) {
            coeff = node2->coeff;
            node2 = node2->next;
            exp2--;
        } else if (node1 && node2 && exp1 == exp2) {
            coeff = node1->coeff + node2->coeff;
            node1 = node1->next;
            node2 = node2->next;
            exp1--;
            exp2--;
        }

        if (coeff != 0) {  // Only create a node for non-zero coefficients
            *curr = new Node(coeff);
            curr = &((*curr)->next);
            resultDegree = max(resultDegree, max(exp1, exp2) + 1);
        }
    }
    if (result.head_ptr == nullptr) {
        result.head_ptr = new Node(0);
        result.degree = 0;
    } else {
        result.degree = resultDegree;
    }
    return result;
}