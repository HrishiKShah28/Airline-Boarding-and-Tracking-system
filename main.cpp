#include <iostream>
#include <memory>
using namespace std;

#include "Passenger.h"
#include "BusinessClass.h"
#include "EconomyClass.h"
#include "FlightClass.h"

int main() {
    Flight f("AI202", "Delhi", "Mumbai", "G12");

    f.addPassenger(make_unique<BusinessPassenger>("Raj", "P123", "1A"));
    f.addPassenger(make_unique<EconomyPassenger>("Anita", "P456", "12B"));
    f.addPassenger(make_unique<EconomyPassenger>("Karan", "P789", "15C"));

    f.startBoarding();
    f.showPassengerStatus();

    return 0;
}
