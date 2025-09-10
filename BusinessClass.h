#pragma once
#include "Passenger.h"

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
