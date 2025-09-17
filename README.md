# ✈️ Airline Boarding and Tracking System

This is a **C++ project** that simulates an airline boarding and passenger tracking system.  
It is built entirely with **Object-Oriented Programming (OOP)** concepts such as **inheritance, polymorphism, constructors, destructors, and friend functions**.  

No database or external library was used — everything is implemented with **basic C++ only**, using **manual arrays and dynamic memory** instead of STL.

---

## 📌 Features
- **Passenger Management**  
  - Stores passenger details (ID, name, age, passport, status).  
  - Supports **Business** and **Economy** subclasses.  

- **Flight Management**  
  - Handles flight details (number, source, destination, gate).  
  - Maintains a manual array of passengers.  

- **Economy & Business Classes**  
  - Demonstrates **inheritance** and **specialization**.  
  - Economy: optional meal, baggage calculation.  
  - Business: lounge access, priority boarding, premium baggage rules.  

- **Business Class Extras**  
  - Lounge access ✔️  
  - Priority boarding ✔️  
  - Extra baggage fare calculation ✔️  

- **Boarding Simulation**  
  - Business passengers board first (priority).  
  - Economy passengers board after Business.  
  - Tracks and displays status of each passenger.  

- **Fare Calculation & Comparison**  
  - Business: base fare + baggage charges.  
  - Economy: base fare + baggage + meal charges.  
  - Compare fares using **friend functions**.  

---

## 🛠️ Technologies Used
- **Language:** C++  
- **Paradigm:** Object-Oriented Programming (OOP)  
- **No DBMS used**  
- **No STL / external libraries** – manual arrays and memory management  

---
