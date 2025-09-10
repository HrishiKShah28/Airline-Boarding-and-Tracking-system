#include "passenger.h"
#include "flightclass.cpp" // better to use flight.h later

int main() {
    Flight f("AI202", "Delhi", "Mumbai", "G12");

    f.addPassenger(std::make_unique<BusinessPassenger>("Raj", "P123", "1A"));
    f.addPassenger(std::make_unique<EconomyPassenger>("Anita", "P456", "12B"));
    f.addPassenger(std::make_unique<EconomyPassenger>("Karan", "P789", "15C"));

    f.startBoarding();
    f.showPassengerStatus();

    return 0;
}
