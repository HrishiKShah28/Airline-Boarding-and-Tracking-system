#include <iostream>
#include <memory>
#include <limits>
using namespace std;

#include "Passenger.h"
#include "BusinessClass.h"
#include "EconomyClass.h"
#include "FlightClass.h"

// utility function for clear input
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// print stylish header
void printHeader() {
    cout << "\n=============================================\n";
    cout << "         ✈️  Airline Boarding System  ✈️\n";
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
        cout << "1️⃣  Add Business Class Passenger\n";
        cout << "2️⃣  Add Economy Class Passenger\n";
        cout << "3️⃣  Start Boarding\n";
        cout << "4️⃣  Show Passenger Status\n";
        cout << "0️⃣  Exit\n";
        cout << "---------------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1 || choice == 2) {
            string name, passport, seat;
            cout << "\nEnter Passenger Name: ";
            getline(cin, name);
            cout << "Enter Passport No: ";
            getline(cin, passport);
            cout << "Enter Seat No: ";
            getline(cin, seat);

            if (choice == 1) {
                f.addPassenger(make_unique<BusinessPassenger>(name, passport, seat));
                cout << "✅ Business passenger added successfully!\n";
            } else {
                f.addPassenger(make_unique<EconomyPassenger>(name, passport, seat));
                cout << "✅ Economy passenger added successfully!\n";
            }
        }
        else if (choice == 3) {
            f.startBoarding();
        }
        else if (choice == 4) {
            f.showPassengerStatus();
        }
        else if (choice != 0) {
            cout << "⚠️ Invalid choice! Try again.\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    cout << "\n👋 Exiting Airline Boarding System. Safe travels!\n";
    return 0;
}
