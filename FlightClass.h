#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

#include "Passenger.h"

class Flight {
private:
    string flightNo;
    string source;
    string destination;
    string gateNo;
    vector<unique_ptr<Passenger>> passengers;

public:
    Flight(string fNo, string src, string dest, string gate)
        : flightNo(move(fNo)), source(move(src)),
          destination(move(dest)), gateNo(move(gate)) {}

    Flight(const Flight&) = delete;
    Flight& operator=(const Flight&) = delete;

    Flight(Flight&&) = default;
    Flight& operator=(Flight&&) = default;

    void addPassenger(unique_ptr<Passenger> p) {
        passengers.push_back(move(p));
    }

    void startBoarding() {
        cout << "\nBoarding started for flight " << flightNo
             << " from " << source << " to " << destination
             << " at Gate " << gateNo << endl;

        cout << "\n--- Boarding Passengers ---\n";
        for (auto &p : passengers) {
            p->boardFlight();
        }
    }

    void showPassengerStatus() const {
        cout << "\nPassenger Status for flight " << flightNo << ":\n";
        for (auto &p : passengers) {
            cout << "- " << p->getName() << " (" << p->getSeatNo()
                 << ") : " << p->getStatus() << endl;
        }
    }
};
