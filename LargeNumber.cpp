/*  LV Marlowe
    SDEV-345: Data Structures & Algorithms
    Week 6: Assignment
    5 Oct 2024
    This file implements the LargeNumber class methods
    defined in LargeNumber.h. It includes the implementation
    of arithmetic operations, constructors, and math functions
    for handling large numbers using a linked list structure.
    It requires LargeNumber.h, <algorithm>, and <iomanip> to 
    run.
-------------------------------------------------- */

#include "LargeNumber.h"
#include <algorithm> // For reverse()
#include <iomanip> // For output formatting setw() and setfill()

using namespace std;

// Implement default constructor
LargeNumber::LargeNumber() : head(nullptr), tail(nullptr), negative(false) {}

// Implement constructor from string
LargeNumber::LargeNumber(const string& number) : head(nullptr), tail(nullptr), negative(false) {
     
    // Reverse input string for improved processing
    // (https://www.geeksforgeeks.org/reverse-a-string-in-c-cpp-different-methods/)
    string reversed = number;
    reverse(reversed.begin(), reversed.end());

    // Process the number in group of 3 digits
    // Store each 3-digit group in a single node
    for (size_t i = 0; i < reversed.length(); i += 3) {
        string chunk = reversed.substr(i, min<size_t>(3, reversed.length() - i));
        
        // Reverse 3-digit group back to original order
        reverse(chunk.begin(), chunk.end());
        while (chunk.length() < 3) {

            // Pad with leading zeros if chunk is less than 3 digits
            chunk = "0" + chunk;
        }

        // Convert string to integer
        // (https://cplusplus.com/reference/string/stoi/)
        addNode(stoi(chunk));
    }
}

// Implement virtual destructor
LargeNumber::~LargeNumber() {
    clear();
}

// Implement copy constructor
LargeNumber::LargeNumber(const LargeNumber& other) : head(nullptr), tail(nullptr), negative(other.negative) {
    copyFrom(other);
}

// Implement overloaded assignment (=) operator
// (https://www.geeksforgeeks.org/operator-overloading-cpp/)
LargeNumber& LargeNumber::operator=(const LargeNumber& other) {
    if (this != &other) {
        clear();
        negative = other.negative;
        copyFrom(other);
    }
    return *this;
}

// Add a new node to end of list
void LargeNumber::addNode(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Implement overloaded addition (+) operator
// (https://www.geeksforgeeks.org/operator-overloading-cpp/)
LargeNumber LargeNumber::operator+(const LargeNumber& other) const {
    LargeNumber result;
    const Node* n1 = this->head;
    const Node* n2 = other.head;
    int carry = 0;

    // Add corresponding nodes and handle carry
    // (https://www.geeksforgeeks.org/add-two-numbers-represented-by-linked-list/)
    while (n1 || n2 || carry) {
        int sum = carry;
        if (n1) {
            sum += n1->value;
            n1 = n1->next;
        }
        if (n2) {
            sum += n2->value;
            n2 = n2->next;
        }
        result.addNode(sum % 1000);
        carry = sum / 1000;
    }

    return result;
}

// Implement overloaded subtraction (-) operator
// (https://www.geeksforgeeks.org/operator-overloading-cpp/)
LargeNumber LargeNumber::operator-(const LargeNumber& other) const {
    LargeNumber result;
    const Node* n1 = this->head;
    const Node* n2 = other.head;
    int borrow = 0;
    bool isNegative = false;

    // Determine if result will be negative
    if (compare(other) < 0) {
        isNegative = true;

        // Swap numbers to perform |a| - |b| if result will be negative
        // (https://www.geeksforgeeks.org/swap-in-cpp/)
        swap(n1, n2);  
    }

    // Perform subtraction
    // (https://www.geeksforgeeks.org/subtract-two-numbers-represented-as-linked-lists/_
    while (n1 || n2) {
        int diff = borrow;
        if (n1) {
            diff += n1->value;
            n1 = n1->next;
        }
        if (n2) {
            diff -= n2->value;
            n2 = n2->next;
        }

        if (diff < 0) {
            diff += 1000;
            borrow = -1;
        }
        else {
            borrow = 0;
        }

        result.addNode(diff);
    }

    // Remove leading zeros
    // (https://www.geeksforgeeks.org/compare-numbers-represented-by-linked-lists/)
    while (result.tail && result.tail != result.head && result.tail->value == 0) {
        Node* temp = result.tail;
        Node* current = result.head;
        while (current->next != result.tail) {
            current = current->next;
        }
        result.tail = current;
        result.tail->next = nullptr;
        delete temp;
    }

    result.negative = isNegative;
    return result;
}

// Compare length of two LargeNumbers to determine if result is positive or negative
// (https://www.geeksforgeeks.org/compare-numbers-represented-by-linked-lists/)
int LargeNumber::compare(const LargeNumber& other) const {
    const Node* n1 = head;
    const Node* n2 = other.head;
    int len1 = 0, len2 = 0;

    // Count number of nodes in each number
    while (n1) {
        len1++;
        n1 = n1->next;
    }
    while (n2) {
        len2++;
        n2 = n2->next;
    }

    // If lengths are different, longer number is larger
    if (len1 != len2) {
        return len1 - len2;
    }

    // If lengths are the same, compare digit by digit
    n1 = head;
    n2 = other.head;
    while (n1 && n2) {
        if (n1->value != n2->value) {
            return n1->value - n2->value;
        }
        n1 = n1->next;
        n2 = n2->next;
    }

    // Numbers are equal, so result is zero
    return 0;
}

// Implement overloaded output stream (<<) operator for improved printing
// (https://dev.to/dinhluanbmt/overloading-operator-of-stdcout-gkc)
ostream& operator<<(ostream& os, const LargeNumber& num) {
    if (num.negative) {
        os << "-";
    }
    Node* current = num.head;
    bool first = true;
    while (current) {
        if (!first) {
            os << ",";
        }
        os << setfill('0') << setw(3) << current->value;
        first = false;
        current = current->next;
    }
    return os;
}

// Clear linked list
void LargeNumber::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

// Copy nodes from another LargeNumber instance for passing to and returning from functions
void LargeNumber::copyFrom(const LargeNumber& other) {
    Node* current = other.head;
    while (current) {
        addNode(current->value);
        current = current->next;
    }
}