/*  LV Marlowe
    SDEV-345: Data Structures & Algorithms
    Week 5: Assignment
    5 Oct 2024
    This file implements the ProgramManager class methods
    defined in ProgramManager.h. It handles user input,
    program flow, and output formatting for the large number
    arithmetic calculator. It manages the interaction between
    the user and the LargeNumber operations.
    It requires ProgramManager.h, <iostream>, <iomanip>,
    <limits>, <algorithm>, and <vector> to run.
-------------------------------------------------- */

#include "ProgramManager.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

// Run main program loop
void ProgramManager::run() {
    cout << "\n+---------------------------------------------+" << endl;
    cout << "|     Large Number Calculator     |" << endl;
    cout << "+---------------------------------------------+" << endl;

    do {
        cout << "+--- Input -----------------------------------+" << endl;
        cout << "| Enter the first number:  ";
        LargeNumber num1 = getInputNumber();

        cout << "| Enter the second number: ";
        LargeNumber num2 = getInputNumber();

        char operation = getOperation();

        // Perform arithmetic based on user input
        LargeNumber result;
        if (operation == '+') {
            result = num1 + num2;
        }
        else if (operation == '-') {
            result = num1 - num2;
        }
        else {
            cout << "| Invalid operation.                        |" << endl;
            continue;
        }

        printResult(result);

    } while (shouldContinue());

    cout << "+--- Thank you -------------------------------+" << endl;
    cout << "| Thank you for using the program.            |" << endl;
    cout << "| Goodbye!                                    |" << endl;
    cout << "+---------------------------------------------+" << endl;
}

// Display result of math
void ProgramManager::printResult(const LargeNumber& result) {

    // Convert linked list representation to vector for easier processing
    vector<int> nodes;
    Node* current = result.getHead();
    while (current) {
        nodes.push_back(current->value);
        current = current->next;
    }

    cout << "+--- Result ----------------------------------+" << endl;
    cout << "| The answer is:                             |" << endl;

    // Display each node's value
    for (int i = nodes.size() - 1; i >= 0; i--) {
        cout << "|   Node " << setw(2) << (nodes.size() - i) << " = "
            << setfill('0') << setw(3) << nodes[i]
            << setfill(' ') << setw(29) << "|" << endl;
    }

    // Print full number, removing leading zeros
    string fullNumber;
    bool leadingZero = true;
    for (int i = nodes.size() - 1; i >= 0; i--) {
        if (nodes[i] != 0 || !leadingZero || i == 0) {
            if (leadingZero) {
                fullNumber += to_string(nodes[i]);
                leadingZero = false;
            }
            else {
                char buffer[4];
                snprintf(buffer, sizeof(buffer), "%03d", nodes[i]);
                fullNumber += buffer;
            }
        }
    }

    // Handle negative numbers
    if (result.isNegative()) {
        fullNumber = "-" + fullNumber;
    }

    cout << "| Giving: " << setw(34) << right << fullNumber << " |" << endl;
    cout << "+---------------------------------------------+" << endl;
}

// Obtain valid number input from user
LargeNumber ProgramManager::getInputNumber() {
    string input = getValidNumberInput();
    cout << "|                                            |" << endl;
    return LargeNumber(input);
}

// Validate user input to ensure it is a positive integer
string ProgramManager::getValidNumberInput() {
    string input;
    while (true) {
        getline(cin, input);

        // Remove leading and trailing whitespace
        // (https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/)
        input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));
        input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);

        if (isValidNumber(input)) {
            break;
        }
        else {
            cout << "| Invalid input. Enter a positive integer:   |" << endl;
            cout << "| ";
        }
    }
    return input;
}

// Check if string represents a valid positive integer
bool ProgramManager::isValidNumber(const string& input) {
    if (input.empty()) return false;
    return all_of(input.begin(), input.end(), ::isdigit);
}

// Prompt user for arithmetic operation to perform
char ProgramManager::getOperation() {
    char operation;
    cout << "| Choose operator (+/-): ";
    do {
        cin >> operation;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (operation != '+' && operation != '-') {
            cout << "| Invalid operator. Please enter '+' or '-': |" << endl;
            cout << "| ";
        }
    } while (operation != '+' && operation != '-');
    cout << "+---------------------------------------------+" << endl;
    return operation;
}

// Ask user if they want to perform another calculation
bool ProgramManager::shouldContinue() {
    char choice;
    cout << "+--- Continue? -------------------------------+" << endl;
    cout << "| Do you want to perform another calculation? |" << endl;
    cout << "| Enter (y/n): ";
    do {
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = tolower(choice);
        if (choice != 'y' && choice != 'n') {
            cout << "| Invalid input. Please enter 'y' or 'n':    |" << endl;
            cout << "| ";
        }
    } while (choice != 'y' && choice != 'n');
    cout << "+---------------------------------------------+" << endl;

    return choice == 'y';
}