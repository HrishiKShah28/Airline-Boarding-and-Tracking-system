#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "passenger.h"

using namespace std;

class Flight {
private:
    string flightNo;
    string source;
    string destination;
    string gateNo;
    vector<unique_ptr<Passenger>> passengers;

public:
    Flight(string f, string s, string d, string g) {
        flightNo = f;
        source = s;
        destination = d;
        gateNo = g;
    }

    // prevent copying (unique_ptr cannot be copied)
    Flight(const Flight&) = delete;
    Flight& operator=(const Flight&) = delete;

    // allow moving
    Flight(Flight&&) = default;
    Flight& operator=(Flight&&) = default;

    // add a passenger (takes ownership)
    void addPassenger(unique_ptr<Passenger> p) {
        passengers.push_back(move(p));
    }

    // boarding logic
    void startBoarding() {
        cout << "\nBoarding started for flight " << flightNo
             << " from " << source << " to " << destination
             << " at Gate " << gateNo << endl;

        cout << "\n--- Business Class Boarding ---\n";
        for (auto &p : passengers) {
            if (p->getIsBusinessClass()) {
                p->boardFlight(); // BusinessPassenger boarding
            }
        }

        cout << "\n--- Economy Class Boarding ---\n";
        for (auto &p : passengers) {
            if (!p->getIsBusinessClass()) {
                p->boardFlight(); // EconomyPassenger boarding
            }
        }
    }

    // show all passenger status
    void showPassengerStatus() const {
        cout << "\nPassenger Status for flight " << flightNo << ":\n";
        for (auto &p : passengers) {
            cout << "- " << p->getName()
                 << " (" << p->getSeatNo()
                 << ") : " << p->getStatus() << endl;
        }
    }
};
