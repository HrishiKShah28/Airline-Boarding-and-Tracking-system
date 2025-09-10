#pragma once
#include <string>
#include <iostream>

class Passenger {
public:
    enum class Status { CheckedIn, BoardedBusiness, BoardedEconomy };

private:
    std::string name;
    std::string passportNo;
    std::string seatNo;
    Status status;
    bool isBusinessClass;

protected:
    // Protected constructor so only derived classes can create passengers
    Passenger(std::string n, std::string p, std::string seat, bool business)
        : name(std::move(n)), passportNo(std::move(p)),
          seatNo(std::move(seat)), isBusinessClass(business),
          status(Status::CheckedIn) {}

    void updateStatus(Status s) { status = s; }

public:
    virtual ~Passenger() = default;

    // Getters (const-correct)
    std::string getName() const { return name; }
    std::string getPassportNo() const { return passportNo; }
    std::string getSeatNo() const { return seatNo; }
    bool getIsBusinessClass() const { return isBusinessClass; }
    Status getStatusEnum() const { return status; }

    // Convert status to readable string
    std::string getStatus() const {
        switch (status) {
            case Status::CheckedIn: return "Checked-in";
            case Status::BoardedBusiness: return "Boarded (Business)";
            case Status::BoardedEconomy: return "Boarded (Economy)";
        }
        return "Unknown";
    }

    // Pure virtual → must implement in derived
    virtual void boardFlight() = 0;
};

class BusinessPassenger : public Passenger {
public:
    BusinessPassenger(std::string n, std::string p, std::string seat)
        : Passenger(std::move(n), std::move(p), std::move(seat), true) {}

    void boardFlight() override {
        updateStatus(Status::BoardedBusiness);
        std::cout << "Business Passenger " << getName()
                  << " (Seat " << getSeatNo() << ") boarded.\n";
    }
};

class EconomyPassenger : public Passenger {
public:
    EconomyPassenger(std::string n, std::string p, std::string seat)
        : Passenger(std::move(n), std::move(p), std::move(seat), false) {}

    void boardFlight() override {
        updateStatus(Status::BoardedEconomy);
        std::cout << "Economy Passenger " << getName()
                  << " (Seat " << getSeatNo() << ") boarded.\n";
    }
};
