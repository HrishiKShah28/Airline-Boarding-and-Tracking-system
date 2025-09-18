#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <utility>

using namespace std;

class Flight;

class Passenger
{
public:
    enum class Status
    {
        CheckedIn,
        BoardedBusiness,
        BoardedEconomy
    };

private:
    string name;
    string passportNo;
    string seatNo;
    Status status;
    bool isBusinessClass;

protected:
    Passenger(string n, string p, string seat, bool business)
        : name(move(n)), passportNo(move(p)),
          seatNo(move(seat)), isBusinessClass(business),
          status(Status::CheckedIn) {}

    void updateStatus(Status s) { status = s; }

public:
    virtual ~Passenger() = default;

    string getName() const { return name; }
    string getPassportNo() const { return passportNo; }
    string getSeatNo() const { return seatNo; }
    bool getIsBusinessClass() const { return isBusinessClass; }
    Status getStatusEnum() const { return status; }

    string getStatus() const
    {
        switch (status)
        {
        case Status::CheckedIn:
            return "Checked-in";
        case Status::BoardedBusiness:
            return "Boarded (Business)";
        case Status::BoardedEconomy:
            return "Boarded (Economy)";
        }
        return "Unknown";
    }

    virtual void boardFlight() = 0;
};

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

class Flight
{
private:
    string flightNumber;
    string source;
    string destination;
    string gate;
    vector<Passenger *> passengers;

public:
    Flight(string fn, string src, string dest, string g)
        : flightNumber(move(fn)), source(move(src)), destination(move(dest)), gate(move(g))
    {
        cout << "\nFlight " << flightNumber << " from " << source << " to " << destination << " is ready for check-in at gate " << gate << "." << endl;
    }

    ~Flight()
    {
        for (Passenger *p : passengers)
        {
            delete p;
        }
    }

    void addPassenger(Passenger *p)
    {
        passengers.push_back(p);
        cout << "Passenger " << p->getName() << " added to flight " << flightNumber << "." << endl;
    }

    void startBoarding()
    {
        cout << "\n=============================================\n";
        cout << "==========Now Boarding Flight " << flightNumber << "\n";
        cout << "=============================================\n";

        cout << "\n--- Boarding Business Class ---\n";
        for (Passenger *p : passengers)
        {
            if (p->getIsBusinessClass() && p->getStatusEnum() == Passenger::Status::CheckedIn)
            {
                p->boardFlight();
            }
        }

        cout << "\n--- Boarding Economy Class ---\n";
        for (Passenger *p : passengers)
        {
            if (!p->getIsBusinessClass() && p->getStatusEnum() == Passenger::Status::CheckedIn)
            {
                p->boardFlight();
            }
        }
        cout << "\nBoarding is complete.\n";
    }

    void showPassengerStatus()
    {
        cout << "\n=============================================\n";
        cout << "=========Passenger Status for Flight " << flightNumber << "\n";
        cout << "=============================================\n";
        if (passengers.empty())
        {
            cout << "No passengers have been added to this flight yet.\n";
            return;
        }
        for (const Passenger *p : passengers)
        {
            cout << " > Passenger: " << p->getName()
                 << ", Seat: " << p->getSeatNo()
                 << ", Status: " << p->getStatus() << endl;
        }
    }
};

void printHeader()
{
    cout << "\n=============================================\n";
    cout << "           Airline Boarding System           \n";
    cout << "=============================================\n";
}

int main()
{
    string flightNo, src, dest, gate;

    printHeader();
    cout << "Enter Flight Number: ";
    getline(cin, flightNo);
    cout << "Enter Source: ";
    getline(cin, src);
    cout << "Enter Destination: ";
    getline(cin, dest);
    cout << "Enter Gate Number: ";
    getline(cin, gate);

    Flight f(flightNo, src, dest, gate);

    int choice;
    do
    {
        printHeader();
        cout << "1. Add Business Class Passenger\n";
        cout << "2. Add Economy Class Passenger\n";
        cout << "3. Start Boarding\n";
        cout << "4. Show Passenger Status\n";
        cout << "0. Exit\n";
        cout << "---------------------------------------------\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1 || choice == 2)
        {
            string name, passport, seat;
            cout << "\nEnter Passenger Name: ";
            getline(cin, name);
            cout << "Enter Passport No: ";
            getline(cin, passport);
            cout << "Enter Seat No: ";
            getline(cin, seat);

            if (choice == 1)
            {
                auto *bp = new BusinessPassenger(name, passport, seat);
                f.addPassenger(bp);

                showBusinessDetails(*bp);
            }
            else
            {
                f.addPassenger(new EconomyPassenger(name, passport, seat));
            }
        }
        else if (choice == 3)
        {
            f.startBoarding();
        }
        else if (choice == 4)
        {
            f.showPassengerStatus();
        }
        else if (choice != 0)
        {
            cout << "Invalid choice! Please try again.\n";
        }

        if (choice != 0)
        {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    cout << "\nExiting Airline Boarding System. Safe travels!\n";
    return 0;
}