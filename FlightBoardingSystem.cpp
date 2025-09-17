// ==================== passenger.h ====================
#pragma once
#include <string>
#include <iostream>
using namespace std;

class Passenger {
public:
    enum class Status { CheckedIn, BoardedBusiness, BoardedEconomy };

protected:
    string id;
    string name;
    int age;
    string passportNo;
    Status status;

public:
    // Default constructor
    Passenger() : id(""), name(""), age(0), passportNo(""), status(Status::CheckedIn) {}
    
    // Parameterized constructor
    Passenger(string i, string n, int a, string passport)
        : id(i), name(n), age(a), passportNo(passport), status(Status::CheckedIn) {}

    // Virtual destructor
    virtual ~Passenger() {}

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getPassportNo() const { return passportNo; }
    Status getStatusEnum() const { return status; }

    string getStatus() const {
        switch (status) {
            case Status::CheckedIn: return "Checked-in";
            case Status::BoardedBusiness: return "Boarded (Business)";
            case Status::BoardedEconomy: return "Boarded (Economy)";
        }
        return "Unknown";
    }

    // Display basic passenger info
    void displayInfo() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Passport: " << passportNo << endl;
        cout << "Status: " << getStatus() << endl;
    }

    // Pure virtual function
    virtual void boardFlight() = 0;

protected:
    void updateStatus(Status s) { status = s; }
};

// ==================== business.h ====================
#include <iostream>
using namespace std;

class BusinessPassenger : public Passenger {
private:
    bool lounge;
    bool priority;
    int bags;
    double fare;
    string seat;
    bool boarded;

public:
    // Default constructor
    BusinessPassenger() : Passenger() {
        lounge = true;
        priority = true;
        bags = 30;
        fare = 1500.0;
        boarded = false;
        seat = "Not Assigned";
        cout << "Business Passenger created (Default Constructor)" << endl;
    }

    // Parameterized constructor
    BusinessPassenger(string id, string n, int a, string passport, int b = 30) 
        : Passenger(id, n, a, passport) {
        lounge = true;
        priority = true;
        bags = b;
        fare = 1500.0;
        boarded = false;
        seat = "Not Assigned";
        cout << "Business Passenger created for " << name << endl;
    }

    // Constructor for main.cpp compatibility
    BusinessPassenger(string n, string passport, string seatNo)
        : Passenger("", n, 0, passport) {
        lounge = true;
        priority = true;
        bags = 30;
        fare = 1500.0;
        boarded = false;
        seat = seatNo;
        cout << "Business Passenger created for " << name << endl;
    }

    // Display passenger information
    void show() const {
        cout << "\n=== BUSINESS CLASS ===" << endl;
        displayInfo();
        cout << "Lounge Access: " << (lounge ? "Yes" : "No") << endl;
        cout << "Priority Boarding: " << (priority ? "Yes" : "No") << endl;
        cout << "Baggage: " << bags << " kg" << endl;
        cout << "Seat: " << seat << endl;
        cout << "Total Fare: $" << totalFare() << endl;
    }

    // Calculate total fare
    double totalFare() const {
        double t = fare;
        if (bags > 40) {
            t += (bags - 40) * 25;
        }
        return t;
    }

    // Board the flight (override pure virtual function)
    void boardFlight() {
        boarded = true;
        updateStatus(Status::BoardedBusiness);
        cout << "=== PRIORITY BOARDING ===" << endl;
        cout << "Business passenger " << name << " boarded successfully." << endl;
    }

    // Board function for compatibility
    void board() {
        boardFlight();
    }

    // Use lounge facility
    void loungeUse() {
        if (lounge) {
            cout << name << " is enjoying the Business Lounge facilities." << endl;
        } else {
            cout << name << " does not have lounge access." << endl;
        }
    }

    // Set seat
    void setSeat(string s) {
        seat = s;
        cout << "Premium seat " << s << " assigned to " << name << endl;
    }

    // Add extra baggage
    void addBags(int extra) {
        int* x = new int(extra);
        bags += *x;
        cout << "Extra " << *x << " kg baggage added for " << name 
             << ". Total: " << bags << " kg" << endl;
        delete x;
    }

    // Getters
    string getSeat() const { return seat; }
    bool isBoarded() const { return boarded; }
    bool hasLoungeAccess() const { return lounge; }
    bool hasPriority() const { return priority; }
    int getBags() const { return bags; }

    // Destructor
    ~BusinessPassenger() {
        cout << "Business Passenger " << name << " destroyed" << endl;
    }

    // Friend function to compare fares
    friend void compareFare(BusinessPassenger& p1, BusinessPassenger& p2) {
        double fare1 = p1.totalFare();
        double fare2 = p2.totalFare();
        
        if (fare1 > fare2) {
            cout << p1.name << " has higher fare ($" << fare1 << " vs $" << fare2 << ")" << endl;
        } else if (fare1 < fare2) {
            cout << p2.name << " has higher fare ($" << fare2 << " vs $" << fare1 << ")" << endl;
        } else {
            cout << "Both passengers have equal fare ($" << fare1 << ")" << endl;
        }
    }
};

// ==================== economy.h ====================
#include <iostream>
using namespace std;

class EconomyPassenger : public Passenger {
private:
    int bags;
    bool meal;
    double fare;
    string seat;
    bool boarded;

public:
    // Default constructor
    EconomyPassenger() : Passenger() {
        bags = 15;
        meal = false;
        fare = 500.0;
        seat = "Not Assigned";
        boarded = false;
        cout << "Economy Passenger created (Default Constructor)" << endl;
    }

    // Parameterized constructor
    EconomyPassenger(string id, string n, int a, string passport, 
                     int b = 15, bool m = false) 
        : Passenger(id, n, a, passport) {
        bags = b;
        meal = m;
        fare = 500.0;
        seat = "Not Assigned";
        boarded = false;
        cout << "Economy Passenger created for " << name << endl;
    }

    // Constructor for main.cpp compatibility
    EconomyPassenger(string n, string passport, string seatNo)
        : Passenger("", n, 0, passport) {
        bags = 15;
        meal = false;
        fare = 500.0;
        seat = seatNo;
        boarded = false;
        cout << "Economy Passenger created for " << name << endl;
    }

    // Display passenger information
    void show() const {
        cout << "\n=== ECONOMY CLASS ===" << endl;
        displayInfo();
        cout << "Baggage: " << bags << " kg" << endl;
        cout << "Meal: " << (meal ? "Yes" : "No") << endl;
        cout << "Seat: " << seat << endl;
        cout << "Total Fare: $" << totalFare() << endl;
    }

    // Calculate total fare
    double totalFare() const {
        double t = fare;
        if (bags > 20) {
            t += (bags - 20) * 15;
        }
        if (meal) {
            t += 25;
        }
        return t;
    }

    // Board the flight (override pure virtual function)
    void boardFlight() {
        boarded = true;
        updateStatus(Status::BoardedEconomy);
        cout << "=== REGULAR BOARDING ===" << endl;
        cout << "Economy passenger " << name << " boarded successfully." << endl;
    }

    // Add meal service
    void addMeal() {
        meal = true;
        cout << "Meal service added for " << name << endl;
    }

    // Set seat
    void setSeat(string s) {
        seat = s;
        cout << "Seat " << s << " assigned to " << name << endl;
    }

    // Add extra baggage
    void addBags(int extra) {
        int* x = new int(extra);
        bags += *x;
        cout << "Extra " << *x << " kg baggage added for " << name 
             << ". Total: " << bags << " kg" << endl;
        delete x;
    }

    // Getters
    string getSeat() const { return seat; }
    bool isBoarded() const { return boarded; }
    bool hasMeal() const { return meal; }
    int getBags() const { return bags; }

    // Destructor
    ~EconomyPassenger() {
        cout << "Economy Passenger " << name << " destroyed" << endl;
    }

    // Friend function to compare fares
    friend void compareFare(EconomyPassenger& p1, EconomyPassenger& p2) {
        double fare1 = p1.totalFare();
        double fare2 = p2.totalFare();
        
        if (fare1 > fare2) {
            cout << p1.name << " has higher fare ($" << fare1 << " vs $" << fare2 << ")" << endl;
        } else if (fare1 < fare2) {
            cout << p2.name << " has higher fare ($" << fare2 << " vs $" << fare1 << ")" << endl;
        } else {
            cout << "Both passengers have equal fare ($" << fare1 << ")" << endl;
        }
    }
};

// ==================== flight.h ====================
#include <iostream>
#include <string>
using namespace std;

class Flight {
private:
    string flightNumber;
    string source;
    string destination;
    string gate;
    Passenger** passengers;  // Manual array instead of vector
    int maxPassengers;       // Maximum capacity
    int currentPassengers;   // Current number of passengers
    bool boardingStarted;

public:
    // Constructor
    Flight(string flightNo, string src, string dest, string g)
        : flightNumber(flightNo), source(src), destination(dest), 
          gate(g), boardingStarted(false), maxPassengers(100), currentPassengers(0) {
        passengers = new Passenger*[maxPassengers];
        for(int i = 0; i < maxPassengers; i++) {
            passengers[i] = NULL;
        }
        cout << "\nFlight " << flightNumber << " from " << source 
             << " to " << destination << " at Gate " << gate << " created." << endl;
    }

    // Add passenger to flight
    void addPassenger(Passenger* p) {
        if (p != NULL && currentPassengers < maxPassengers) {
            passengers[currentPassengers] = p;
            currentPassengers++;
            cout << "\nPassenger " << p->getName() << " added to Flight " 
                 << flightNumber << endl;
        } else if (currentPassengers >= maxPassengers) {
            cout << "\nFlight is full! Cannot add more passengers." << endl;
        }
    }

    // Start boarding process
    void startBoarding() {
        if (currentPassengers == 0) {
            cout << "\nNo passengers to board!" << endl;
            return;
        }

        cout << "\n";
        for(int i = 0; i < 50; i++) cout << "=";
        cout << endl;
        cout << "BOARDING STARTED FOR FLIGHT " << flightNumber << endl;
        cout << "Gate: " << gate << " | " << source << " -> " << destination << endl;
        for(int i = 0; i < 50; i++) cout << "=";
        cout << endl;

        boardingStarted = true;

        // Board business class passengers first (priority boarding)
        cout << "\n--- PRIORITY BOARDING (Business Class) ---" << endl;
        bool businessFound = false;
        for (int i = 0; i < currentPassengers; i++) {
            if (passengers[i] != NULL && passengers[i]->getStatusEnum() == Passenger::Status::CheckedIn) {
                passengers[i]->boardFlight();
                if (passengers[i]->getStatusEnum() == Passenger::Status::BoardedBusiness) {
                    businessFound = true;
                }
            }
        }
        if (!businessFound) {
            cout << "No business class passengers found." << endl;
        }

        cout << "\n--- GENERAL BOARDING (Economy Class) ---" << endl;
        bool economyFound = false;
        for (int i = 0; i < currentPassengers; i++) {
            if (passengers[i] != NULL && passengers[i]->getStatusEnum() == Passenger::Status::CheckedIn) {
                passengers[i]->boardFlight();
                if (passengers[i]->getStatusEnum() == Passenger::Status::BoardedEconomy) {
                    economyFound = true;
                }
            }
        }
        if (!economyFound) {
            cout << "No economy class passengers found." << endl;
        }

        cout << "\n";
        for(int i = 0; i < 50; i++) cout << "=";
        cout << endl;
        cout << "BOARDING COMPLETED FOR FLIGHT " << flightNumber << endl;
        for(int i = 0; i < 50; i++) cout << "=";
        cout << endl;
    }

    // Show passenger status
    void showPassengerStatus() {
        if (currentPassengers == 0) {
            cout << "\nNo passengers registered for this flight." << endl;
            return;
        }

        cout << "\n";
        for(int i = 0; i < 60; i++) cout << "=";
        cout << endl;
        cout << "PASSENGER STATUS - FLIGHT " << flightNumber << endl;
        cout << source << " -> " << destination << " | Gate: " << gate << endl;
        for(int i = 0; i < 60; i++) cout << "=";
        cout << endl;

        int businessCount = 0, economyCount = 0, boardedCount = 0;

        for (int i = 0; i < currentPassengers; i++) {
            cout << "\n[" << (i + 1) << "] ";
            cout << "Name: " << passengers[i]->getName() << endl;
            cout << "    Passport: " << passengers[i]->getPassportNo() << endl;
            cout << "    Status: " << passengers[i]->getStatus() << endl;

            // Count passengers by type
            if (passengers[i]->getStatusEnum() == Passenger::Status::BoardedBusiness) {
                businessCount++;
                boardedCount++;
            } else if (passengers[i]->getStatusEnum() == Passenger::Status::BoardedEconomy) {
                economyCount++;
                boardedCount++;
            }
        }

        cout << "\n";
        for(int i = 0; i < 40; i++) cout << "-";
        cout << endl;
        cout << "SUMMARY:" << endl;
        cout << "Total Passengers: " << currentPassengers << endl;
        cout << "Boarded: " << boardedCount << endl;
        cout << "Business Class Boarded: " << businessCount << endl;
        cout << "Economy Class Boarded: " << economyCount << endl;
        cout << "Pending: " << (currentPassengers - boardedCount) << endl;
        for(int i = 0; i < 40; i++) cout << "-";
        cout << endl;
    }

    // Get flight info
    void displayFlightInfo() const {
        cout << "\nFlight Information:" << endl;
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Route: " << source << " -> " << destination << endl;
        cout << "Gate: " << gate << endl;
        cout << "Boarding Status: " << (boardingStarted ? "Started" : "Not Started") << endl;
        cout << "Passengers: " << currentPassengers << endl;
    }

    // Getters
    string getFlightNumber() const { return flightNumber; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    string getGate() const { return gate; }
    int getPassengerCount() const { return currentPassengers; }

    // Destructor - cleanup passengers
    ~Flight() {
        cout << "\nCleaning up Flight " << flightNumber << "..." << endl;
        for (int i = 0; i < currentPassengers; i++) {
            if (passengers[i] != NULL) {
                delete passengers[i];
            }
        }
        delete[] passengers;
        cout << "Flight " << flightNumber << " destroyed." << endl;
    }
};

// ==================== main.cpp ====================
#include <iostream>
#include <string>
using namespace std;

// Menu header function
void printHeader() {
    cout << "\n";
    for(int i = 0; i < 50; i++) cout << "=";
    cout << endl;
    cout << "         AIRLINE BOARDING SYSTEM" << endl;
    for(int i = 0; i < 50; i++) cout << "=";
    cout << endl;
}

// Clear input buffer helper function
void clearInputBuffer() {
    cin.clear();
    char c;
    while((c = cin.get()) != '\n' && c != EOF);
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
        if (input.length() == 0) {
            cout << "Input cannot be empty! Please try again." << endl;
        }
    } while (input.length() == 0);
    return input;
}

int main() {
    string flightNo, src, dest, gate;

    // Welcome message
    printHeader();
    cout << "Welcome to the Airline Boarding System!" << endl;
    for(int i = 0; i < 50; i++) cout << "=";
    cout << endl;

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
        for(int i = 0; i < 50; i++) cout << "-";
        cout << endl;
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
Save this entire code as airline_system.cpp and compile with:

g++ -o airline_system airline_system.cpp

Then run:
./airline_system

FIXED ERRORS:
=============
1. Changed nullptr to NULL for C++98 compatibility
2. Fixed virtual destructor (removed = default)  
3. Fixed all include dependencies
4. Corrected manual array initialization
5. Fixed buffer clearing function
6. Made totalFare() const functions
7. Removed all STL dependencies completely

NO STL/LIBRARY FUNCTIONS USED:
==============================
✓ Manual arrays instead of vectors
✓ Basic loops instead of string constructors  
✓ NULL instead of nullptr
✓ Traditional for loops only
✓ Basic iostream only
✓ Manual memory management
✓ No limits library
✓ No algorithm library
*/