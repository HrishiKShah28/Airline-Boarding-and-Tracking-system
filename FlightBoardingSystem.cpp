#include <iostream>
#include <string>

using namespace std;

class Flight; 

class Passenger {
public:
    enum class Status { CheckedIn, BoardedBusiness, BoardedEconomy };

private:
    string name;
    string passportNo;
    string seatNo;
    Status status;
    bool isBusinessClass;

protected:
    Passenger(string n, string p, string seat, bool business) {
        this->name = n;
        this->passportNo = p;
        this->seatNo = seat;
        this->isBusinessClass = business;
        this->status = Status::CheckedIn;
    }

    void updateStatus(Status s) { this->status = s; }

public:
    virtual ~Passenger() = default;

    string getName() const { return this->name; }
    string getPassportNo() const { return this->passportNo; }
    string getSeatNo() const { return this->seatNo; }
    bool getIsBusinessClass() const { return this->isBusinessClass; }
    Status getStatusEnum() const { return this->status; }

    string getStatus() const {
        switch (this->status) {
            case Status::CheckedIn: return "Checked-in";
            case Status::BoardedBusiness: return "Boarded (Business)";
            case Status::BoardedEconomy: return "Boarded (Economy)";
        }
        return "Unknown";
    }

    virtual void boardFlight() {  }
};

class BusinessPassenger : public Passenger {
private:
    bool loungeAccess;
    bool priorityBoarding;
    int baggageAllowance;
    double baseFare;

    friend void showBusinessDetails(const BusinessPassenger &bp);

public:
    BusinessPassenger() : Passenger("", "", "", true) {
        this->loungeAccess = true;
        this->priorityBoarding = true;
        this->baggageAllowance = 40;
        this->baseFare = 1500.0;
        cout << "Business Passenger created (Default Constructor)" << endl;
    }

    BusinessPassenger(string n, string p, string seat) : Passenger(n, p, seat, true) {
        this->loungeAccess = true;
        this->priorityBoarding = true;
        this->baggageAllowance = 40;
        this->baseFare = 1500.0;
        cout << "Business Passenger created for " << getName() << endl;
    }

    void boardFlight() override {
        updateStatus(Status::BoardedBusiness);
        cout << "PRIORITY BOARDING: Business passenger " << getName() << " has boarded." << endl;
    }

    virtual void show() const {
        cout << "\n--- BUSINESS CLASS PASSENGER ---" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Passport No: " << getPassportNo() << endl;
        cout << "Seat No: " << getSeatNo() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Lounge Access: " << (loungeAccess ? "Yes" : "No") << endl;
        cout << "Priority Boarding: " << (priorityBoarding ? "Yes" : "No") << endl;
        cout << "Baggage: " << baggageAllowance << " kg" << endl;
    }

    double totalFare() const {
        return this->baseFare;
    }

    ~BusinessPassenger() {
        cout << "Business Passenger " << getName() << " destroyed" << endl;
    }
};

class FirstClassPassenger : public BusinessPassenger {
private:
    bool hasPrivateSuite;

public:
    FirstClassPassenger(string n, string p, string seat)
        : BusinessPassenger(n, p, seat) 
    {
        this->hasPrivateSuite = true;
        cout << "First Class Passenger created for " << getName() << endl;
    }

    void boardFlight() override {
        updateStatus(Status::BoardedBusiness);
        cout << "ULTRA PRIORITY BOARDING: First Class passenger "
             << getName() << " has boarded to their private suite." << endl;
    }

    void show() const override {
        BusinessPassenger::show();
        cout << "Private Suite: " << (hasPrivateSuite ? "Yes" : "No") << endl;
    }

    ~FirstClassPassenger() {
        cout << "First Class Passenger " << getName() << " destroyed" << endl;
    }
};

void showBusinessDetails(const BusinessPassenger &bp) {
    cout << "\n[Friend Function Access] Business Passenger Details" << endl;
    cout << "Name: " << bp.getName() << endl;
    cout << "Lounge Access: " << (bp.loungeAccess ? "Yes" : "No") << endl;
    cout << "Priority Boarding: " << (bp.priorityBoarding ? "Yes" : "No") << endl;
    cout << "Baggage Allowance: " << bp.baggageAllowance << " kg" << endl;
    cout << "Base Fare: " << bp.baseFare << endl;
}
class EconomyPassenger : public Passenger {
private:
    int baggageAllowance;
    bool mealIncluded;
    double baseFare;

public:
    EconomyPassenger() : Passenger("", "", "", false) {
        this->baggageAllowance = 20;
        this->mealIncluded = false;
        this->baseFare = 500.0;
        cout << "Economy Passenger created (Default Constructor)" << endl;
    }

    EconomyPassenger(string n, string p, string seat) : Passenger(n, p, seat, false) {
        this->baggageAllowance = 20;
        this->mealIncluded = false;
        this->baseFare = 500.0;
        cout << "Economy Passenger created for " << getName() << endl;
    }

    void boardFlight() override {
        updateStatus(Status::BoardedEconomy);
        cout << "Economy passenger " << getName() << " has boarded." << endl;
    }

    void show() const {
        cout << "\n--- ECONOMY CLASS PASSENGER ---" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Passport No: " << getPassportNo() << endl;
        cout << "Seat No: " << getSeatNo() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Baggage: " << baggageAllowance << " kg" << endl;
        cout << "Meal Included: " << (mealIncluded ? "Yes" : "No") << endl;
    }

    double totalFare() const { return this->baseFare; }

    ~EconomyPassenger() {
        cout << "Economy Passenger " << getName() << " destroyed" << endl;
    }
};

class AirlineStaff {
private:
    string employeeId;

public:
    AirlineStaff(string id) {
        this->employeeId = id;
    }

    string getEmployeeId() const { return this->employeeId; }

    void showStaffDetails() const {
        cout << "Employee ID: " << employeeId << endl;
        cout << "Travel Type: Staff on Duty" << endl;
    }

    virtual ~AirlineStaff() {
        cout << "AirlineStaff object destroyed" << endl;
    }
};

class StaffPassenger : public EconomyPassenger, public AirlineStaff {
public:
    StaffPassenger(string n, string p, string seat, string empId)
        : EconomyPassenger(n, p, seat), AirlineStaff(empId)
    {
        cout << "Staff Passenger created for " 
             << getName() << " (ID: " << getEmployeeId() << ")" << endl;
    }

    void show() const {
        EconomyPassenger::show();
        showStaffDetails();
    }

    ~StaffPassenger() {
        cout << "Staff Passenger " << getName() << " destroyed" << endl;
    }
};

class Flight {
private:
    string flightNumber;
    string source;
    string destination;
    string gate;
    Passenger **passengers;
    int passengerCount;
    int capacity;

public:
    Flight(string fn, string src, string dest, string g) {
        this->flightNumber = fn;
        this->source = src;
        this->destination = dest;
        this->gate = g;

        cout << "\nFlight " << flightNumber << " from " << source
             << " to " << destination << " is ready for check-in at gate "
             << gate << "." << endl;

        capacity = 10;
        passengerCount = 0;
        passengers = new Passenger*[capacity];
    }

    ~Flight() {
        for (int i = 0; i < passengerCount; i++) {
            delete passengers[i];
        }
        delete[] passengers;
    }

    void resize() {
        capacity = capacity * 2;
        Passenger **temp = new Passenger*[capacity];

        for (int i = 0; i < passengerCount; i++) {
            temp[i] = passengers[i];
        }

        delete[] passengers;
        passengers = temp;
    }

    void addPassenger(Passenger *p) {
        if (passengerCount >= capacity) resize();
        passengers[passengerCount] = p;
        passengerCount++;

        cout << "Passenger " << p->getName()
             << " added to flight " << flightNumber << "." << endl;
    }

    void addPassenger(const string &n, const string &p, const string &seat, bool isBiz) {
        if (passengerCount >= capacity) resize();

        Passenger *temp = nullptr;
        if (isBiz) temp = new BusinessPassenger(n, p, seat);
        else temp = new EconomyPassenger(n, p, seat);

        passengers[passengerCount] = temp;
        passengerCount++;

        cout << "Passenger " << temp->getName()
             << " added to flight " << flightNumber
             << " using overloaded function." << endl;
    }

    void startBoarding() {
        cout << "\n=============================================\n";
        cout << "============ Boarding Flight " << flightNumber << " ============\n";
        cout << "=============================================\n";

        cout << "\n--- Boarding Business Class ---\n";
        for (int i = 0; i < passengerCount; i++) {
            if (passengers[i]->getIsBusinessClass() &&
                passengers[i]->getStatusEnum() == Passenger::Status::CheckedIn)
            {
                passengers[i]->boardFlight();
            }
        }

        cout << "\n--- Boarding Economy Class ---\n";
        for (int i = 0; i < passengerCount; i++) {
            if (!passengers[i]->getIsBusinessClass() &&
                passengers[i]->getStatusEnum() == Passenger::Status::CheckedIn)
            {
                passengers[i]->boardFlight();
            }
        }

        cout << "\nBoarding is complete.\n";
    }

    void showPassengerStatus() {
        cout << "\n=============================================\n";
        cout << "======= Passenger Status for Flight " << flightNumber << " =======\n";
        cout << "=============================================\n";

        if (passengerCount == 0) {
            cout << "No passengers added yet.\n";
            return;
        }

        for (int i = 0; i < passengerCount; i++) {
            cout << "Passenger: " << passengers[i]->getName()
                 << ", Seat: " << passengers[i]->getSeatNo()
                 << ", Status: " << passengers[i]->getStatus() << endl;
        }
    }
};

void printHeader() {
    cout << "\n=============================================\n";
    cout << "           Airline Boarding System           \n";
    cout << "=============================================\n";
}

int main() {
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

    do {
        printHeader();
        cout << "1. Add Business Class Passenger\n";
        cout << "2. Add Economy Class Passenger\n";
        cout << "3. Start Boarding\n";
        cout << "4. Show Passenger Status\n";
        cout << "5. Add Passenger (Overloaded Function)\n";
        cout << "6. Add First Class Passenger\n";
        cout << "7. Add Staff Passenger\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        cin.ignore(10000, '\n');

        if (choice == 1 || choice == 2) {
            string name, pass, seat;
            cout << "\nEnter Passenger Name: ";
            getline(cin, name);

            cout << "Enter Passport No: ";
            getline(cin, pass);

            cout << "Enter Seat No: ";
            getline(cin, seat);

            if (choice == 1) {
                auto *bp = new BusinessPassenger(name, pass, seat);
                f.addPassenger(bp);
                showBusinessDetails(*bp);
            } else {
                f.addPassenger(new EconomyPassenger(name, pass, seat));
            }
        }

        else if (choice == 3) {
            f.startBoarding();
        }

        else if (choice == 4) {
            f.showPassengerStatus();
        }

        else if (choice == 5) {
            string name, pass, seat;
            int type;
            cout << "\nEnter Passenger Name: ";
            getline(cin, name);

            cout << "Enter Passport No: ";
            getline(cin, pass);

            cout << "Enter Seat No: ";
            getline(cin, seat);

            cout << "Enter Class (1 = Business, 2 = Economy): ";
            cin >> type;
            cin.ignore(10000, '\n');

            bool biz = (type == 1);
            f.addPassenger(name, pass, seat, biz);
        }

        else if (choice == 6) {
            string n, p, s;
            cout << "\nEnter First Class Passenger Name: ";
            getline(cin, n);

            cout << "Enter Passport No: ";
            getline(cin, p);

            cout << "Enter Seat No: ";
            getline(cin, s);

            f.addPassenger(new FirstClassPassenger(n, p, s));
        }

        else if (choice == 7) {
            string n, p, s, id;
            cout << "\nEnter Staff Passenger Name: ";
            getline(cin, n);

            cout << "Enter Passport No: ";
            getline(cin, p);

            cout << "Enter Seat No: ";
            getline(cin, s);

            cout << "Enter Employee ID: ";
            getline(cin, id);

            f.addPassenger(new StaffPassenger(n, p, s, id));
        }

        else if (choice != 0) {
            cout << "Invalid option.\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    cout << "\nExiting Airline Boarding System. Safe travels!\n";
    return 0;
}
