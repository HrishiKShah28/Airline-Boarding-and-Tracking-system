class Passenger {
private:
    string name;
    string passportNo;
    string status;  
protected:
    string seatNo;
    bool isBusinessClass;

public:
    Passenger(string n, string p, string seat, bool business)
        : name(n), passportNo(p), seatNo(seat), isBusinessClass(business), status("Checked-in") {}

    string getName() const { return name; }
    string getPassportNo() const { return passportNo; }
    string getSeatNo() const { return seatNo; }
    string getStatus() const { return status; }
    void updateStatus(string s) { status = s; }

    virtual void boardFlight() = 0;

    virtual ~Passenger() {}
};
