#include <iostream>
using namespace std;

class EconomyPassenger : public Passenger {
    int baggageWeight;
    bool mealIncluded;
    double baseFare;
    string seatNumber;

public:
    EconomyPassenger() : Passenger() {
        baggageWeight = 0;
        mealIncluded = false;
        baseFare = 500.0;
        seatNumber = "Not Assigned";
        cout << "Economy Passenger created (Default Constructor)" << endl;
    }

    EconomyPassenger(string id, string n, int a, string passport, 
                     int bagWeight = 15, bool meal = false) 
        : Passenger(id, n, a, passport) {
        baggageWeight = bagWeight;
        mealIncluded = meal;
        baseFare = 500.0;
        seatNumber = "Not Assigned";
        cout << "Economy Passenger created for " << name << endl;
    }

    void displayInfo() const {
        cout << "\nECONOMY CLASS" << endl;
        Passenger::displayInfo();
        cout << "Baggage Weight: " << baggageWeight << " kg" << endl;
        cout << "Meal Included: " << (mealIncluded ? "Yes" : "No") << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Total Fare: Rupees " << calculateFare() << endl;
    }

    double calculateFare() {
        double totalFare = baseFare;
        if (baggageWeight > 20) totalFare += (baggageWeight - 20) * 15;
        if (mealIncluded) totalFare += 25;
        return totalFare;
    }

    void addMeal() {
        mealIncluded = true;
        cout << "Meal added for passenger " << name << endl;
    }

    void assignSeat(string seat) {
        seatNumber = seat;
        cout << "Seat " << seat << " assigned to " << name << endl;
    }

    void allocateExtraBaggage(int extraKg) {
        int* extra = new int(extraKg);
        baggageWeight += *extra;
        cout << "Extra " << *extra << " kg baggage allocated to " << name << endl;
        delete extra;
    }

    ~EconomyPassenger() {
        cout << "Economy Passenger " << name << " destroyed" << endl;
    }

    friend void compareFare(EconomyPassenger& p1, EconomyPassenger& p2) {
        if (p1.calculateFare() > p2.calculateFare())
            cout << p1.name << " has a higher fare." << endl;
        else if (p1.calculateFare() < p2.calculateFare())
            cout << p2.name << " has a higher fare." << endl;
        else
            cout << "Both passengers have equal fare." << endl;
    }
};
