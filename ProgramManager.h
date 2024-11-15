/*  LV Marlowe
    SDEV-345: Data Structures & Algorithms
    Week 6: Assignment
    5 Oct 2024
    This header file defines the ProgramManager class,
    which handles the user interface and program flow
    for the large number arithmetic calculator.
    It requires LargeNumber.h and <string> to run.
-------------------------------------------------- */

#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

using namespace std;

#include "LargeNumber.h"
#include <string>

class ProgramManager {
public:

    // Define default constructor
    ProgramManager() = default;

    // Run main program loop
    void run();

private:

    // Define helper methods
    void printResult(const LargeNumber& result);
    LargeNumber getInputNumber();
    char getOperation();
    bool shouldContinue();
    string getValidNumberInput();
    bool isValidNumber(const string& input);
};

#endif // PROGRAM_MANAGER_H