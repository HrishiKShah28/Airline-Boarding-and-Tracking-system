#pragma once
#include <iostream>
#include <string>
#include <utility>   // for std::move
using namespace std;

#include "Passenger.h"

class Flight {
private:
    string flightNo;
    string source;
    string destination;
    string gateNo;

    Passenger* passengers[100] = {nullptr};  // fixed-size array of pointers
    int passengerCount;                      // keep track of number of passengers

public:
    // constructor takes const references for efficiency
    Flight(const string& fNo, const string& src,
           const string& dest, const string& gate)
        : flightNo(fNo), source(src), destination(dest),
          gateNo(gate), passengerCount(0) {}

    ~Flight() {
        // cleanup manually allocated passengers
        for (int i = 0; i < passengerCount; i++) {
            delete passengers[i];
        }
    }

    // prevent copy
    Flight(const Flight&) = delete;
    Flight& operator=(const Flight&) = delete;

    // add passenger using raw pointer
    void addPassenger(Passenger* p) {
        if (passengerCount < 100) {
            passengers[passengerCount++] = p;
            cout << "Passenger added successfully.\n";
        } else {
            cout << "Cannot add more passengers. Flight is full.\n";
            delete p; // avoid memory leak
        }
    }

    void startBoarding() {
        cout << "\nBoarding started for flight " << flightNo
             << " from " << source << " to " << destination
             << " at Gate " << gateNo << endl;

        cout << "\n--- Boarding Passengers ---\n";
        for (int i = 0; i < passengerCount; i++) {
            passengers[i]->boardFlight();
        }
    }

    void showPassengerStatus() const {
        cout << "\nPassenger Status for flight " << flightNo << ":\n";
        for (int i = 0; i < passengerCount; i++) {
            cout << "- " << passengers[i]->getName()
                 << " (" << passengers[i]->getSeatNo()
                 << ") : " << passengers[i]->getStatus() << endl;
        }
    }
};
