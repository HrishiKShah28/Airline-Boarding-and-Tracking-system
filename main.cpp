#include <iostream>
#include <string>
#include <limits>
using namespace std;

#include "passenger.h"
#include "business.h"
#include "economy.h"
#include "flight.h"

// Menu header function
void printHeader() {
    cout << "\n" << string(50, '=') << endl;
    cout << "         AIRLINE BOARDING SYSTEM" << endl;
    cout << string(50, '=') << endl;
}

// Clear input buffer helper function
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Get valid integer input
int getValidChoice() {
    int choice;
    while (!(cin >> choice)) {
        cout << "Invalid input! Please enter a number: ";
        clearInputBuffer();
    }
    clearInputBuffer(); // Clear remaining newline
    return choice;
}

// Get non-empty string input
string getNonEmptyString(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Input cannot be empty! Please try again." << endl;
        }
    } while (input.empty());
    return input;
}

int main() {
    string flightNo, src, dest, gate;

    // Welcome message
    printHeader();
    cout << "Welcome to the Airline Boarding System!" << endl;
    cout << string(50, '=') << endl;

    // Get flight details
    cout << "\nPlease enter flight details:" << endl;
    flightNo = getNonEmptyString("Enter Flight Number: ");
    src = getNonEmptyString("Enter Source Airport: ");
    dest = getNonEmptyString("Enter Destination Airport: ");
    gate = getNonEmptyString("Enter Gate Number: ");

    // Create flight object
    Flight flight(flightNo, src, dest, gate);

    int choice;
    do {
        printHeader();
        flight.displayFlightInfo();
        cout << "\nMAIN MENU:" << endl;
        cout << "1. Add Business Class Passenger" << endl;
        cout << "2. Add Economy Class Passenger" << endl;
        cout << "3. Start Boarding Process" << endl;
        cout << "4. Show Passenger Status" << endl;
        cout << "5. Demonstrate Features" << endl;
        cout << "0. Exit System" << endl;
        cout << string(50, '-') << endl;
        cout << "Enter your choice: ";

        choice = getValidChoice();

        switch (choice) {
            case 1: {
                cout << "\n--- ADD BUSINESS CLASS PASSENGER ---" << endl;
                string name = getNonEmptyString("Enter Passenger Name: ");
                string passport = getNonEmptyString("Enter Passport Number: ");
                string seat = getNonEmptyString("Enter Seat Number: ");

                BusinessPassenger* bp = new BusinessPassenger(name, passport, seat);
                flight.addPassenger(bp);

                // Show additional business class features
                cout << "\nBusiness Class Features:" << endl;
                bp->loungeUse();
                
                char addBaggage;
                cout << "Add extra baggage? (y/n): ";
                cin >> addBaggage;
                clearInputBuffer();
                
                if (addBaggage == 'y' || addBaggage == 'Y') {
                    cout << "Enter extra baggage weight (kg): ";
                    int extraWeight = getValidChoice();
                    bp->addBags(extraWeight);
                }

                bp->show();
                break;
            }

            case 2: {
                cout << "\n--- ADD ECONOMY CLASS PASSENGER ---" << endl;
                string name = getNonEmptyString("Enter Passenger Name: ");
                string passport = getNonEmptyString("Enter Passport Number: ");
                string seat = getNonEmptyString("Enter Seat Number: ");

                EconomyPassenger* ep = new EconomyPassenger(name, passport, seat);
                flight.addPassenger(ep);

                // Show additional economy class features
                char addMeal;
                cout << "Add meal service? (y/n): ";
                cin >> addMeal;
                clearInputBuffer();
                
                if (addMeal == 'y' || addMeal == 'Y') {
                    ep->addMeal();
                }

                char addBaggage;
                cout << "Add extra baggage? (y/n): ";
                cin >> addBaggage;
                clearInputBuffer();
                
                if (addBaggage == 'y' || addBaggage == 'Y') {
                    cout << "Enter extra baggage weight (kg): ";
                    int extraWeight = getValidChoice();
                    ep->addBags(extraWeight);
                }

                ep->show();
                break;
            }

            case 3: {
                cout << "\n--- BOARDING PROCESS ---" << endl;
                flight.startBoarding();
                break;
            }

            case 4: {
                cout << "\n--- PASSENGER STATUS ---" << endl;
                flight.showPassengerStatus();
                break;
            }

            case 5: {
                cout << "\n--- FEATURE DEMONSTRATION ---" << endl;
                cout << "Creating sample passengers for demonstration..." << endl;

                // Create sample business passengers
                BusinessPassenger* bp1 = new BusinessPassenger("B001", "John Smith", 35, "P123456", 45);
                BusinessPassenger* bp2 = new BusinessPassenger("B002", "Jane Doe", 28, "P789012", 35);
                
                // Create sample economy passengers
                EconomyPassenger* ep1 = new EconomyPassenger("E001", "Bob Wilson", 42, "P345678", 25, true);
                EconomyPassenger* ep2 = new EconomyPassenger("E002", "Alice Brown", 31, "P901234", 18, false);

                flight.addPassenger(bp1);
                flight.addPassenger(bp2);
                flight.addPassenger(ep1);
                flight.addPassenger(ep2);

                cout << "\n--- Demonstrating Fare Comparison ---" << endl;
                compareFare(*bp1, *bp2);
                compareFare(*ep1, *ep2);

                cout << "\n--- Passenger Details ---" << endl;
                bp1->show();
                bp2->show();
                ep1->show();
                ep2->show();

                cout << "\n--- Demonstrating Boarding ---" << endl;
                flight.startBoarding();
                break;
            }

            case 0: {
                cout << "\n--- SYSTEM SHUTDOWN ---" << endl;
                cout << "Thank you for using the Airline Boarding System!" << endl;
                cout << "Safe travels!" << endl;
                break;
            }

            default: {
                cout << "\nInvalid choice! Please select from 0-5." << endl;
                break;
            }
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    cout << "\nSystem exited successfully." << endl;
    return 0;
}

/* 
COMPILATION INSTRUCTIONS:
========================
To compile this program, use:

g++ -o airline_system main.cpp

Or if you prefer separate compilation:
g++ -c passenger.h
g++ -c business.h  
g++ -c economy.h
g++ -c flight.h
g++ -o airline_system main.cpp

Then run:
./airline_system

FEATURES INCLUDED:
=================
1. Inheritance: BusinessPassenger and EconomyPassenger inherit from Passenger
2. Polymorphism: Virtual functions and pure virtual boardFlight()
3. Encapsulation: Private/protected members with public interfaces  
4. Dynamic memory: new/delete for passenger objects
5. Friend functions: compareFare functions for each class
6. Constructors: Default, parameterized, and copy constructors
7. Destructors: Virtual destructor in base class
8. STL containers: vector for storing passengers
9. File organization: Separate header files for each class
10. Error handling: Input validation and buffer management
*/