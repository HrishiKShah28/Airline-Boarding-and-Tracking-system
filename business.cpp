#include <iostream>
using namespace std;

class BusinessPassenger : public Passenger {
    bool loungeAccess;
    bool priorityBoarding;
    int baggageWeight;
    double baseFare;
    string seatNumber;
    bool hasBoarded;

public:
    BusinessPassenger() : Passenger() {
        loungeAccess = true;
        priorityBoarding = true;
        baggageWeight = 0;
        baseFare = 1500.0;
        hasBoarded = false;
        seatNumber = "Not Assigned";
        cout << "Business Passenger created (Default Constructor)" << endl;
    }

    BusinessPassenger(string id, string n, int a, string passport, 
                      int bagWeight = 30) 
        : Passenger(id, n, a, passport) {
        loungeAccess = true;
        priorityBoarding = true;
        baggageWeight = bagWeight;
        baseFare = 1500.0;
        hasBoarded = false;
        seatNumber = "Not Assigned";
        cout << "Business Passenger created for " << name << endl;
    }

    void displayInfo() const {
        cout << "\nBUSINESS CLASS" << endl;
        Passenger::displayInfo();
        cout << "Lounge Access: " << (loungeAccess ? "Yes" : "No") << endl;
        cout << "Priority Boarding: " << (priorityBoarding ? "Yes" : "No") << endl;
        cout << "Baggage Weight: " << baggageWeight << " kg" << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Total Fare: $" << calculateFare() << endl;
    }

    double calculateFare() {
        double totalFare = baseFare;
        if (baggageWeight > 40) totalFare += (baggageWeight - 40) * 25;
        return totalFare;
    }

    void boardPassenger() {
        hasBoarded = true;
        cout << "PRIORITY BOARDING" << endl;
        cout << "Business class passenger " << name << " has priority boarded." << endl;
    }

    void accessLounge() {
        if (loungeAccess) cout << name << " is accessing the Business Lounge." << endl;
    }

    void assignSeat(string seat) {
        seatNumber = seat;
        cout << "Premium seat " << seat << " assigned to " << name << endl;
    }

    void allocateExtraBaggage(int extraKg) {
        int* extra = new int(extraKg);
        baggageWeight += *extra;
        cout << "Extra " << *extra << " kg baggage allocated to " << name << endl;
        delete extra;
    }

    ~BusinessPassenger() {
        cout << "Business Passenger " << name << " destroyed" << endl;
    }

    friend void compareBusinessFare(BusinessPassenger& p1, BusinessPassenger& p2) {
        if (p1.calculateFare() > p2.calculateFare())
            cout << p1.name << " has a higher fare." << endl;
        else if (p1.calculateFare() < p2.calculateFare())
            cout << p2.name << " has a higher fare." << endl;
        else
            cout << "Both business passengers have equal fare." << endl;
    }
};
