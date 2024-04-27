/*
 * Natanya Anderson
 * Polynomial.h
 * Section C, April 27, 2024
 * Program defines a Polynomial class that models mathematical polynomials using a linked list for storing coefficients.
 * It enables basic polynomial operations such as addition, equality checking, and evaluation at specific points.
 * The class supports initialization from a list of coefficients or by copying another polynomial and provides
 * functionality to output polynomials in standard mathematical notation. This allows for efficient manipulation
 * and evaluation of polynomials in various mathematical computations.
*/

#ifndef HW09_POLYNOMIAL_H
#define HW09_POLYNOMIAL_H

#include <iostream>
#include <vector>
class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
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
    Polynomial(const std::vector<int>& coeffs);
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

#endif //HW09_POLYNOMIAL_H
