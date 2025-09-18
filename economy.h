class EconomyPassenger : public Passenger
{
private:
    int baggage;
    bool meal;
    double fare;

public:
    EconomyPassenger(string nm, string pp, string st)
        : Passenger(nm, pp, st, false), baggage(20),
          meal(false), fare(500.0)
    {
        cout << "Economy Passenger created for " << getName() << endl;
    }

    void boardFlight() override
    {
        updateStatus(Status::BoardedEconomy);
        cout << "Economy passenger " << getName() << " has boarded." << endl;
    }

    void show() const
    {
        cout << "\n--- ECONOMY CLASS PASSENGER ---" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Passport No: " << getPassportNo() << endl;
        cout << "Seat No: " << getSeatNo() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Baggage: " << baggage << " kg" << endl;
        cout << "Meal Included: " << (meal ? "Yes" : "No") << endl;
        cout << "Total Fare: $" << totalFare() << endl;
    }

    double totalFare() const
    {
        return fare;
    }

    ~EconomyPassenger()
    {
        cout << "Economy Passenger " << getName() << " destroyed" << endl;
    }
};