#pragma once
#include <string>
#include <iostream>
using namespace std;

class Passenger {
public:
    enum class Status { CheckedIn, BoardedBusiness, BoardedEconomy };

protected:
    string id;
    string name;
    int age;
    string passportNo;
    Status status;

public:
    // Default constructor
    Passenger() : id(""), name(""), age(0), passportNo(""), status(Status::CheckedIn) {}
    
    // Parameterized constructor
    Passenger(string i, string n, int a, string passport)
        : id(i), name(n), age(a), passportNo(passport), status(Status::CheckedIn) {}

    // Virtual destructor
    virtual ~Passenger() = default;

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getPassportNo() const { return passportNo; }
    Status getStatusEnum() const { return status; }

    string getStatus() const {
        switch (status) {
            case Status::CheckedIn: return "Checked-in";
            case Status::BoardedBusiness: return "Boarded (Business)";
            case Status::BoardedEconomy: return "Boarded (Economy)";
        }
        return "Unknown";
    }

    // Display basic passenger info
    void displayInfo() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Passport: " << passportNo << endl;
        cout << "Status: " << getStatus() << endl;
    }

    // Pure virtual function
    virtual void boardFlight() = 0;

protected:
    void updateStatus(Status s) { status = s; }
};