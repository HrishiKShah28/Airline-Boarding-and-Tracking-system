class Flight {
private:
    string flightNo;
    string source, destination, gateNo;
    vector<Passenger*> passengers;

public:

    Flight(string f, string s, string d, string g)
        : flightNo(f), source(s), destination(d), gateNo(g) {}

    void addPassenger(Passenger* p) {
        passengers.push_back(p);
    }

    void startBoarding() {
        cout << "\nBoarding started for flight " << flightNo
             << " from " << source << " to " << destination
             << " at Gate " << gateNo << endl;

        // Priority: Business first
        cout << "\n--- Business Class Boarding ---\n";
        for (auto p : passengers) {
            if (dynamic_cast<BusinessPassenger*>(p)) {
                p->boardFlight();  // Polymorphism in action
            }
        }

        cout << "\n--- Economy Class Boarding ---\n";
        for (auto p : passengers) {
            if (dynamic_cast<EconomyPassenger*>(p)) {
                p->boardFlight();
            }
        }
    }

    void showPassengerStatus() {
        cout << "\nPassenger Status for flight " << flightNo << ":\n";
        for (auto p : passengers) {
            cout << "- " << p->getName() << " (" << p->getSeatNo()
                 << ") : " << p->getStatus() << endl;
        }
    }

    ~Flight() {
        for (auto p : passengers) delete p;
    }
};
