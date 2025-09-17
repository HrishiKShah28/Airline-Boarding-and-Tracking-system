#pragma once
#include "passenger.h"
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
    void boardFlight() override {
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