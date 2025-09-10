class EconomyPassenger : public Passenger {
public:
    EconomyPassenger(string n, string p, string seat)
        : Passenger(move(n), move(p), move(seat), false) {}

    void boardFlight() override {
        updateStatus(Status::BoardedEconomy);
        cout << "Economy Passenger " << getName()
             << " (Seat " << getSeatNo() << ") boarded.\n";
    }
};
