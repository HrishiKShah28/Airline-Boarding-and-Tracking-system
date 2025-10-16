#include <iostream>
#include <string>
#include <new> // Required for std::bad_alloc
#include <stdexcept> // Required for std::exception

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
        : name(n), passportNo(p),
          seatNo(seat), isBusinessClass(business),
          status(Status::CheckedIn) {}

    void updateStatus(Status s) { status = s; }

public:
    virtual ~Passenger() = default; // Make destructor virtual for base class

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
    // Make boardFlight a virtual function so derived classes can override it
    virtual void boardFlight()
    {
    }
};

class BusinessPassenger : public Passenger
{
private:
    bool loungeAccess;
    bool priorityBoarding;
    int baggageAllowance;
    double baseFare;
    friend void showBusinessDetails(const BusinessPassenger &bp);

public:
    BusinessPassenger()
        : Passenger("", "", "", true), loungeAccess(true), priorityBoarding(true),
          baggageAllowance(40), baseFare(1500.0)
    {
        cout << "Business Passenger created (Default Constructor)" << endl;
    }

    BusinessPassenger(string n, string p, string seat)
        : Passenger(n, p, seat, true), loungeAccess(true),
          priorityBoarding(true), baggageAllowance(40), baseFare(1500.0)
    {
        cout << "Business Passenger created for " << getName() << endl;
    }

    void boardFlight() override
    {
        updateStatus(Status::BoardedBusiness);
        cout << "PRIORITY BOARDING: Business passenger " << getName() << " has boarded." << endl;
    }

    virtual void show() const
    {
        cout << "\n--- BUSINESS CLASS PASSENGER ---" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Passport No: " << getPassportNo() << endl;
        cout << "Seat No: " << getSeatNo() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Lounge Access: " << (loungeAccess ? "Yes" : "No") << endl;
        cout << "Priority Boarding: " << (priorityBoarding ? "Yes" : "No") << endl;
        cout << "Baggage: " << baggageAllowance << " kg" << endl;
    }

    double totalFare() const
    {
        return baseFare;
    }

    ~BusinessPassenger()
    {
        cout << "Business Passenger " << getName() << " destroyed" << endl;
    }
};

// =================================================================
// START: MULTILEVEL INHERITANCE IMPLEMENTATION
// Chain: FirstClassPassenger -> BusinessPassenger -> Passenger
// =================================================================
class FirstClassPassenger : public BusinessPassenger
{
private:
    bool hasPrivateSuite;

public:
    FirstClassPassenger(string n, string p, string seat)
        : BusinessPassenger(n, p, seat), hasPrivateSuite(true)
    {
        cout << "First Class Passenger created for " << getName() << endl;
    }

    // Override boardFlight for First Class
    void boardFlight() override
    {
        updateStatus(Status::BoardedBusiness); // Re-using Business status for simplicity
        cout << "ULTRA PRIORITY BOARDING: First Class passenger " << getName() << " has boarded to their private suite." << endl;
    }

    // Override show to add First Class details
    void show() const override
    {
        // Call the parent's show method first
        BusinessPassenger::show();
        // Add new details
        cout << "Private Suite: " << (hasPrivateSuite ? "Yes" : "No") << endl;
    }

    ~FirstClassPassenger()
    {
        cout << "First Class Passenger " << getName() << " destroyed" << endl;
    }
};
// =================================================================
// END: MULTILEVEL INHERITANCE IMPLEMENTATION
// =================================================================

void showBusinessDetails(const BusinessPassenger &bp)
{
    cout << "\n[Friend Function Access] Business Passenger Details" << endl;
    cout << "Name: " << bp.getName() << endl;
    cout << "Lounge Access: " << (bp.loungeAccess ? "Yes" : "No") << endl;
    cout << "Priority Boarding: " << (bp.priorityBoarding ? "Yes" : "No") << endl;
    cout << "Baggage Allowance: " << bp.baggageAllowance << " kg" << endl;
    cout << "Base Fare: " << bp.baseFare << endl;
}

class EconomyPassenger : public Passenger
{
private:
    int baggageAllowance;
    bool mealIncluded;
    double baseFare;

public:
    EconomyPassenger()
        : Passenger("", "", "", false), baggageAllowance(20),
          mealIncluded(false), baseFare(500.0)
    {
        cout << "Economy Passenger created (Default Constructor)" << endl;
    }

    EconomyPassenger(string n, string p, string seat)
        : Passenger(n, p, seat, false), baggageAllowance(20),
          mealIncluded(false), baseFare(500.0)
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
        cout << "Baggage: " << baggageAllowance << " kg" << endl;
        cout << "Meal Included: " << (mealIncluded ? "Yes" : "No") << endl;
    }

    double totalFare() const
    {
        return baseFare;
    }

    ~EconomyPassenger()
    {
        cout << "Economy Passenger " << getName() << " destroyed" << endl;
    }
};

// =================================================================
// START: MULTIPLE INHERITANCE IMPLEMENTATION
// A new base class representing an airline employee
// =================================================================
class AirlineStaff
{
private:
    string employeeId;

public:
    AirlineStaff(string id) : employeeId(id) {}
    string getEmployeeId() const { return employeeId; }
    void showStaffDetails() const
    {
        cout << "Employee ID: " << employeeId << endl;
        cout << "Travel Type: Staff on Duty" << endl;
    }
    virtual ~AirlineStaff() { cout << "AirlineStaff object destroyed" << endl; }
};

// This class inherits from both a passenger type and a staff type
class StaffPassenger : public EconomyPassenger, public AirlineStaff
{
public:
    StaffPassenger(string n, string p, string seat, string empId)
        : EconomyPassenger(n, p, seat), AirlineStaff(empId)
    {
        cout << "Staff Passenger created for " << getName() << " (ID: " << getEmployeeId() << ")" << endl;
    }

    // New show() method to display combined info
    void show() const
    {
        // Call parent's show method
        EconomyPassenger::show();
        // Show staff details
        showStaffDetails();
    }

    ~StaffPassenger()
    {
        cout << "Staff Passenger " << getName() << " destroyed" << endl;
    }
};
// =================================================================
// END: MULTIPLE INHERITANCE IMPLEMENTATION
// =================================================================

class Flight
{
private:
    string flightNumber;
    string source;
    string destination;
    string gate;
    Passenger **passengers;
    int passengerCount;
    int capacity;

public:
    Flight(string fn, string src, string dest, string g)
        : flightNumber(fn), source(src), destination(dest), gate(g), passengers(nullptr), passengerCount(0), capacity(10)
    {
        cout << "\nFlight " << flightNumber << " from " << source << " to " << destination
             << " is ready for check-in at gate " << gate << "." << endl;
        
        // Use try-catch for the initial memory allocation.
        try {
            passengers = new Passenger*[capacity];
        } catch (const std::bad_alloc& e) {
            cerr << "FATAL: Memory allocation failed for flight passengers list. " << e.what() << endl;
            throw; // Re-throw exception to be caught in main.
        }
    }

    ~Flight()
    {
        for (int i = 0; i < passengerCount; i++)
        {
            delete passengers[i];
        }
        delete[] passengers;
    }

    void addPassenger(Passenger *p)
    {
        if (passengerCount >= capacity)
            resize(); // This might throw an exception.
        passengers[passengerCount++] = p;
        cout << "Passenger " << p->getName() << " added to flight " << flightNumber << "." << endl;
    }

    void addPassenger(const string &n, const string &p, const string &seat, bool business)
    {
        if (passengerCount >= capacity)
            resize(); // This might throw an exception.
        
        Passenger* np = nullptr;
        // Use try-catch for creating new passenger objects.
        try {
            if (business)
                np = new BusinessPassenger(n, p, seat);
            else
                np = new EconomyPassenger(n, p, seat);
        } catch (const std::bad_alloc& e) {
            cerr << "ERROR: Failed to create passenger object. Not enough memory. " << e.what() << endl;
            throw; // Re-throw to be caught by main.
        }
        
        passengers[passengerCount++] = np;
        cout << "Passenger " << np->getName() << " added to flight " << flightNumber
             << " using overloaded function." << endl;
    }

    void resize()
    {
        // Use try-catch for resizing the dynamic array.
        try {
            capacity *= 2;
            Passenger **temp = new Passenger *[capacity];
            for (int i = 0; i < passengerCount; i++)
            {
                temp[i] = passengers[i];
            }
            delete[] passengers;
            passengers = temp;
            cout << "[System] Flight passenger capacity increased to " << capacity << endl;
        } catch (const std::bad_alloc& e) {
            cerr << "ERROR: Failed to resize passenger list. Not enough memory. " << e.what() << endl;
            throw; // Re-throw to be caught by main.
        }
    }

    void startBoarding()
    {
        cout << "\n=============================================\n";
        cout << "==========Now Boarding Flight " << flightNumber << "\n";
        cout << "=============================================\n";

        cout << "\n--- Boarding Business Class ---\n";
        for (int i = 0; i < passengerCount; i++)
        {
            if (passengers[i]->getIsBusinessClass() &&
                passengers[i]->getStatusEnum() == Passenger::Status::CheckedIn)
            {
                passengers[i]->boardFlight();
            }
        }

        cout << "\n--- Boarding Economy Class ---\n";
        for (int i = 0; i < passengerCount; i++)
        {
            if (!passengers[i]->getIsBusinessClass() &&
                passengers[i]->getStatusEnum() == Passenger::Status::CheckedIn)
            {
                passengers[i]->boardFlight();
            }
        }
        cout << "\nBoarding is complete.\n";
    }

    void showPassengerStatus()
    {
        cout << "\n=============================================\n";
        cout << "=========Passenger Status for Flight " << flightNumber << "\n";
        cout << "=============================================\n";
        if (passengerCount == 0)
        {
            cout << "No passengers have been added to this flight yet.\n";
            return;
        }
        for (int i = 0; i < passengerCount; i++)
        {
            cout << " > Passenger: " << passengers[i]->getName()
                 << ", Seat: " << passengers[i]->getSeatNo()
                 << ", Status: " << passengers[i]->getStatus() << endl;
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
    try 
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
            cout << "5. Add Passenger (using Overloaded Function)\n";
            cout << "6. Add First Class Passenger (Multilevel Inheritance)\n";
            cout << "7. Add Staff Passenger (Multiple Inheritance)\n";
            cout << "0. Exit\n";
            cout << "---------------------------------------------\n";
            cout << "Enter choice: ";

            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            cin.ignore(10000, '\n');

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
            else if (choice == 5)
            {
                string name, passport, seat;
                int type;
                cout << "\nEnter Passenger Name: ";
                getline(cin, name);
                cout << "Enter Passport No: ";
                getline(cin, passport);
                cout << "Enter Seat No: ";
                getline(cin, seat);
                cout << "Enter Class (1 = Business, 2 = Economy): ";
                cin >> type;
                cin.ignore(10000, '\n');

                bool business = (type == 1);
                f.addPassenger(name, passport, seat, business);
            }
            else if (choice == 6) // Handle First Class Passenger
            {
                string name, passport, seat;
                cout << "\nEnter First Class Passenger Name: ";
                getline(cin, name);
                cout << "Enter Passport No: ";
                getline(cin, passport);
                cout << "Enter Seat No: ";
                getline(cin, seat);
                f.addPassenger(new FirstClassPassenger(name, passport, seat));
            }
            else if (choice == 7) // Handle Staff Passenger
            {
                string name, passport, seat, empId;
                cout << "\nEnter Staff Passenger Name: ";
                getline(cin, name);
                cout << "Enter Passport No: ";
                getline(cin, passport);
                cout << "Enter Seat No: ";
                getline(cin, seat);
                cout << "Enter Employee ID: ";
                getline(cin, empId);
                f.addPassenger(new StaffPassenger(name, passport, seat, empId));
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
    }
    catch (const std::bad_alloc& e)
    {
        // This will catch memory allocation failures.
        cerr << "\nCRITICAL ERROR: A memory allocation failed. The program cannot continue." << endl;
        cerr << "Details: " << e.what() << endl;
        return 1; // Exit with an error code
    }
    catch (const std::exception& e)
    {
        // This is a general catch-all for other standard exceptions.
        cerr << "\nAn unexpected error occurred: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        // This catches any other unknown exceptions.
        cerr << "\nAn unknown fatal error occurred. The program will terminate." << endl;
        return 1;
    }

    cout << "\nExiting Airline Boarding System. Safe travels!\n";
    return 0;
}