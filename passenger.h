
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

    string getStatus() const {
        switch (status) {
            case Status::CheckedIn: return "Checked-in";
            case Status::BoardedBusiness: return "Boarded (Business)";
            case Status::BoardedEconomy: return "Boarded (Economy)";
        }
        return "Unknown";
    }

    virtual void boardFlight() = 0;
};
