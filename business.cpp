## **business.cpp**
```cpp
#include "business.h"
#include <iostream>
using namespace std;

BusinessPassenger::BusinessPassenger() : Passenger() {
    loungeAccess = true;
    priorityBoarding = true;
    baggageWeight = 0;
    baseFare = 1500.0;
    cout << "Business Passenger created (Default Constructor)" << endl;
}

BusinessPassenger::BusinessPassenger(string id, string n, int a, string passport, int bagWeight) 
    : Passenger(id, n, a, passport) {
    loungeAccess = true;
    priorityBoarding = true;
    baggageWeight = bagWeight;
    baseFare = 1500.0;
    cout << "Business Passenger created for " << name << endl;
}

void BusinessPassenger::displayInfo() const {
    cout << "\nBUSINESS CLASS" << endl;
    Passenger::displayInfo();
    cout << "Lounge Access: " << (loungeAccess ? "Yes" : "No") << endl;
    cout << "Priority Boarding: " << (priorityBoarding ? "Yes" : "No") << endl;
    cout << "Baggage Weight: " << baggageWeight << " kg" << endl;
    cout << "Total Fare: $" << calculateFare() << endl;
}

double BusinessPassenger::calculateFare() {
    double totalFare = baseFare;
    
    if (baggageWeight > 40) {
        totalFare += (baggageWeight - 40) * 25;
    }
    
    return totalFare;
}

void BusinessPassenger::boardPassenger() {
    hasBoarded = true;
    cout << "PRIORITY BOARDING" << endl;
    cout << "Business class passenger " << name << " has priority boarded." << endl;
}

void BusinessPassenger::accessLounge() {
    if (loungeAccess) {
        cout << name << " is accessing the Business Lounge." << endl;
    }
}

void BusinessPassenger::assignSeat(string seat) {
    seatNumber = seat;
    cout << "Premium seat " << seat << " assigned to " << name << endl;
}

BusinessPassenger::~BusinessPassenger() {
    cout << "Business Passenger " << name << " destroyed" << endl;
}
```
