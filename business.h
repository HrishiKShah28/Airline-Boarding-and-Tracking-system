class BusinessPassenger : public Passenger
{
private:
    bool lounge;
    bool priority;
    int baggage;
    double fare;
    friend void showBusinessDetails(const BusinessPassenger &bp);

public:
    BusinessPassenger()
        : Passenger("", "", "", true), lounge(true), priority(true),
          baggage(40), fare(1500.0)
    {
        cout << "Business Passenger created (Default Constructor)" << endl;
    }

    BusinessPassenger(string nm, string pp, string st)
        : Passenger(move(nm), move(pp), move(st), true), lounge(true),
          priority(true), baggage(40), fare(1500.0)
    {
        cout << "Business Passenger created for " << getName() << endl;
    }

    void boardFlight() override
    {
        updateStatus(Status::BoardedBusiness);
        cout << "PRIORITY BOARDING: Business passenger " << getName() << " has boarded." << endl;
    }

    void show() const
    {
        cout << "\n--- BUSINESS CLASS PASSENGER ---" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Passport No: " << getPassportNo() << endl;
        cout << "Seat No: " << getSeatNo() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Lounge Access: " << (lounge ? "Yes" : "No") << endl;
        cout << "Priority Boarding: " << (priority ? "Yes" : "No") << endl;
        cout << "Baggage: " << baggage << " kg" << endl;
    }

    double totalFare() const
    {
        return fare;
    }

    ~BusinessPassenger()
    {
        cout << "Business Passenger " << getName() << " destroyed" << endl;
    }
};

void showBusinessDetails(const BusinessPassenger &bp)
{
    cout << "\n--- FRIEND FUNCTION ACCESS ---" << endl;
    cout << "Details for: " << bp.getName() << endl;
    cout << "Base Fare: $" << bp.fare << endl;
    cout << "Has Lounge Access: " << (bp.lounge ? "Yes" : "No") << endl;
}