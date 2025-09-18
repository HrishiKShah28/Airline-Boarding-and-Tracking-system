#pragma once
#include "passenger.h"
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
    void boardFlight() override {
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