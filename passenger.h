#pragma once
#include <string>
#include <iostream>

using namespace std;

class Passenger {
public:
    enum class Status { CheckedIn, BoardedBusiness, BoardedEconomy };

private:
    string name;
    string passportNo;
    string seatNo;
    Status status;
    bool isBusinessClass;

protected:
    // only derived classes can make Passenger
    Passenger(string n, string p, string seat, bool business)
        : name(move(n)), passportNo(move(p)),
          seatNo(move(seat)), isBusinessClass(business),
          status(Status::CheckedIn) {}

    void updateStatus(Status s) { status = s; }

public:
    virtual ~Passenger() = default;

    // getters
    string getName() const { return name; }
    string getPassportNo() const { return passportNo; }
    string getSeatNo() const { return seatNo; }
    bool getIsBusinessClass() const { return isBusinessClass; }
    Status getStatusEnum() const { return status; }

    // return status as string
    string getStatus() const {
        switch (status) {
            case Status::CheckedIn: return "Checked-in";
            case Status::BoardedBusiness: return "Boarded (Business)";
            case Status::BoardedEconomy: return "Boarded (Economy)";
        }
        return "Unknown";
    }

    // every derived class must implement this
    virtual void boardFlight() = 0;
};

class BusinessPassenger : public Passenger {
public:
    BusinessPassenger(string n, string p, string seat)
        : Passenger(move(n), move(p), move(seat), true) {}

    void boardFlight() override {
        updateStatus(Status::BoardedBusiness);
        cout << "Business Passenger " << getName()
             << " (Seat " << getSeatNo() << ") boarded.\n";
    }
};


