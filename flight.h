#pragma once
#include "passenger.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Flight {
private:
    string flightNumber;
    string source;
    string destination;
    string gate;
    vector<Passenger*> passengers;
    bool boardingStarted;

public:
    // Constructor
    Flight(string flightNo, string src, string dest, string g)
        : flightNumber(flightNo), source(src), destination(dest), 
          gate(g), boardingStarted(false) {
        cout << "\nFlight " << flightNumber << " from " << source 
             << " to " << destination << " at Gate " << gate << " created." << endl;
    }

    // Add passenger to flight
    void addPassenger(Passenger* p) {
        if (p != nullptr) {
            passengers.push_back(p);
            cout << "\nPassenger " << p->getName() << " added to Flight " 
                 << flightNumber << endl;
        }
    }

    // Start boarding process
    void startBoarding() {
        if (passengers.empty()) {
            cout << "\nNo passengers to board!" << endl;
            return;
        }

        cout << "\n" << string(50, '=') << endl;
        cout << "BOARDING STARTED FOR FLIGHT " << flightNumber << endl;
        cout << "Gate: " << gate << " | " << source << " → " << destination << endl;
        cout << string(50, '=') << endl;

        boardingStarted = true;

        // Board business class passengers first (priority boarding)
        cout << "\n--- PRIORITY BOARDING (Business Class) ---" << endl;
        bool businessFound = false;
        for (auto* passenger : passengers) {
            // Check if it's a business passenger by trying dynamic_cast
            if (passenger->getStatusEnum() == Passenger::Status::CheckedIn) {
                passenger->boardFlight();
                if (passenger->getStatusEnum() == Passenger::Status::BoardedBusiness) {
                    businessFound = true;
                }
            }
        }
        if (!businessFound) {
            cout << "No business class passengers found." << endl;
        }

        cout << "\n--- GENERAL BOARDING (Economy Class) ---" << endl;
        bool economyFound = false;
        for (auto* passenger : passengers) {
            if (passenger->getStatusEnum() == Passenger::Status::CheckedIn) {
                passenger->boardFlight();
                if (passenger->getStatusEnum() == Passenger::Status::BoardedEconomy) {
                    economyFound = true;
                }
            }
        }
        if (!economyFound) {
            cout << "No economy class passengers found." << endl;
        }

        cout << "\n" << string(50, '=') << endl;
        cout << "BOARDING COMPLETED FOR FLIGHT " << flightNumber << endl;
        cout << string(50, '=') << endl;
    }

    // Show passenger status
    void showPassengerStatus() {
        if (passengers.empty()) {
            cout << "\nNo passengers registered for this flight." << endl;
            return;
        }

        cout << "\n" << string(60, '=') << endl;
        cout << "PASSENGER STATUS - FLIGHT " << flightNumber << endl;
        cout << source << " → " << destination << " | Gate: " << gate << endl;
        cout << string(60, '=') << endl;

        int businessCount = 0, economyCount = 0, boardedCount = 0;

        for (size_t i = 0; i < passengers.size(); ++i) {
            cout << "\n[" << (i + 1) << "] ";
            cout << "Name: " << passengers[i]->getName() << endl;
            cout << "    Passport: " << passengers[i]->getPassportNo() << endl;
            cout << "    Status: " << passengers[i]->getStatus() << endl;

            // Count passengers by type
            if (passengers[i]->getStatusEnum() == Passenger::Status::BoardedBusiness) {
                businessCount++;
                boardedCount++;
            } else if (passengers[i]->getStatusEnum() == Passenger::Status::BoardedEconomy) {
                economyCount++;
                boardedCount++;
            }
        }

        cout << "\n" << string(40, '-') << endl;
        cout << "SUMMARY:" << endl;
        cout << "Total Passengers: " << passengers.size() << endl;
        cout << "Boarded: " << boardedCount << endl;
        cout << "Business Class Boarded: " << businessCount << endl;
        cout << "Economy Class Boarded: " << economyCount << endl;
        cout << "Pending: " << (passengers.size() - boardedCount) << endl;
        cout << string(40, '-') << endl;
    }

    // Get flight info
    void displayFlightInfo() const {
        cout << "\nFlight Information:" << endl;
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Route: " << source << " → " << destination << endl;
        cout << "Gate: " << gate << endl;
        cout << "Boarding Status: " << (boardingStarted ? "Started" : "Not Started") << endl;
        cout << "Passengers: " << passengers.size() << endl;
    }

    // Getters
    string getFlightNumber() const { return flightNumber; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    string getGate() const { return gate; }
    size_t getPassengerCount() const { return passengers.size(); }

    // Destructor - cleanup passengers
    ~Flight() {
        cout << "\nCleaning up Flight " << flightNumber << "..." << endl;
        for (auto* passenger : passengers) {
            delete passenger;
        }
        passengers.clear();
        cout << "Flight " << flightNumber << " destroyed." << endl;
    }
};