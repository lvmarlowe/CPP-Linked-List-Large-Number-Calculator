/*  LV Marlowe
    SDEV-345: Data Structures & Algorithms
    Week 6: Assignment
    5 Oct 2024
    This header file defines the LargeNumber class,
    which implements arbitrary-precision arithmetic
    using a linked list structure. It includes methods
    for addition, subtraction, and comparison of large numbers.
    This file requires the standard libraries <string> and 
    <iostream>.
-------------------------------------------------- */

#ifndef LARGE_NUMBER_H
#define LARGE_NUMBER_H
#include <string>
#include <iostream>

// Define node structure for linked list
struct Node {
    int value;
    Node* next;
    Node(int val) : value(val), next(nullptr) {}
};

class LargeNumber {
public:
    // Define constructors and destructor
    LargeNumber();
    explicit LargeNumber(const std::string& number);
    ~LargeNumber();
    LargeNumber(const LargeNumber& other);
    LargeNumber& operator=(const LargeNumber& other);

    // Define arithmetic operations
    LargeNumber operator+(const LargeNumber& other) const;
    LargeNumber operator-(const LargeNumber& other) const;

    // Define output stream operator for improved printing
    friend std::ostream& operator<<(std::ostream& os, const LargeNumber& num);

    // Define accessor methods
    bool isNegative() const { return negative; }
    Node* getHead() const { return head; }

private:
    Node* head;
    Node* tail;
    bool negative;

    // Define helper methods for internal operations
    void addNode(int value);
    int compare(const LargeNumber& other) const;
    void clear();
    void copyFrom(const LargeNumber& other);
};

#endif // LARGE_NUMBER_H