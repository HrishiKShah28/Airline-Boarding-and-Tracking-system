#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using std::string;

class Passenger {
protected:
    string name;
    string passportNo;
    string seatNo;
    string status;
    bool isBusinessClass;

public:
    Passenger(string n, string p, string seat, bool business)
        : name(n), passportNo(p), seatNo(seat),
          isBusinessClass(business), status("Checked-in") {}

    virtual ~Passenger() = default;

    string getName() const { return name; }
    string getPassportNo() const { return passportNo; }
    string getSeatNo() const { return seatNo; }
    string getStatus() const { return status; }
    void updateStatus(string s) { status = s; }

    virtual void boardFlight() = 0; // Pure virtual
};

class BusinessPassenger : public Passenger {
public:
    BusinessPassenger(string n, string p, string seat)
        : Passenger(n, p, seat, true) {}

    void boardFlight() override {
        updateStatus("Boarded (Business)");
        std::cout << "Business Passenger " << name
                  << " (Seat " << seatNo << ") boarded.\n";
    }
};

class EconomyPassenger : public Passenger {
public:
    EconomyPassenger(string n, string p, string seat)
        : Passenger(n, p, seat, false) {}

    void boardFlight() override {
        updateStatus("Boarded (Economy)");
        std::cout << "Economy Passenger " << name
                  << " (Seat " << seatNo << ") boarded.\n";
    }
};

#endif
