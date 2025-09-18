#include <iostream>
#include <string>
#include <limits>
using namespace std;

#include "Passenger.h"
#include "BusinessClass.h"
#include "EconomyClass.h"
#include "FlightClass.h"

// menu header
void printHeader() {
    cout << "\n=============================================\n";
    cout << "           Airline Boarding System           \n";
    cout << "=============================================\n";
}

int main() {
    string flightNo, src, dest, gate;

    printHeader();
    cout << "Enter Flight Number: ";
    getline(cin, flightNo);
    cout << "Enter Source: ";
    getline(cin, src);
    cout << "Enter Destination: ";
    getline(cin, dest);
    cout << "Enter Gate Number: ";
    getline(cin, gate);

    Flight f(flightNo, src, dest, gate);

    int choice;
    do {
        printHeader();
        cout << "1. Add Business Class Passenger\n";
        cout << "2. Add Economy Class Passenger\n";
        cout << "3. Start Boarding\n";
        cout << "4. Show Passenger Status\n";
        cout << "0. Exit\n";
        cout << "---------------------------------------------\n";
        cout << "Enter choice: ";

        // input safety
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // flush newline

        if (choice == 1 || choice == 2) {
            string name, passport, seat;
            cout << "\nEnter Passenger Name: ";
            getline(cin, name);
            cout << "Enter Passport No: ";
            getline(cin, passport);
            cout << "Enter Seat No: ";
            getline(cin, seat);

            if (choice == 1) {
                f.addPassenger(new BusinessPassenger(name, passport, seat));
            } else {
                f.addPassenger(new EconomyPassenger(name, passport, seat));
            }
        }
        else if (choice == 3) {
            f.startBoarding();
        }
        else if (choice == 4) {
            f.showPassengerStatus();
        }
        else if (choice != 0) {
            cout << "Invalid choice! Please try again.\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    cout << "\nExiting Airline Boarding System. Safe travels!\n";
    return 0;
}
