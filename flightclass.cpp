#pragma once
#include <iostream>
#include <vector>
#include <memory>       // for unique_ptr
#include "passenger.h"

class Flight {
private:
    std::string flightNo;
    std::string source, destination, gateNo;
    std::vector<std::unique_ptr<Passenger>> passengers;

public:
    Flight(std::string f, std::string s, std::string d, std::string g)
        : flightNo(std::move(f)), source(std::move(s)),
          destination(std::move(d)), gateNo(std::move(g)) {}

    // Prevent accidental copying (double ownership)
    Flight(const Flight&) = delete;
    Flight& operator=(const Flight&) = delete;

    // Allow moving if needed
    Flight(Flight&&) = default;
    Flight& operator=(Flight&&) = default;

    void addPassenger(std::unique_ptr<Passenger> p) {
        passengers.push_back(std::move(p));
    }

    void startBoarding() {
        std::cout << "\nBoarding started for flight " << flightNo
                  << " from " << source << " to " << destination
                  << " at Gate " << gateNo << std::endl;

        // Priority-based boarding
        std::cout << "\n--- Business Class Boarding ---\n";
        for (auto& p : passengers) {
            if (p->getIsBusinessClass()) {
                p->boardFlight();
            }
        }

        std::cout << "\n--- Economy Class Boarding ---\n";
        for (auto& p : passengers) {
            if (!p->getIsBusinessClass()) {
                p->boardFlight();
            }
        }
    }

    void showPassengerStatus() const {
        std::cout << "\nPassenger Status for flight " << flightNo << ":\n";
        for (const auto& p : passengers) {
            std::cout << "- " << p->getName() << " (" << p->getSeatNo()
                      << ") : " << p->getStatus() << std::endl;
        }
    }
};
