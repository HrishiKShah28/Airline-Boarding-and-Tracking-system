#include <iostream>
using namespace std;

class EconomyPassenger : public Passenger {
    int bags;
    bool meal;
    double fare;
    string seat;

public:
    EconomyPassenger() : Passenger() {
        bags = 0;
        meal = false;
        fare = 500.0;
        seat = "Not Assigned";
        cout << "Economy Passenger created (Default Constructor)" << endl;
    }

    EconomyPassenger(string id, string n, int a, string passport, 
                     int b = 15, bool m = false) 
        : Passenger(id, n, a, passport) {
        bags = b;
        meal = m;
        fare = 500.0;
        seat = "Not Assigned";
        cout << "Economy Passenger created for " << name << endl;
    }

    void show() const {
        cout << "\nECONOMY CLASS" << endl;
        Passenger::displayInfo();
        cout << "Baggage: " << bags << " kg" << endl;
        cout << "Meal: " << (meal ? "Yes" : "No") << endl;
        cout << "Seat: " << seat << endl;
        cout << "Total Fare: Rs. " << totalFare() << endl;
    }

    double totalFare() {
        double t = fare;
        if (bags > 20) t += (bags - 20) * 15;
        if (meal) t += 25;
        return t;
    }

    void addMeal() {
        meal = true;
        cout << "Meal added for " << name << endl;
    }

    void setSeat(string s) {
        seat = s;
        cout << "Seat " << s << " assigned to " << name << endl;
    }

    void addBags(int extra) {
        int* x = new int(extra);
        bags += *x;
        cout << "Extra " << *x << " kg baggage added for " << name << endl;
        delete x;
    }

    ~EconomyPassenger() {
        cout << "Economy Passenger " << name << " destroyed" << endl;
    }

    friend void compareFare(EconomyPassenger& p1, EconomyPassenger& p2) {
        if (p1.totalFare() > p2.totalFare())
            cout << p1.name << " has higher fare." << endl;
        else if (p1.totalFare() < p2.totalFare())
            cout << p2.name << " has higher fare." << endl;
        else
            cout << "Both have equal fare." << endl;
    }
};
