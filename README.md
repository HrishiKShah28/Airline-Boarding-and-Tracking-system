✈️ Airline Boarding and Tracking System
This is a C++ project that simulates an airline boarding and passenger tracking system.
It is built entirely with Object-Oriented Programming (OOP) concepts, demonstrating a comprehensive class hierarchy with hierarchical, multilevel, and multiple inheritance. The system also showcases polymorphism, constructors, destructors, function overloading, and friend functions.

No database or external library was used — everything is implemented with standard C++ only, using manual dynamic arrays and memory management instead of the STL.

📌 Features
Passenger Management

Stores passenger details (name, passport, seat, and boarding status).

Utilizes a base Passenger class with several specialized derived classes.

Complex Class Hierarchy

Hierarchical Inheritance: BusinessPassenger and EconomyPassenger inherit from Passenger.

Multilevel Inheritance: FirstClassPassenger inherits from BusinessPassenger, creating the chain: FirstClassPassenger -> BusinessPassenger -> Passenger.

Multiple Inheritance: StaffPassenger inherits from both EconomyPassenger and a new AirlineStaff base class, combining attributes from both.

Flight Management

Handles flight details (number, source, destination, gate).

Maintains a dynamic array of Passenger pointers, capable of holding any passenger type (demonstrating polymorphism).

The passenger list automatically resizes when its capacity is reached.

Boarding Simulation

Demonstrates polymorphism by calling virtual boardFlight() methods.

First Class and Business passengers board first (priority boarding).

Economy and Staff passengers board after premium classes.

Tracks and displays the live status of each passenger (Checked-in or Boarded).

Demonstration of Various OOP Concepts

Polymorphism: The Flight class manages all passenger types through a Passenger* pointer array.

Function Overloading: The Flight::addPassenger method is overloaded for different ways of adding passengers.

Friend Function: A global function showBusinessDetails can access the private members of the BusinessPassenger class.

Virtual Functions: Functions like boardFlight() and show() are declared virtual to allow for overriding in derived classes.

🛠️ Technologies Used
Language: C++

Paradigm: Object-Oriented Programming (OOP)

No DBMS used

No STL / external libraries – manual arrays and dynamic memory management only.
