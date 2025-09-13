#include <iostream>
using namespace std;

EconomyPassenger::EconomyPassenger() : Passenger() {
    baggageWeight = 0;
    mealIncluded = false;
    baseFare = 500.0;
    cout << "Economy Passenger created (Default Constructor)" << endl;
}

EconomyPassenger::EconomyPassenger(string id, string n, int a, string passport, int bagWeight, bool meal) 
    : Passenger(id, n, a, passport) {
    baggageWeight = bagWeight;
    mealIncluded = meal;
    baseFare = 500.0;
    cout << "Economy Passenger created for " << name << endl;
}

void EconomyPassenger::displayInfo() const {
    cout << "\nECONOMY CLASS" << endl;
    Passenger::displayInfo();
    cout << "Baggage Weight: " << baggageWeight << " kg" << endl;
    cout << "Meal Included: " << (mealIncluded ? "Yes" : "No") << endl;
    cout << "Total Fare: Rupees" << calculateFare() << endl;
}

double EconomyPassenger::calculateFare() {
    double totalFare = baseFare;
   
    if (baggageWeight > 20) {
        totalFare += (baggageWeight - 20) * 15;
    }
    
    if (mealIncluded) {
        totalFare += 25;
    }
    
    return totalFare;
}

void EconomyPassenger::addMeal() {
    mealIncluded = true;
    cout << "Meal added for passenger " << name << endl;
}

void EconomyPassenger::assignSeat(string seat) {
    seatNumber = seat;
    cout << "Seat " << seat << " assigned to " << name << endl;
}

EconomyPassenger::~EconomyPassenger() {
    cout << "Economy Passenger " << name << " destroyed" << endl;
}
