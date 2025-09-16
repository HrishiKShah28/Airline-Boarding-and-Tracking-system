#include <iostream>
using namespace std;

class BusinessPassenger : public Passenger {
    bool lounge;
    bool priority;
    int bags;
    double fare;
    string seat;
    bool boarded;

public:
    BusinessPassenger() : Passenger() {
        lounge = true;
        priority = true;
        bags = 0;
        fare = 1500.0;
        boarded = false;
        seat = "Not Assigned";
        cout << "Business Passenger created (Default Constructor)" << endl;
    }

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

    void show() const {
        cout << "\nBUSINESS CLASS" << endl;
        Passenger::displayInfo();
        cout << "Lounge Access: " << (lounge ? "Yes" : "No") << endl;
        cout << "Priority Boarding: " << (priority ? "Yes" : "No") << endl;
        cout << "Baggage: " << bags << " kg" << endl;
        cout << "Seat: " << seat << endl;
        cout << "Total Fare: $" << totalFare() << endl;
    }

    double totalFare() {
        double t = fare;
        if (bags > 40) t += (bags - 40) * 25;
        return t;
    }

    void board() {
        boarded = true;
        cout << "PRIORITY BOARDING" << endl;
        cout << "Business passenger " << name << " boarded." << endl;
    }

    void loungeUse() {
        if (lounge) cout << name << " is in Business Lounge." << endl;
    }

    void setSeat(string s) {
        seat = s;
        cout << "Premium seat " << s << " assigned to " << name << endl;
    }

    void addBags(int extra) {
        int* x = new int(extra);
        bags += *x;
        cout << "Extra " << *x << " kg baggage added for " << name << endl;
        delete x;
    }

    ~BusinessPassenger() {
        cout << "Business Passenger " << name << " destroyed" << endl;
    }

    friend void compareFare(BusinessPassenger& p1, BusinessPassenger& p2) {
        if (p1.totalFare() > p2.totalFare())
            cout << p1.name << " has higher fare." << endl;
        else if (p1.totalFare() < p2.totalFare())
            cout << p2.name << " has higher fare." << endl;
        else
            cout << "Both have equal fare." << endl;
    }
};
